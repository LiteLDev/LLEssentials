#include "pch.h"
#include <Global.h>
#include <iostream>
#include "rapidjson/rapidjson.h"
#include "rapidjson/document.h"
#include <MC/Player.hpp>
#include <regCommandAPI.h>
#include <map>
#include "pch.h"
#include<fstream>
#include<streambuf>
#include <EventAPI.h>
#include "LLMoney.h"
#include "Money.h"
#include <filesystem>
#include <JsonLoader.h>
using namespace RegisterCommandHelper;

double MoneyFee;
bool initDB();

extern money_t DEF_MONEY;

/*
bool oncmd_money_sel(CommandOrigin const& ori, CommandOutput& outp, MyEnum<MONEYOP> op, optional<CommandSelector<Player>> res) {
	optional<xuid_t> dstid;
	if (res.set && ori.getPermissionsLevel() > 0) {
		if (!res.val().results(ori).empty()) {
			dstid = PlayerDB::getXuid(res.val().results(ori).begin().operator*()->getRealName());
		}
	}
	else {
		dstid = PlayerDB::getXuid(ori.getName());
	}
	if (!dstid.Set()) {
		outp.error(tr("money.no.target"));
		return false;
	}
	switch (op)
	{
	case query:
		outp.addMessage("Money: " + std::to_string(LLMoneyGet(dstid.val())));
		break;
	case hist:
		outp.addMessage(LLMoneyGetHist(dstid.val()));
		break;
	}
	return true;
}
*/

/*
bool oncmd_money2_sel(CommandOrigin const& ori, CommandOutput& outp, MyEnum<MONEYOP_pay> op, CommandSelector<Player> res, int val) {
	if (res.results(ori).empty()) {
		outp.error(tr("money.no.target"));
		return false;
	}
	for (auto resu : res.results(ori)) {
		optional<xuid_t> dstxuid, myuid;
		dstxuid = PlayerDB::getXuid(resu->getRealName());
		if (!dstxuid.Set()) {
			outp.error(tr("money.no.target"));
			return false;
		}
		switch (op)
		{
		case pay:
		{
			if (val <= 0) {
				outp.error(tr("money.invalid.arg"));
				return false;
			}
			myuid = PlayerDB::getXuid(ori.getName());
			if (!myuid.Set()) {
				outp.error(tr("money.no.target"));
				return false;
			}
			if (LLMoneyTrans(myuid.val(), dstxuid.val(), val, "money pay")) {
				money_t fee = (money_t)(val * MoneyFee);
				if (fee)
					LLMoneyTrans(dstxuid.val(), 0, fee, "money pay fee");
				outp.success("pay success");
				return true;
			}
			else {
				outp.error(tr("money.not.enough"));
				return false;
			}
		}
		break;
		case set:
			if (ori.getPermissionsLevel() < 1) {
				outp.error(tr("money.no.perm"));
				return false;
			}
			if (LLMoneySet(dstxuid.val(), val)) {
				outp.success("set success");
				return true;
			}
			else {
				outp.error(tr("money.invalid.arg"));
				return false;
			}
			break;
		case add:
			if (ori.getPermissionsLevel() < 1) {
				outp.error(tr("money.no.perm"));
				return false;
			}
			if (LLMoneyAdd(dstxuid.val(), val)) {
				outp.success("add success");
				return true;
			}
			else {
				outp.error(tr("money.invalid.arg"));
				return false;
			}
			break;
		case reduce:
			if (ori.getPermissionsLevel() < 1) {
				outp.error(tr("money.no.perm"));
				return false;
			}
			if (LLMoneyReduce(dstxuid.val(), val)) {
				return true;
			}
			else {
				outp.error(tr("money.invalid.arg"));
				return false;
			}
			break;
		}
	}
	return true;
}
*/


class MoneyCommand : public Command {
	enum MoneyOP :int {
		query = 1,
		hist = 2,
		pay = 3,
		set = 4,
		add = 5,
		reduce = 6,
		purge = 7
	} op;
	string dst;
	bool dst_isSet;
	bool difftime_isSet;
	int moneynum;
	int difftime;
public:
	void execute(CommandOrigin const& ori, CommandOutput& outp) const {
		optional<xuid_t> dstid;
		optional<xuid_t> dstxuid, myuid;
		switch (op)
		{
		case query:
		case hist:
			if (dst_isSet && ori.getPermissionsLevel() > 0) {
				dstid = PlayerDB::getXuid(dst);
			}
			else {
				dstid = PlayerDB::getXuid(ori.getName());
			}
			if (!dstid.Set()) {
				outp.error(tr("money.no.target"));
				return;
			}
			break;
		case pay:
		case set:
		case add:
		case reduce:
			dstxuid = PlayerDB::getXuid(dst);
			if (!dstxuid.Set()) {
				outp.error(tr("money.no.target"));
				return;
			}
			break;
		case purge:
			if (ori.getPermissionsLevel() < 1) {
				outp.error(tr("money.no.perm"));
				return;
			}
			break;
		}
		switch (op)
		{
		case query:
			outp.addMessage("Money: " + std::to_string(LLMoneyGet(dstid.val())));
			break;
		case hist:
			outp.addMessage(LLMoneyGetHist(dstid.val()));
			break;
		case pay:
		{
			if (moneynum <= 0) {
				outp.error(tr("money.invalid.arg"));
			}
			myuid = PlayerDB::getXuid(ori.getName());
			if (!myuid.Set()) {
				outp.error(tr("money.no.target"));
			}
			if (LLMoneyTrans(myuid.val(), dstxuid.val(), moneynum, "money pay")) {
				money_t fee = (money_t)(moneynum * MoneyFee);
				if (fee)
					LLMoneyTrans(dstxuid.val(), 0, fee, "money pay fee");
				outp.success("pay success");
			}
			else {
				outp.error(tr("money.not.enough"));
			}
		}
		break;
		case set:
			if (ori.getPermissionsLevel() < 1) {
				outp.error(tr("money.no.perm"));
			}
			if (LLMoneySet(dstxuid.val(), moneynum)) {
				outp.success("set success");
			}
			else {
				outp.error(tr("money.invalid.arg"));
			}
			break;
		case add:
			if (ori.getPermissionsLevel() < 1) {
				outp.error(tr("money.no.perm"));
			}
			if (LLMoneyAdd(dstxuid.val(), moneynum)) {
				outp.success("add success");
			}
			else {
				outp.error(tr("money.invalid.arg"));
			}
			break;
		case reduce:
			if (ori.getPermissionsLevel() < 1) {
				outp.error(tr("money.no.perm"));
			}
			if (LLMoneyReduce(dstxuid.val(), moneynum)) {
			}
			else {
				outp.error(tr("money.invalid.arg"));
			}
			break;
		case purge:
			if (difftime_isSet)
				LLMoneyClearHist(difftime);
			else
				LLMoneyClearHist(0);
		}
		return;
	}
	static void setup(CommandRegistry* registry) {

		//registerCommand
		registry->registerCommand(
			"money", "money system", CommandPermissionLevel::Any, { (CommandFlagValue)0 }, { (CommandFlagValue)0x80 });
		//addEnum
		registry->addEnum<MoneyOP>("MoneyOP1", { { "query",MoneyOP::query},{ "hist",MoneyOP::hist}});
		registry->addEnum<MoneyOP>("MoneyOP2", { { "add",MoneyOP::add},{ "pay",MoneyOP::pay },{"reduce",MoneyOP::reduce},{"set",MoneyOP::set}});
		registry->addEnum<MoneyOP>("MoneyOP3", { { "purge",MoneyOP::purge} });

		//registerOverload
		registry->registerOverload<MoneyCommand>(
			"money",
			makeMandatory<CommandParameterDataType::ENUM>(&MoneyCommand::op, "optional", "MoneyOP1"),
			makeOptional(&MoneyCommand::dst, "target", &MoneyCommand::dst_isSet));
		registry->registerOverload<MoneyCommand>(
			"money",
			makeMandatory<CommandParameterDataType::ENUM>(&MoneyCommand::op, "optional", "MoneyOP2"),
			makeMandatory(&MoneyCommand::dst, "target"),
			makeMandatory(&MoneyCommand::moneynum, "num"));
		registry->registerOverload<MoneyCommand>(
			"money",
			makeMandatory<CommandParameterDataType::ENUM>(&MoneyCommand::op, "optional", "MoneyOP3"),
			makeOptional(&MoneyCommand::difftime, "time", &MoneyCommand::difftime_isSet));
	}
};

void entry() {
	std::filesystem::create_directory("plugins\\LLMoney");
	std::filesystem::create_directory("plugins\\LLMoney\\langpack");
	if (!initDB()) {
		exit(1);
	}
	Logger::setTitle("Money");
	Translation::load("plugins\\LLMoney\\langpack\\money.json");
	Event::RegCmdEvent::subscribe([](const Event::RegCmdEvent& ev) {
		MoneyCommand::setup(ev.mCommandRegistry);
		return true;
		});
	try {
		ConfigJReader jr("plugins\\LLMoney\\money.json");
		int defmoney;
		jr.bind("def_money", defmoney, 0);
		jr.bind("pay_tax", MoneyFee, .0);
		DEF_MONEY = defmoney;
	}
	catch (string e) {
		Logger::Error("Json error: {}", e);
		throw 0;
	}
	Logger::Info("Loaded version: {}", _ver);
}
