#include <Global.h>
#include <MC/Player.hpp>
#include <MC/ServerPlayer.hpp>
#include <regCommandAPI.h>
#include <EventAPI.h>
#include "LLMoney.h"
#include "Money.h"
#include <TranslationAPI.h>
#include <Dedicated/JsonLoader.h>
#include <SQLiteCpp/SQLiteCpp.h>

using namespace RegisterCommandHelper;

Logger logger("LLMoney");
std::string LANGUAGE = "en-us";

double MoneyFee;

bool initDB();

extern money_t DEF_MONEY;

class MoneyCommand : public Command {
    enum MoneyOP : int {
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
    void execute(CommandOrigin const &ori, CommandOutput &outp) const {
        std::string dstxuid, myuid;
        switch (op) {
            case query:
            case hist:
                if (dst_isSet && ori.getPermissionsLevel() > 0) {
                    dstxuid = PlayerInfo::getXuid(dst);
                } else {
                    dstxuid = PlayerInfo::getXuid(ori.getName());
                }
                if (dstxuid == "") {
                    outp.error(tr("money.no.target"));
                    return;
                }
                break;
            case pay:
            case set:
            case add:
            case reduce:
                dstxuid = PlayerInfo::getXuid(dst);
                if (dstxuid == "") {
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
        switch (op) {
            case query:
                outp.addMessage("Balance: " + std::to_string(LLMoneyGet(dstxuid)));
                break;
            case hist:
                outp.addMessage(LLMoneyGetHist(dstxuid));
                break;
            case pay: {
                if (moneynum <= 0) {
                    outp.error(tr("money.invalid.arg"));
                    return;
                }
                myuid = ori.getPlayer()->getXuid();
                if (LLMoneyTrans(myuid, dstxuid, moneynum, "money pay")) {
                    money_t fee = (money_t) (moneynum * MoneyFee);
                    if (fee)
                        LLMoneyTrans(dstxuid, "", fee, "money pay fee");
                    outp.success("Pay successfully");
                } else {
                    outp.error(tr("money.not.enough"));
                }
                return;
            }
                break;
            case set:
                if (ori.getPermissionsLevel() < 1) {
                    outp.error(tr("money.no.perm"));
                    return;
                }
                if (LLMoneySet(dstxuid, moneynum)) {
                    outp.success("Set successfully");
                } else {
                    outp.error(tr("money.invalid.arg"));
                }
                break;
            case add:
                if (ori.getPermissionsLevel() < 1) {
                    outp.error(tr("money.no.perm"));
                    return;
                }
                if (LLMoneyAdd(dstxuid, moneynum)) {
                    outp.success("Add successfully");
                } else {
                    outp.error(tr("money.invalid.arg"));
                }
                break;
            case reduce:
                if (ori.getPermissionsLevel() < 1) {
                    outp.error(tr("money.no.perm"));
                    return;
                }
                if (LLMoneyReduce(dstxuid, moneynum)) {
                    outp.success(tr("Reduce successfully"));
                } else {
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
                std::map<std::string, money_t> mapTemp = LLMoneyRanking();
                outp.addMessage("===== Ranking =====");
                for (std::pair<std::string, money_t> mp : mapTemp) {
                    outp.addMessage(PlayerInfo::fromXuid(mp.first) + "  " + std::to_string(mp.second));
                }
                outp.success("===================");
        }
        return;
    }

    static void setup(CommandRegistry *registry) {

        //registerCommand
        registry->registerCommand(
                "money", "Economy system", CommandPermissionLevel::Any, {(CommandFlagValue) 0},
                {(CommandFlagValue) 0x80});
        //addEnum
        registry->addEnum<MoneyOP>("MoneyOP1", {{"query", MoneyOP::query},
                                                {"hist",  MoneyOP::hist},
                                                {"top", MoneyOP::top}});
        registry->addEnum<MoneyOP>("MoneyOP2", {{"add",    MoneyOP::add},
                                                {"pay",    MoneyOP::pay},
                                                {"reduce", MoneyOP::reduce},
                                                {"set",    MoneyOP::set}});
        registry->addEnum<MoneyOP>("MoneyOP3", {{"purge", MoneyOP::purge}});

        //registerOverload
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

class MoneySCommand : public Command {
    enum MoneyOP : int {
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
    void execute(CommandOrigin const &ori, CommandOutput &outp) const {
        optional<std::string> dstxuid;
        std::string myuid;
        switch (op) {
            case query:
            case hist:
                if (dst_isSet) {
                    if (ori.getPermissionsLevel() > 0) {
                        if (!player.results(ori).empty()) {
                            dstxuid = PlayerInfo::getXuid(player.results(ori).begin().operator*()->getRealName());
                        }
                    }
                } else {
                    dstxuid = PlayerInfo::getXuid(ori.getName());
                }
                if (dstxuid.val() == "") {
                    outp.error(tr("money.no.target"));
                    return;
                }
                break;
            case pay:
            case set:
            case add:
            case reduce:
                if (player.results(ori).empty()) {
                    outp.error(tr("money.no.target"));
                    return;
                }
                for (auto resu: player.results(ori)) {
                    dstxuid = PlayerInfo::getXuid(resu->getRealName());
                    if (!dstxuid.Set()) {
                        outp.error(tr("money.no.target"));
                        return;
                    }
                }
                break;
        }
        switch (op) {
            case query:
                outp.addMessage("Balance: " + std::to_string(LLMoneyGet(dstxuid.val())));
                break;
            case hist:
                outp.addMessage(LLMoneyGetHist(dstxuid.val()));
                break;
            case pay: {
                if (moneynum <= 0) {
                    outp.error(tr("money.invalid.arg"));
                    return;
                }
                myuid = PlayerInfo::getXuid(ori.getName());
                if (myuid == "") {
                    outp.error(tr("money.no.target"));
                    return;
                }
                if (LLMoneyTrans(myuid, dstxuid.val(), moneynum, "money pay")) {
                    money_t fee = (money_t) (moneynum * MoneyFee);
                    if (fee)
                        LLMoneyTrans(dstxuid.val(), "", fee, "money pay fee");
                    outp.success("Pay successfully");
                } else {
                    outp.error(tr("money.not.enough"));
                }
            }
                break;
            case set:
                if (ori.getPermissionsLevel() < 1) {
                    outp.error(tr("money.no.perm"));
                    return;
                }
                if (LLMoneySet(dstxuid.val(), moneynum)) {
                    outp.success("Set successfully");
                } else {
                    outp.error(tr("money.invalid.arg"));
                }
                break;
            case add:
                if (ori.getPermissionsLevel() < 1) {
                    outp.error(tr("money.no.perm"));
                    return;
                }
                if (LLMoneyAdd(dstxuid.val(), moneynum)) {
                    outp.success("Add successfully");
                } else {
                    outp.error(tr("money.invalid.arg"));
                }
                break;
            case reduce:
                if (ori.getPermissionsLevel() < 1) {
                    outp.error(tr("money.no.perm"));
                    return;
                }
                if (LLMoneyReduce(dstxuid.val(), moneynum)) {
                    outp.success("Reduce successfully");
                } else {
                    outp.error(tr("money.invalid.arg"));
                }
                break;
        }
        return;
    }

    static void setup(CommandRegistry *registry) {
        //registerCommand
        registry->registerCommand(
                "money_s", "Economy system(Selector)", CommandPermissionLevel::Any, {(CommandFlagValue) 0},
                {(CommandFlagValue) 0x80});

        //addEnum
        registry->addEnum<MoneyOP>("MoneyOP1", {{"query", MoneyOP::query},
                                                {"hist",  MoneyOP::hist}});
        registry->addEnum<MoneyOP>("MoneyOP2", {{"add",    MoneyOP::add},
                                                {"pay",    MoneyOP::pay},
                                                {"reduce", MoneyOP::reduce},
                                                {"set",    MoneyOP::set}});

        //registerOverload
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

void entry() {
    if (!initDB()) {
        return;
    }
    Event::RegCmdEvent::subscribe([](const Event::RegCmdEvent &ev) {
        MoneyCommand::setup(ev.mCommandRegistry);
        MoneySCommand::setup(ev.mCommandRegistry);
        return true;
    });
    try {
        ConfigJReader jr("plugins\\LLMoney\\money.json");
        int defmoney;
        jr.bind("language", LANGUAGE);
        jr.bind("def_money", defmoney, 0);
        jr.bind("pay_tax", MoneyFee, .0);
        DEF_MONEY = defmoney;
    }
    catch (string e) {
        Logger("LLMoney").error("Json error: {}", e);
        throw 0;
    }
    Translation::load("plugins\\LLMoney\\langpack\\" + LANGUAGE + ".json");
    Logger("LLMoney").info("Loaded version: {}", LLMONEY_VERSION.toString());
}
