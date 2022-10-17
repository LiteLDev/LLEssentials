#include <Global.h>
#include <MC/Player.hpp>
#include <MC/ServerPlayer.hpp>
#include <regCommandAPI.h>
#include <EventAPI.h>
#include "LLMoney.h"
#include "Money.h"
#include <SQLiteCpp/SQLiteCpp.h>

using namespace RegisterCommandHelper;

Logger logger("LLMoney");

#define JSON1(key, val)                           \
	if (json.find(key) != json.end())             \
	{                                             \
		const nlohmann::json &out = json.at(key); \
		out.get_to(val);                          \
	}

namespace Settings
{
    std::string language = "en";
    int def_money = 0;
    float pay_tax = 0.0;
    bool enable_ranking = true;

	nlohmann::json globaljson()
	{
		nlohmann::json json;
		json["language"] = language;
		json["def_money"] = def_money;
		json["pay_tax"] = pay_tax;
		json["enable_ranking"] = enable_ranking;
		return json;
	}

	void initjson(nlohmann::json json)
	{
		JSON1("language", language);
		JSON1("def_money", def_money);
		JSON1("pay_tax", pay_tax);
		JSON1("enable_ranking", enable_ranking);
	}
	void WriteDefaultConfig(const std::string &fileName)
	{
		std::ofstream file(fileName);
		if (!file.is_open())
		{
			logger.error("Can't open file {}", fileName);
			return;
		}
		auto json = globaljson();
		file << json.dump(4);
		file.close();
	}

	void LoadConfigFromJson(const std::string &fileName)
	{
		std::ifstream file(fileName);
		if (!file.is_open())
		{
			logger.error("Can't open file {}", fileName);
			return;
		}
		nlohmann::json json;
		file >> json;
		file.close();
		initjson(json);
		WriteDefaultConfig(fileName);
	}
	void reloadJson(const std::string &fileName)
	{
		std::ofstream file(fileName);
		if (file)
		{
			file << globaljson().dump(4);
		}
		else
		{
			logger.error("Configuration File Creation failed!");
		}
		file.close();
	}
} // namespace Settings

bool initDB();

bool cmp(std::pair<std::string, money_t> a, std::pair<std::string, money_t> b)
{
	return a.second > b.second;
}

class MoneyCommand : public Command
{
	enum MoneyOP : int
	{
		query = 1,
		hist = 2,
		pay = 3,
		set = 4,
		add = 5,
		reduce = 6,
		purge = 7,
		top = 8
	} op;
	string dst;
	bool dst_isSet;
	bool difftime_isSet;
	int moneynum;
	int difftime;

public:
	void execute(CommandOrigin const &ori, CommandOutput &outp) const
	{
		std::string dstxuid, myuid;
		switch (op)
		{
		case query:
		case hist:
			if (dst_isSet && (int)ori.getPermissionsLevel() > 0)
			{
				dstxuid = PlayerInfo::getXuid(dst);
			}
			else
			{
				if (ori.getOriginType() != (CommandOriginType)OriginType::Player)
				{
					outp.error(tr("money.dontuseinconsole"));
					return;
				}
				dstxuid = ori.getPlayer()->getXuid();
			}
			if (dstxuid == "")
			{
				outp.error(tr("money.no.target"));
				return;
			}
			break;
		case pay:
			if (ori.getOriginType() != (CommandOriginType)OriginType::Player)
			{
				outp.error(tr("money.dontuseinconsole"));
				return;
			}
		case set:
		case add:
		case reduce:
			dstxuid = PlayerInfo::getXuid(dst);
			if (dstxuid == "")
			{
				outp.error(tr("money.no.target"));
				return;
			}
			break;
		case purge:
			if (ori.getOriginType() != (CommandOriginType)OriginType::Player)
			{
				outp.error(tr("money.dontuseinconsole"));
				return;
			}
			if ((int)ori.getPermissionsLevel() < 1)
			{
				outp.error(tr("money.no.perm"));
				return;
			}
			break;
		case top:
			if (!Settings::enable_ranking)
			{
				outp.error("Balance ranking not enabled");
				return;
			}
		}
		switch (op)
		{
		case query:
			outp.addMessage("Balance: " + std::to_string(LLMoneyGet(dstxuid)));
			break;
		case hist:
			outp.addMessage(LLMoneyGetHist(dstxuid));
			break;
		case pay:
		{
			if (moneynum <= 0)
			{
				outp.error(tr("money.invalid.arg"));
				return;
			}
			myuid = ori.getPlayer()->getXuid();
			if (LLMoneyTrans(myuid, dstxuid, moneynum, "money pay"))
			{
				money_t fee = (money_t)(moneynum * Settings::pay_tax);
				if (fee)
					LLMoneyTrans(dstxuid, "", fee, "money pay fee");
				outp.success(tr("money.pay.succ"));
			}
			else
			{
				outp.error(tr("money.not.enough"));
			}
			return;
		}
		break;
		case set:
			if ((int)ori.getPermissionsLevel() < 1)
			{
				outp.error(tr("money.no.perm"));
				return;
			}
			if (LLMoneySet(dstxuid, moneynum))
			{
				outp.success(tr("money.set.succ"));
			}
			else
			{
				outp.error(tr("money.invalid.arg"));
			}
			break;
		case add:
			if ((int)ori.getPermissionsLevel() < 1)
			{
				outp.error(tr("money.no.perm"));
				return;
			}
			if (LLMoneyAdd(dstxuid, moneynum))
			{
				outp.success(tr("money.add.succ"));
			}
			else
			{
				outp.error(tr("money.invalid.arg"));
			}
			break;
		case reduce:
			if ((int)ori.getPermissionsLevel() < 1)
			{
				outp.error(tr("money.no.perm"));
				return;
			}
			if (LLMoneyReduce(dstxuid, moneynum))
			{
				outp.success(tr("money.reduce.succ"));
			}
			else
			{
				outp.error(tr("money.invalid.arg"));
			}
			break;
		case purge:
			if (difftime_isSet)
				LLMoneyClearHist(difftime);
			else
				LLMoneyClearHist(0);
			break;
		case top:
			vector<std::pair<std::string, money_t>> mapTemp = LLMoneyRanking();
			sort(mapTemp.begin(), mapTemp.end(), cmp);
			outp.success("===== Ranking =====");
			for (auto it = mapTemp.begin(); it != mapTemp.end(); it++)
			{
				outp.addMessage((PlayerInfo::fromXuid(it->first).empty() ? "NULL" : PlayerInfo::fromXuid(it->first)) + "  " + std::to_string(it->second));
			}
			outp.addMessage("===================");
		}
		return;
	}

	static void setup(CommandRegistry *registry)
	{

		// registerCommand
		registry->registerCommand(
			"money", "Economy system", CommandPermissionLevel::Any, {(CommandFlagValue)0},
			{(CommandFlagValue)0x80});
		// addEnum
		registry->addEnum<MoneyOP>("MoneyOP1", {{"query", MoneyOP::query},
												{"hist", MoneyOP::hist},
												{"top", MoneyOP::top}});
		registry->addEnum<MoneyOP>("MoneyOP2", {{"add", MoneyOP::add},
												{"pay", MoneyOP::pay},
												{"reduce", MoneyOP::reduce},
												{"set", MoneyOP::set}});
		registry->addEnum<MoneyOP>("MoneyOP3", {{"purge", MoneyOP::purge}});

		// registerOverload
		registry->registerOverload<MoneyCommand>(
			"money",
			makeMandatory<CommandParameterDataType::ENUM>(&MoneyCommand::op, "optional", "MoneyOP1"),
			makeOptional(&MoneyCommand::dst, "PlayerName", &MoneyCommand::dst_isSet));
		registry->registerOverload<MoneyCommand>(
			"money",
			makeMandatory<CommandParameterDataType::ENUM>(&MoneyCommand::op, "optional", "MoneyOP2"),
			makeMandatory(&MoneyCommand::dst, "PlayerName"),
			makeMandatory(&MoneyCommand::moneynum, "num"));
		registry->registerOverload<MoneyCommand>(
			"money",
			makeMandatory<CommandParameterDataType::ENUM>(&MoneyCommand::op, "optional", "MoneyOP3"),
			makeOptional(&MoneyCommand::difftime, "time", &MoneyCommand::difftime_isSet));
	}
};

class MoneySCommand : public Command
{
	enum MoneyOP : int
	{
		query = 1,
		hist = 2,
		pay = 3,
		set = 4,
		add = 5,
		reduce = 6,
	} op;
	CommandSelector<Player> player;
	bool dst_isSet;
	bool difftime_isSet;
	int moneynum;
	int difftime;

public:
	void execute(CommandOrigin const &ori, CommandOutput &outp) const
	{
		vector<std::string> dstxuidlist;
		optional<std::string> dstxuid;
		std::string myuid;
		switch (op)
		{
		case query:
		case hist:
			if (dst_isSet)
			{
				if ((int)ori.getPermissionsLevel() > 0)
				{
					if (!player.results(ori).empty())
					{
						dstxuid = player.results(ori).begin().operator*()->getXuid();
					}
				}
				else
				{
					outp.error("You don't have permission to do this");
					return;
				}
			}
			else
			{
				if (ori.getOriginType() != (CommandOriginType)OriginType::Player)
				{
					outp.error(tr("money.dontuseinconsole"));
					return;
				}
				dstxuid = ori.getPlayer()->getXuid();
			}
			if (dstxuid.val() == "")
			{
				outp.error(tr("money.no.target"));
				return;
			}
			break;
		case pay:
		{
			if (ori.getOriginType() != (CommandOriginType)OriginType::Player)
			{
				outp.error(tr("money.dontuseinconsole"));
				return;
			}
			if (player.results(ori).empty())
			{
				outp.error(tr("money.no.target"));
				return;
			}
			for (auto resu : player.results(ori))
			{
				dstxuid = resu->getXuid();
				if (!dstxuid.Set())
				{
					outp.error(tr("money.no.target"));
					return;
				}
			}
			break;
		}
		case set:
		case add:
		case reduce:
			if (player.results(ori).empty())
			{
				outp.error(tr("money.no.target"));
				return;
			}
			for (auto resu : player.results(ori))
			{
				dstxuidlist.push_back(resu->getXuid());
			}
			if (dstxuidlist.empty())
			{
				outp.error(tr("money.no.target"));
				return;
			}
			break;
		}
		switch (op)
		{
		case query:
			outp.addMessage("Balance: " + std::to_string(LLMoneyGet(dstxuid.val())));
			break;
		case hist:
			outp.addMessage(LLMoneyGetHist(dstxuid.val()));
			break;
		case pay:
			if (moneynum <= 0)
			{
				outp.error(tr("money.invalid.arg"));
				return;
			}
			myuid = ori.getPlayer()->getXuid();
			if (myuid == "")
			{
				outp.error(tr("money.no.target"));
				return;
			}
			if (LLMoneyTrans(myuid, dstxuid.val(), moneynum, "money pay"))
			{
				money_t fee = (money_t)(moneynum * Settings::pay_tax);
				if (fee)
					LLMoneyTrans(dstxuid.val(), "", fee, "money pay fee");
				outp.success(tr("money.pay.succ"));
			}
			else
			{
				outp.error(tr("money.not.enough"));
			}
			break;
		case set:
		{
			if ((int)ori.getPermissionsLevel() < 1)
			{
				outp.error(tr("money.no.perm"));
				return;
			}
			bool su = 0;
			for (auto i : dstxuidlist)
			{
				if (LLMoneySet(i, moneynum))
				{
					su = 1;
				}
			}
			if (su)
			{
				outp.success(tr("money.set.succ"));
			}
			else
			{
				outp.error(tr("money.invalid.arg"));
			}
			break;
		}
		case add:
		{
			if ((int)ori.getPermissionsLevel() < 1)
			{
				outp.error(tr("money.no.perm"));
				return;
			}
			bool su = 0;
			for (auto i : dstxuidlist)
			{
				if (LLMoneyAdd(i, moneynum))
				{
					su = 1;
				}
			}
			if (su)
			{
				outp.success(tr("money.add.succ"));
			}
			else
			{
				outp.error(tr("money.invalid.arg"));
			}
			break;
		}
		case reduce:
		{
			if ((int)ori.getPermissionsLevel() < 1)
			{
				outp.error(tr("money.no.perm"));
				return;
			}
			bool su = 0;
			for (auto i : dstxuidlist)
			{
				if (LLMoneyReduce(i, moneynum))
				{
					su = 1;
				}
			}
			if (su)
			{
				outp.success(tr("money.reduce.succ"));
			}
			else
			{
				outp.error(tr("money.invalid.arg"));
			}
			break;
		}
		}
		return;
	}

	static void setup(CommandRegistry *registry)
	{
		// registerCommand
		registry->registerCommand(
			"money_s", "Economy system(Selector)", CommandPermissionLevel::Any, {(CommandFlagValue)0},
			{(CommandFlagValue)0x80});

		// addEnum
		registry->addEnum<MoneyOP>("MoneyOP1", {{"query", MoneyOP::query},
												{"hist", MoneyOP::hist}});
		registry->addEnum<MoneyOP>("MoneyOP2", {{"add", MoneyOP::add},
												{"pay", MoneyOP::pay},
												{"reduce", MoneyOP::reduce},
												{"set", MoneyOP::set}});

		// registerOverload
		registry->registerOverload<MoneySCommand>(
			"money_s",
			makeMandatory<CommandParameterDataType::ENUM>(&MoneySCommand::op, "optional", "MoneyOP1"),
			makeOptional(&MoneySCommand::player, "PlayerName", &MoneySCommand::dst_isSet));

		registry->registerOverload<MoneySCommand>(
			"money_s",
			makeMandatory<CommandParameterDataType::ENUM>(&MoneySCommand::op, "optional", "MoneyOP2"),
			makeMandatory(&MoneySCommand::player, "PlayerName"),
			makeMandatory(&MoneySCommand::moneynum, "num"));
	}
};
#include "lang.h"

void loadCfg()
{
	// config
	if (!std::filesystem::exists("plugins/LLMoney"))
		std::filesystem::create_directories("plugins/LLMoney");
	if (std::filesystem::exists("plugins/LLMoney/money.json"))
	{
		try
		{
			Settings::LoadConfigFromJson("plugins/LLMoney/money.json");
		}
		catch (std::exception &e)
		{
			logger.error("Configuration file is Invalid, Error: {}", e.what());
		}
		catch (...)
		{
			logger.error("Configuration file is Invalid");
		}
	}
	else
	{
		Settings::WriteDefaultConfig("plugins/LLMoney/money.json");
	}
}

void RemoteCallInit();
void entry()
{
	loadCfg();
	if (!initDB())
	{
		return;
	}
	Event::RegCmdEvent::subscribe([](const Event::RegCmdEvent &ev)
								  {
		MoneyCommand::setup(ev.mCommandRegistry);
		MoneySCommand::setup(ev.mCommandRegistry);
		return true; });
	Translation::load("plugins\\LLMoney\\language.json", Settings::language, defaultLangData);
	logger.info("Loaded version: {}", LLMONEY_VERSION.toString());
	RemoteCallInit();
}
