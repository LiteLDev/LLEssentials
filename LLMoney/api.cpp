#include "LLMoney.h"
#include <memory>
#include <vector>
#include "Event.h"
#include <LoggerAPI.h>
#include <SQLiteCpp/SQLiteCpp.h>
#include "Money.h"

static std::unique_ptr<SQLite::Database> db;
Logger moneylog("LLMoney");
#undef snprintf

struct cleanSTMT
{
	SQLite::Statement &get;

	cleanSTMT(SQLite::Statement &g) : get(g)
	{
	}

	~cleanSTMT()
	{
		get.reset();
		get.clearBindings();
	}
};

void ConvertData();

bool initDB()
{
	try
	{
		db = std::make_unique<SQLite::Database>("plugins\\LLMoney\\economy.db",
												SQLite::OPEN_CREATE | SQLite::OPEN_READWRITE);
		db->exec("PRAGMA journal_mode = MEMORY");
		db->exec("PRAGMA synchronous = NORMAL");
		db->exec("CREATE TABLE IF NOT EXISTS money ( \
			XUID  TEXT PRIMARY KEY \
			UNIQUE \
			NOT NULL, \
			Money NUMERIC NOT NULL \
		) \
			WITHOUT ROWID; ");
		db->exec("CREATE TABLE IF NOT EXISTS mtrans ( \
			tFrom TEXT  NOT NULL, \
			tTo   TEXT  NOT NULL, \
			Money NUMERIC  NOT NULL, \
			Time  NUMERIC NOT NULL \
			DEFAULT(strftime('%s', 'now')), \
			Note  TEXT \
		);");
		db->exec("CREATE INDEX IF NOT EXISTS idx ON mtrans ( \
			Time COLLATE BINARY COLLATE BINARY DESC \
		); ");
	}
	catch (std::exception const &e)
	{
		moneylog.error("Database error: {}", e.what());
		return false;
	}
	ConvertData();
	return true;
}

money_t LLMoneyGet(xuid_t xuid)
{
	try
	{
		SQLite::Statement get{*db, "select Money from money where XUID=?"};
		get.bindNoCopy(1, xuid);
		money_t rv = Settings::def_money;
		bool fg = false;
		while (get.executeStep())
		{
			rv = (money_t)get.getColumn(0).getInt64();
			fg = true;
		}
		get.reset();
		get.clearBindings();
		if (!fg)
		{
			SQLite::Statement set{*db, "insert into money values (?,?)"};
			set.bindNoCopy(1, xuid);
			set.bind(2, Settings::def_money);
			set.exec();
			set.reset();
			set.clearBindings();
		}
		return rv;
	}
	catch (std::exception const &e)
	{
		moneylog.error("Database error: {}\n", e.what());
		return -1;
	}
}

bool isRealTrans = true;

bool LLMoneyTrans(xuid_t from, xuid_t to, money_t val, string const &note)
{
	bool isRealTrans = ::isRealTrans;
	::isRealTrans = true;
	if (isRealTrans)
		if (!CallBeforeEvent(LLMoneyEvent::Trans, from, to, val))
			return false;

	if (val < 0 || from == to)
		return false;
	try
	{
		db->exec("begin");
		SQLite::Statement set{*db, "update money set Money=? where XUID=?"};
		if (from != "")
		{
			auto fmoney = LLMoneyGet(from);
			if (fmoney < val)
			{
				db->exec("rollback");
				return false;
			}
			fmoney -= val;
			{

				set.bindNoCopy(2, from);
				set.bind(1, fmoney);
				set.exec();
				set.reset();
				set.clearBindings();
			}
		}
		if (to != "")
		{
			auto tmoney = LLMoneyGet(to);
			tmoney += val;
			if (tmoney < 0)
			{
				db->exec("rollback");
				return false;
			}
			{
				set.bindNoCopy(2, to);
				set.bind(1, tmoney);
				set.exec();
				set.reset();
				set.clearBindings();
			}
		}
		{
			SQLite::Statement addTrans{*db, "insert into mtrans (tFrom,tTo,Money,Note) values (?,?,?,?)"};
			addTrans.bindNoCopy(1, from);
			addTrans.bindNoCopy(2, to);
			addTrans.bind(3, val);
			addTrans.bindNoCopy(4, note);
			addTrans.exec();
			addTrans.reset();
			addTrans.clearBindings();
		}
		db->exec("commit");

		if (isRealTrans)
			CallAfterEvent(LLMoneyEvent::Trans, from, to, val);
		return true;
	}
	catch (std::exception const &e)
	{
		db->exec("rollback");
		moneylog.error("Database error: {}\n", e.what());
		return false;
	}
}

bool LLMoneyAdd(xuid_t xuid, money_t money)
{
	if (!CallBeforeEvent(LLMoneyEvent::Add, "", xuid, money))
		return false;

	isRealTrans = false;
	bool res = LLMoneyTrans("", xuid, money, "add " + std::to_string(money));
	if (res)
		CallAfterEvent(LLMoneyEvent::Add, "", xuid, money);
	return res;
}

bool LLMoneyReduce(xuid_t xuid, money_t money)
{
	if (!CallBeforeEvent(LLMoneyEvent::Reduce, "", xuid, money))
		return false;

	isRealTrans = false;
	bool res = LLMoneyTrans(xuid, "", money, "reduce " + std::to_string(money));
	if (res)
		CallAfterEvent(LLMoneyEvent::Reduce, "", xuid, money);
	return res;
}

bool LLMoneySet(xuid_t xuid, money_t money)
{
	if (!CallBeforeEvent(LLMoneyEvent::Set, "", xuid, money))
		return false;
	money_t now = LLMoneyGet(xuid), diff;
	xuid_t from, to;
	if (money >= now)
	{
		from = "";
		to = xuid;
		diff = money - now;
	}
	else
	{
		from = xuid;
		to = "";
		diff = now - money;
	}

	isRealTrans = false;
	bool res = LLMoneyTrans(from, to, diff, "set to " + std::to_string(money));
	if (res)
		CallAfterEvent(LLMoneyEvent::Reduce, "", xuid, money);
	return res;
}

vector<std::pair<std::string, money_t>> LLMoneyRanking(unsigned short num)
{
	try
	{
		SQLite::Statement get{*db, "select * from money ORDER BY money DESC LIMIT ?"};
		vector<std::pair<std::string, money_t>> mapTemp;
		get.bind(1, num);
		while (get.executeStep())
		{
			std::string xuid = get.getColumn(0).getString();
			long long balance = get.getColumn(1).getInt64();
			// std::cout << xuid << " " << balance << "\n";
			mapTemp.push_back(std::pair<std::string, money_t>(xuid, balance));
		}
		get.reset();
		get.clearBindings();
		return mapTemp;
	}
	catch (std::exception const &e)
	{
		moneylog.error("Database error: {}\n", e.what());
		return {};
	}
}

string LLMoneyGetHist(xuid_t xuid, int timediff)
{
	try
	{
		SQLite::Statement get{*db,
							  "select tFrom,tTo,Money,datetime(Time,'unixepoch', 'localtime'),Note from mtrans where strftime('%s','now')-time<? and (tFrom=? OR tTo=?) ORDER BY Time DESC"};
		string rv;
		get.bind(1, timediff);
		get.bindNoCopy(2, xuid);
		get.bindNoCopy(3, xuid);
		while (get.executeStep())
		{
			optional<string> from, to;
			from = PlayerInfo::fromXuid(get.getColumn(0).getString());
			to = PlayerInfo::fromXuid(get.getColumn(1).getString());
			if (from.Set() && to.Set())
				if (from.val() == "")
				{
					from.val() = "System";
				}
				else if (to.val() == "")
				{
					to.val() = "System";
				}
			rv += from.val() + " -> " + to.val() + " " + std::to_string((money_t)get.getColumn(2).getInt64()) + " " +
				  get.getColumn(3).getText() + " (" + get.getColumn(4).getText() + ")\n";
		}
		get.reset();
		get.clearBindings();
		return rv;
	}
	catch (std::exception const &e)
	{
		moneylog.error("Database error: {}\n", e.what());
		return "failed";
	}
}

void LLMoneyClearHist(int difftime)
{
	try
	{
		db->exec("DELETE FROM mtrans WHERE strftime('%s','now')-time>" + std::to_string(difftime));
	}
	catch (std::exception &)
	{
	}
}

void ConvertData()
{
	if (std::filesystem::exists("plugins\\LLMoney\\money.db"))
	{
		moneylog.info("Old money data detected, try to convert old data to new data");
		try
		{
			std::unique_ptr<SQLite::Database> db2 = std::make_unique<SQLite::Database>("plugins\\LLMoney\\money.db",
																					   SQLite::OPEN_CREATE |
																						   SQLite::OPEN_READWRITE);
			SQLite::Statement get{*db2, "select hex(XUID),Money from money"};
			SQLite::Statement set{*db, "insert into money values (?,?)"};
			while (get.executeStep())
			{
				std::string blob = get.getColumn(0).getText();
				unsigned long long value;
				std::istringstream iss(blob);
				iss >> std::hex >> value;
				unsigned long long xuid = _byteswap_uint64(value);
				long long money = get.getColumn(1).getInt64();
				set.bindNoCopy(1, std::to_string(xuid));
				set.bind(2, money);
				set.exec();
				set.reset();
				set.clearBindings();
			}
			get.reset();
		}
		catch (std::exception &e)
		{
			moneylog.error("{}", e.what());
		}
		std::filesystem::rename("plugins\\LLMoney\\money.db", "plugins\\LLMoney\\money_old.db");
		moneylog.info("Conversion completed");
	}
}
#include <RemoteCallAPI.h>
#define EXPORTAPI(T) RemoteCall::exportAs("LLMoney", #T, T);

void RemoteCallInit()
{
	EXPORTAPI(LLMoneyGet);
	EXPORTAPI(LLMoneyTrans);
	EXPORTAPI(LLMoneyAdd);
	EXPORTAPI(LLMoneyReduce);
	EXPORTAPI(LLMoneySet);
	EXPORTAPI(LLMoneyGetHist);
	EXPORTAPI(LLMoneyClearHist);
}