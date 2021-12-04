#include "pch.h"
#include "llmoney.h"
#include <memory>
#include <vector>
#include "Event.h"
#include <LoggerAPI.h>
static std::unique_ptr<SQLite::Database> db;
money_t DEF_MONEY = 0;

struct cleanSTMT {
	SQLite::Statement& get;
	cleanSTMT(SQLite::Statement& g) :get(g) {

	}
	~cleanSTMT() {
		get.reset();
		get.clearBindings();
	}
};
bool initDB() {
	try {
		Logger::setTitle("Money");
		db = std::make_unique<SQLite::Database>("plugins\\LLMoney\\money.db", SQLite::OPEN_CREATE | SQLite::OPEN_READWRITE);
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
	catch (std::exception const& e) {
		Logger::Error("DB err %s\n", e.what());
		return false;
	}
	return true;
}

LLMONEY_API money_t LLMoneyGet(xuid_t xuid) {
	try {
		static SQLite::Statement get{ *db,"select Money from money where XUID=?" };
		get.bindNoCopy(1, &xuid, sizeof(xuid));
		money_t rv = DEF_MONEY;
		bool fg = false;
		while (get.executeStep()) {
			rv = (money_t)get.getColumn(0).getInt64();
			fg = true;
		}
		get.reset();
		get.clearBindings();
		if (!fg) {
			static SQLite::Statement set{ *db,"insert into money values (?,?)" };
			set.bindNoCopy(1, &xuid, sizeof xuid);
			set.bind(2, DEF_MONEY);
			set.exec();
			set.reset();
			set.clearBindings();
		}
		return rv;
	}
	catch (std::exception const& e) {
		Logger::Error("DB err %s\n", e.what());
		return -1;
	}
}

bool isRealTrans = true;

LLMONEY_API bool LLMoneyTrans(xuid_t from, xuid_t to, money_t val, string const& note)
{
	bool isRealTrans = ::isRealTrans;
	::isRealTrans = true;
	if(isRealTrans)
		if (!CallBeforeEvent(LLMoneyEvent::Trans, from, to, val))
			return false;

	if (val < 0 || from == to)
		return false;
	try {
		db->exec("begin");
		static SQLite::Statement set{ *db,"update money set Money=? where XUID=?" };
		if (from != "") {
			auto fmoney = LLMoneyGet(from);
			if (fmoney < val) {
				db->exec("rollback");
				return false;
			}
			fmoney -= val;
			{

				set.bindNoCopy(2, &from, sizeof from);
				set.bind(1, fmoney);
				set.exec();
				set.reset();
				set.clearBindings();
			}
		}
		if (to != "") {
			auto tmoney = LLMoneyGet(to);
			tmoney += val;
			if (tmoney < 0) {
				db->exec("rollback");
				return false;
			}
			{
				set.bindNoCopy(2, &to, sizeof to);
				set.bind(1, tmoney);
				set.exec();
				set.reset();
				set.clearBindings();
			}
		}
		{
			static SQLite::Statement addTrans{ *db,"insert into mtrans (tFrom,tTo,Money,Note) values (?,?,?,?)" };
			addTrans.bindNoCopy(1, &from, sizeof from);
			addTrans.bindNoCopy(2, &to, sizeof to);
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
	catch (std::exception const& e) {
		db->exec("rollback");
		Logger::Error("DB err %s\n", e.what());
		return false;
	}
}

LLMONEY_API bool LLMoneyAdd(xuid_t xuid, money_t money)
{
	if (!CallBeforeEvent(LLMoneyEvent::Add, 0, xuid, money))
		return false;

	isRealTrans = false;
	bool res = LLMoneyTrans(0, xuid, money, "add " + std::to_string(money));
	if(res)
		CallAfterEvent(LLMoneyEvent::Add, 0, xuid, money);
	return res;
}

LLMONEY_API bool LLMoneyReduce(xuid_t xuid, money_t money)
{
	if (!CallBeforeEvent(LLMoneyEvent::Reduce, 0, xuid, money))
		return false;

	isRealTrans = false;
	bool res = LLMoneyTrans(xuid, 0, money, "reduce " + std::to_string(money));
	if (res)
		CallAfterEvent(LLMoneyEvent::Reduce, 0, xuid, money);
	return res;
}

LLMONEY_API bool LLMoneySet(xuid_t xuid, money_t money)
{
	if (!CallBeforeEvent(LLMoneyEvent::Set, 0, xuid, money))
		return false;
	money_t now = LLMoneyGet(xuid), diff;
	xuid_t from, to;
	if (money >= now) {
		from = "";
		to = xuid;
		diff = money - now;
	}
	else {
		from = xuid;
		to = "";
		diff = now - money;
	}

	isRealTrans = false;
	bool res = LLMoneyTrans(from, to, diff, "set to " + std::to_string(money));
	if (res)
		CallAfterEvent(LLMoneyEvent::Reduce, 0, xuid, money);
	return res;
}


LLMONEY_API string LLMoneyGetHist(xuid_t xuid, int timediff)
{
	try {
		static SQLite::Statement get{ *db,"select tFrom,tTo,Money,datetime(Time,'unixepoch', 'localtime'),Note from mtrans where strftime('%s','now')-time<? and (tFrom=? OR tTo=?) ORDER BY Time DESC" };
		string rv;
		get.bind(1, timediff);
		get.bindNoCopy(2, &xuid, sizeof xuid);
		get.bindNoCopy(3, &xuid, sizeof xuid);
		while (get.executeStep()) {
			auto from = PlayerDB::fromXuid(*(xuid_t*)get.getColumn(0).getBlob());
			auto to = PlayerDB::fromXuid(*(xuid_t*)get.getColumn(1).getBlob());
			if (from != "" && to != "")
				rv += from + " -> " + to + " " + std::to_string((money_t)get.getColumn(2).getInt64()) + " " + get.getColumn(3).getText() + " (" + get.getColumn(4).getText() + ")\n";
		}
		get.reset();
		get.clearBindings();
		return rv;
	}
	catch (std::exception const& e) {
		Logger::Error("DB err %s\n", e.what());
		return "failed";
	}
}

LLMONEY_API void LLMoneyClearHist(int difftime) {
	try {
		db->exec("DELETE FROM mtrans WHERE strftime('%s','now')-time>" + std::to_string(difftime));
	}
	catch (std::exception&) {

	}
}