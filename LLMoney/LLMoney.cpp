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

double MoneyFee;
bool initDB();

extern money_t DEF_MONEY;
enum MONEYOP :int {
	query = 1,
	hist = 2,
};
enum MONEYOP_pay :int {
	pay = 1,
	set = 2,
	add = 3,
	reduce = 4
};
enum MONEYOP_PURGE :int {
	purge = 1
};
bool oncmd_money(CommandOrigin const& ori, CommandOutput& outp, MyEnum<MONEYOP> op, optional<string>& dst) {
	optional<xuid_t> dstid;
	if (dst.set && ori.getPermissionsLevel() > 0) {
		dstid = PlayerDB::getXuid(dst.val());
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

bool oncmd_money_sel(CommandOrigin const& ori, CommandOutput& outp, MyEnum<MONEYOP> op, optional<CommandSelector<Player>>& res) {
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

bool oncmd_money2(CommandOrigin const& ori, CommandOutput& outp, MyEnum<MONEYOP_pay> op, string const& dst, int val) {
	optional<xuid_t> dstxuid, myuid;
	dstxuid = PlayerDB::getXuid(dst);
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
	return true;
}

bool oncmd_money2_sel(CommandOrigin const& ori, CommandOutput& outp, MyEnum<MONEYOP_pay> op, CommandSelector<Player>& res, int val) {
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

bool oncmd_money3_p(CommandOrigin const& ori, CommandOutput& outp, MyEnum<MONEYOP_PURGE> op, optional<int>& difftime) {
	if (ori.getPermissionsLevel() < 1) {
		outp.error(tr("money.no.perm"));
		return false;
	}
	if (difftime.Set())
		LLMoneyClearHist(difftime.val());
	else
		LLMoneyClearHist(0);
	return true;
}


void entry() {
	std::filesystem::create_directory("plugins\\LLMoney");
	std::filesystem::create_directory("plugins\\LLMoney\\langpack");
	if (!initDB()) {
		exit(1);
	}
	Logger::setTitle("Money");
	Translation::load("plugins\\LLMoney\\langpack\\money.json");
	Event::addEventListener([](RegCmdEvent ev) {
		MakeCommand("money", "money", 0);
		MakeCommand("money_s", "money(CommandSelector)", 1);
		CEnum<MONEYOP> _1("type", { "query","hist" });
		CEnum<MONEYOP_pay> _2("type2", { "pay","set","add","reduce" });
		CEnum<MONEYOP_PURGE> _3("mpurge", { "purge" });
		CmdOverload(money, oncmd_money, "op", "target");
		CmdOverload(money, oncmd_money2, "op", "target1", "money");
		CmdOverload(money, oncmd_money3_p, "purge", "difftime");
		CmdOverload(money_s, oncmd_money_sel, "op", "target");
		CmdOverload(money_s, oncmd_money2_sel, "op", "target1", "money");
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
