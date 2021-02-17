#include "pch.h"
#include <loader/Loader.h>
#include <iostream>
#include "rapidjson/rapidjson.h"
#include "rapidjson/document.h"
#include "mc/Player.h"
#include "mc/item.h"
#include <api/types/types.h>
#include <api/types/helper.h>
#include <mc/BlockSource.h>
#include <mc/Block.h>
#include <mc/OffsetHelper.h>
#include <api/commands.h>
#include <map>
#include "pch.h"
#include<fstream>
#include<streambuf>
#include<api/Basic_Event.h>
#include<api/xuidreg.h>
#include <llmoney.h>
double MoneyFee;
LangPack LP("langpack/money.json");
static Logger LOG(stdio_commit{ "[MONEY] " });
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
	using namespace Money;
	optional<xuid_t> dstid;
	if (dst.set && ori.getPermissionsLevel() > 0) {
		dstid = XIDREG::str2id(dst.val());
	}
	else {
		dstid = XIDREG::str2id(ori.getName());
	}
	if (!dstid.Set()) {
		outp.error(_TRS("money.no.target"));
		return false;
	}
	switch (op)
	{
	case query:
		outp.addMessage("Money: " + std::to_string(getMoney(dstid.val())));
		break;
	case hist:
		outp.addMessage(getTransHist(dstid.val()));
		break;
	}
	return true;
}

bool oncmd_money2(CommandOrigin const& ori, CommandOutput& outp, MyEnum<MONEYOP_pay> op, string const& dst, int val) {
	using namespace Money;
	optional<xuid_t> dstxuid, myuid;
	dstxuid = XIDREG::str2id(dst);
	if (!dstxuid.Set()) {
		outp.error(_TRS("money.no.target"));
		return false;
	}
	switch (op)
	{
	case pay:
	{
		if (val <= 0) {
			outp.error(_TRS("money.invalid.arg"));
			return false;
		}
		myuid = XIDREG::str2id(ori.getName());
		if (!myuid.Set()) {
			outp.error(_TRS("money.no.target"));
			return false;
		}
		if (createTrans(myuid.val(), dstxuid.val(), val, "money pay")) {
			money_t fee = (money_t)(val * MoneyFee);
			if (fee)
				createTrans(dstxuid.val(), 0, fee, "money pay fee");
			outp.success("pay success");
			return true;
		}
		else {
			outp.error(_TRS("money.not.enough"));
			return false;
		}
	}
	break;
	case set:
		if (ori.getPermissionsLevel() < 1) {
			outp.error(_TRS("money.no.perm"));
			return false;
		}
		if (setMoney(dstxuid.val(), val)) {
			outp.success("set success");
			return true;
		}
		else {
			outp.error(_TRS("money.invalid.arg"));
			return false;
		}
		break;
	case add:
		if (ori.getPermissionsLevel() < 1) {
			outp.error(_TRS("money.no.perm"));
			return false;
		}
		if (createTrans(0, dstxuid.val(), val, "money add")) {
			outp.success("add success");
			return true;
		}
		else {
			outp.error(_TRS("money.invalid.arg"));
			return false;
		}
		break;
	case reduce:
		if (ori.getPermissionsLevel() < 1) {
			outp.error(_TRS("money.no.perm"));
			return false;
		}
		if (createTrans(dstxuid.val(), 0, val, "money reduce")) {
			return true;
		}
		else {
			outp.error(_TRS("money.invalid.arg"));
			return false;
		}
		break;
	}
	return true;
}

bool oncmd_money2_p(CommandOrigin const& ori, CommandOutput& outp, MyEnum<MONEYOP_pay> op, CommandSelector<Player>& dst, int val) {
	auto res = dst.results(ori);
	if (!Command::checkHasTargets(res, outp)) return false;
	bool fg = true;
	for (auto i : res) {

	}
	return fg;
}
bool oncmd_money3_p(CommandOrigin const& ori, CommandOutput& outp, MyEnum<MONEYOP_PURGE> op, optional<int>& difftime) {
	if (difftime.Set())
		Money::purgeHist(difftime.val());
	else
		Money::purgeHist(0);
	return true;
}


void entry() {
	if (!initDB()) {
		exit(1);
	}
		Event::addEventListener([](RegCmdEV ev) {
		CMDREG::SetCommandRegistry(ev.CMDRg);
		MakeCommand("money", "money", 0);
		MakeCommand("money_op", "money_op", 1);
		CEnum<MONEYOP> _1("type", { "query","hist" });
		CEnum<MONEYOP_pay> _2("type2", { "pay","set","add","reduce" });
		CEnum<MONEYOP_PURGE> _3("mpurge", { "purge" });
		CmdOverload(money, oncmd_money, "op", "target");
		CmdOverload(money, oncmd_money2, "op", "target1", "money");
		CmdOverload(money_op, oncmd_money2_p, "op", "target2", "money");
		CmdOverload(money_op, oncmd_money3_p, "purge", "difftime");
		});
	try {
		ConfigJReader jr("config/money.json");
		int defmoney;
		jr.bind("def_money", defmoney, 0);
		jr.bind("pay_tax", MoneyFee, .0);
		DEF_MONEY = defmoney;
	}
	catch (string e) {
		LOG.p<LOGLVL::Error>("json error", e);
		throw 0;
	}
}