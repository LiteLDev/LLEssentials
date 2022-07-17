#include <EventAPI.h>
#include <stddef.h>
#include <string>
#include "Helper.h"
#include <string_view>
#include <MC/ExtendedCertificate.hpp>
#include <MC/NetworkIdentifier.hpp>
#include <MC/ServerNetworkHandler.hpp>
#include <MC/Item.hpp>
#include <SendPacketAPI.h>
#include <MC/MinecraftPackets.hpp>
#include "settings.h"
#include <thread>
#include <regCommandAPI.h>
#include <ctime>
#include <chrono>
#include <unordered_set>
#include <KVDBAPI.h>
#include <PlayerInfoAPI.h>
#include <Utils/ViewHelper.h>
#include <MC/Certificate.hpp>
#include <Utils/VarInt.h>
#include <Utils/PlayerMap.h>
#include "I18nAPI.h"
#include <MC/ItemStack.hpp>
#include <MC/ServerPlayer.hpp>
#include <MC/Level.hpp>
#include <DynamicCommandAPI.h>
#include <ScheduleAPI.h>

std::unique_ptr<KVDB> db;
playerMap<string> ORIG_NAME;
std::unordered_map<string, string> CNAME;
extern unsigned short Tick_per_second;
extern unsigned short Tick_per_minute;

void loadCNAME() {
	db = KVDB::create("plugins/LLHelper/data", false);
	db->iter([](string_view k, string_view v) {
		if (!k._Starts_with("b_"))
			CNAME.emplace(k, v);
		return true;
		});
}

void addBanEntry(string const& entry, time_t timediff) {
	time_t next = timediff == 0 ? 0 : (time(0) + timediff);
	db->put("b_" + entry, to_view(next));
}

optional<time_t> getBanEntry(string const& entry) {
	string val;
	if (db->get("b_" + entry, val)) return { *(time_t*)val.data() };
	return {};
}

void removeBanEntry(string const& entry) {
	db->del("b_" + entry);
}

class GmodeCommand : public Command {
	CommandSelector<Player> pl;
	int mode;
public:
	void execute(CommandOrigin const& ori, CommandOutput& outp) const {
		auto res = pl.results(ori);
		if (!Command::checkHasTargets(res, outp)) return;
		for (auto i : res) {
			i->setPlayerGameType((GameType)mode);
		}
		outp.success(tr("gmode.success"));
	}

	static void setup(CommandRegistry* registry) {
		using RegisterCommandHelper::makeMandatory;
		using RegisterCommandHelper::makeOptional;
		registry->registerCommand("gmode", "Switch your gamemode", CommandPermissionLevel::GameMasters,
			{ (CommandFlagValue)0 }, { (CommandFlagValue)0x80 });
		registry->registerOverload<GmodeCommand>("gmode", makeMandatory(&GmodeCommand::pl, "target"),
			makeMandatory(&GmodeCommand::mode, "mode"));
	}
};

class BanCommand : public Command {
	enum BANOP : int {
		ban = 1,
		unban = 2,
		banip = 3,
		list = 4
	} op;
	std::string entry;
	bool time_isSet;
	int time;
public:
	void execute(CommandOrigin const& ori, CommandOutput& outp) const {
		switch (op) {
		case BANOP::banip: {
			addBanEntry(entry, time_isSet ? time : 0);
			outp.success(entry + tr("ban.banip.success"));
			return;
		}
		case BANOP::ban: {
			std::string xuid = PlayerInfo::getXuid(entry);
			if (xuid == "") {
				outp.error("Player not found");
				return;
			}
			addBanEntry(xuid, time_isSet ? time : 0);
			Level::runcmdEx("skick " + entry);
			outp.success(entry + tr("ban.ban.success"));
			return;
		}
					   break;
		case BANOP::unban: {
			if (getBanEntry(entry).set) {
				removeBanEntry(entry);
				outp.success(entry + tr("ban.unban.success"));
			}
			else {
				std::string XID = PlayerInfo::getXuid(entry);
				if (XID == "") {
					outp.error(tr("ban.unban.error"));
				}
				else {
					removeBanEntry(XID);
					outp.success(entry + tr("ban.unban.success"));
					return;
				}
			}
		}
						 break;
		case BANOP::list: {
			db->iter([&](string_view key, string_view val) -> bool {
				if (key._Starts_with("b_")) {
					string banned{ key.substr(2) };
					if (banned.find('.') != banned.npos) {
						outp.addMessage(banned + " " + std::to_string(*(time_t*)val.data()));
					}
					else {
						xuid_t xid;
						std::stringstream ss{ banned };
						ss >> xid;
						outp.addMessage(banned + " (" + PlayerInfo::fromXuid(xid) + ") " +
							std::to_string(*(time_t*)val.data()));
					}
				}
				});
			outp.success(tr("ban.list.success"));
			return;
		}
						break;
		default:
			break;
		}
	}

	static void setup(CommandRegistry* registry) {
		using RegisterCommandHelper::makeMandatory;
		using RegisterCommandHelper::makeOptional;
		registry->registerCommand("ban", "Ban a player", CommandPermissionLevel::GameMasters, { (CommandFlagValue)0 },
			{ (CommandFlagValue)0x80 });
		registry->addEnum<BANOP>("BANOP", { {"ban",   BANOP::ban},
										   {"unban", BANOP::unban},
										   {"banip", BANOP::banip} });
		registry->addEnum<BANOP>("BANOP2", { {"list", BANOP::list} });
		registry->registerOverload<BanCommand>("ban",
			makeMandatory<CommandParameterDataType::ENUM>(&BanCommand::op, "OP",
				"BANOP"),
			makeMandatory(&BanCommand::entry, "target"),
			makeOptional(&BanCommand::time, "time", &BanCommand::time_isSet));
		registry->registerOverload<BanCommand>("ban",
			makeMandatory<CommandParameterDataType::ENUM>(&BanCommand::op, "OP2",
				"BANOP2"));
	}
};

class SkickCommand : public Command {
	std::string target;
public:
	void execute(CommandOrigin const& ori, CommandOutput& outp) const {
		std::vector<Player*> plist = Level::getAllPlayers();
		Player* pl = nullptr;
		for (auto p : plist) {
			if (p->getRealName() == target) {
				pl = p;
				break;
			}
		}
		if (pl) {
			pl->kick("You are kicked by admin");
			outp.success(target + tr("skick.success"));
		}
		else {
			outp.error(target + " not found");
		}
	}

	static void setup(CommandRegistry* registry) {
		using RegisterCommandHelper::makeMandatory;
		using RegisterCommandHelper::makeOptional;
		registry->registerCommand("skick", "Force kick", CommandPermissionLevel::GameMasters, { (CommandFlagValue)0 },
			{ (CommandFlagValue)0x80 });
		registry->registerOverload<SkickCommand>("skick", makeMandatory(&SkickCommand::target, "target"));
	}
};

class VanishCommand : public Command {
public:
	void execute(CommandOrigin const& ori, CommandOutput& outp) const {
		ServerPlayer* sp = ori.getPlayer();
		BinaryStream bs;
		bs.writeUnsignedVarInt64(ZigZag(sp->getUniqueID().id));
		auto pkt = MinecraftPackets::createPacket(MinecraftPacketIds::RemoveActor);
		pkt->read(bs);
		std::vector<Player*> plist = Level::getAllPlayers();
		for (auto p : plist) {
			if (p != sp) {
				ServerPlayer* spp = (ServerPlayer*)p;
				spp->sendNetworkPacket(*pkt);
			}
		}
		outp.addMessage(tr("vanish.success"));
	}

	static void setup(CommandRegistry* registry) {
		using RegisterCommandHelper::makeMandatory;
		using RegisterCommandHelper::makeOptional;
		registry->registerCommand("vanish", "Hide yourself", CommandPermissionLevel::GameMasters,
			{ (CommandFlagValue)0 }, { (CommandFlagValue)0x80 });
		registry->registerOverload<VanishCommand>("vanish");
	}
};

class CrashCommand : public Command {
	CommandSelector<Player> pl;
public:
	void execute(CommandOrigin const& ori, CommandOutput& outp) const {
		auto res = pl.results(ori);
		for (auto p : res) {
			p->crashClient();
		}
		outp.success("Crashed");
	}

	static void setup(CommandRegistry* registry) {
		using RegisterCommandHelper::makeMandatory;
		using RegisterCommandHelper::makeOptional;
		registry->registerCommand("crash", "Crash player's client", CommandPermissionLevel::GameMasters,
			{ (CommandFlagValue)0 }, { (CommandFlagValue)0x80 });
		registry->registerOverload<CrashCommand>("crash", makeMandatory(&CrashCommand::pl, "player"));
	}
};

class CnameCommand : public Command {
	enum CNAMEOP : int {
		set = 1,
		remove = 2
	} op;
	std::string src;
	bool name_isSet;
	std::string name;

public:
	void execute(CommandOrigin const& ori, CommandOutput& outp) const {
		std::vector<Player*> pList = Level::getAllPlayers();
		Player* player = nullptr;
		for (auto p : pList) {
			if (p->getRealName() == src) {
				player = p;
				break;
			}
		}
		if (op == CNAMEOP::set) {
			if (!name_isSet) {
				outp.error(tr("cname.set.null"));
				return;
			}
			std::string str = name;
			for (int i = 0; i < str.size(); ++i) {
				if (str[i] == '^') str[i] = '\n';
			}
			CNAME[src] = str;
			db->put(src, str);
			if (!player) {
				outp.error(tr("cname.set.notonline"));
				return;
			}
			outp.success(tr("cname.set.success"));
			player->setName(str);
			ORIG_NAME[(ServerPlayer*)player] = player->getName().c_str();
		}
		if (op == CNAMEOP::remove) {
			CNAME.erase(src);
			db->del(src);
			if (!player) {
				outp.error(tr("cname.rm.notonline"));
				return;
			}
			outp.success(tr("cname.rm.success"));
			player->setName(src);
			ORIG_NAME._map.erase((ServerPlayer*)player);
		}
	}

	static void setup(CommandRegistry* registry) {
		using RegisterCommandHelper::makeMandatory;
		using RegisterCommandHelper::makeOptional;
		registry->registerCommand("cname", "Custom name", CommandPermissionLevel::GameMasters, { (CommandFlagValue)0 },
			{ (CommandFlagValue)0x80 });
		registry->addEnum<CNAMEOP>("CNAMEOP", { {"set", CNAMEOP::set},
											   {"rm",  CNAMEOP::remove} });
		registry->registerOverload<CnameCommand>("cname",
			makeMandatory<CommandParameterDataType::ENUM>(&CnameCommand::op,
				"optinal", "CNAMEOP"),
			makeMandatory(&CnameCommand::src, "player"),
			makeOptional(&CnameCommand::name, "name", &CnameCommand::name_isSet));
	}
};

class TransferCommand : public Command {
	CommandSelector<Player> p;
	std::string host;
	int port;
	bool port_isSet;

public:
	void execute(CommandOrigin const& ori, CommandOutput& outp) const {
		int P = port_isSet ? port : 19132;
		auto res = p.results(ori);
		if (!Command::checkHasTargets(res, outp)) return;
		for (auto i : res) {
			i->sendTransferPacket(host, P);
		}
	}

	static void setup(CommandRegistry* registry) {
		using RegisterCommandHelper::makeMandatory;
		using RegisterCommandHelper::makeOptional;
		registry->registerCommand("transfer", "Transfer player to another server", CommandPermissionLevel::GameMasters,
			{ (CommandFlagValue)0 }, { (CommandFlagValue)0x80 });
		registry->registerOverload<TransferCommand>("transfer",
			makeMandatory(&TransferCommand::p, "player"),
			makeMandatory(&TransferCommand::host, "IP"),
			makeOptional(&TransferCommand::port, "port",
				&TransferCommand::port_isSet));
	}
};

class HelperCommand : public Command {
	enum HelperOP : int {
		reload = 0
	} action;

public:
	void execute(CommandOrigin const& ori, CommandOutput& outp) const {
		switch (action) {
		case HelperOP::reload:
			loadCfg();
			outp.success(tr("hreload.success"));
			break;
		}

	}

	static void setup(CommandRegistry* registry) {
		using RegisterCommandHelper::makeMandatory;
		using RegisterCommandHelper::makeOptional;
		registry->registerCommand("helper", "LLHelper", CommandPermissionLevel::GameMasters, { (CommandFlagValue)0 },
			{ (CommandFlagValue)0x80 });
		registry->addEnum<HelperOP>("HelperOP", { {"reload", HelperOP::reload} });
		registry->registerOverload<HelperCommand>("helper",
			makeMandatory<CommandParameterDataType::ENUM>(&HelperCommand::action,
				"optinal", "HelperOP"));
	}
};

class ItemCommand : public Command {
public:
	void execute(CommandOrigin const& ori, CommandOutput& outp) const {
		ServerPlayer* wp = ori.getPlayer();
		if (wp) {
			const ItemStack* item = &wp->getCarriedItem();
			std::string itemName = "Air";
			if (item->getId() != 0) {
				itemName = item->getItem()->getSerializedName();
			}
			outp.success(itemName + " " + std::to_string(item->getId()));
		}
		else {
			outp.error("You are not a player");
			return;
		}
	}

	static void setup(CommandRegistry* registry) {
		using RegisterCommandHelper::makeMandatory;
		using RegisterCommandHelper::makeOptional;
		registry->registerCommand("item", "Show item information on your hand", CommandPermissionLevel::Any,
			{ (CommandFlagValue)0 }, { (CommandFlagValue)0x80 });
		registry->registerOverload<ItemCommand>("item");
	}
};

class RunasCommand : public Command {
	CommandSelector<Player> pl;
	std::string cmd;
public:
	void execute(CommandOrigin const& ori, CommandOutput& outp) const {
		auto res = pl.results(ori);
		for (auto p : res) {
			p->runcmd(cmd);
		}
		outp.success("Executed");
	}

	static void setup(CommandRegistry* registry) {
		using RegisterCommandHelper::makeMandatory;
		using RegisterCommandHelper::makeOptional;
		registry->registerCommand("runas", "Run command as a player", CommandPermissionLevel::GameMasters,
			{ (CommandFlagValue)0 }, { (CommandFlagValue)0x80 });
		registry->registerOverload<RunasCommand>("runas", makeMandatory(&RunasCommand::pl, "player"),
			makeMandatory(&RunasCommand::cmd, "command"));
	}
};

std::string TpsColor(unsigned short tps) {
	if (tps < 15)
		return "§6" + std::to_string(tps);
	if (tps <= 10)
		return "§c" + std::to_string(tps);
	return "§a" + std::to_string(tps);
}

void TpsCommand() {
	using ParamType = DynamicCommand::ParameterType;
	using Param = DynamicCommand::ParameterData;
	DynamicCommand::setup(
		"tps",        // command name
		"Query server tps", // command description
		{},
		{},
		{ {}, },
		// dynamic command callback
		[](DynamicCommand const& command, CommandOrigin const& origin, CommandOutput& output,
			std::unordered_map<std::string, DynamicCommand::Result>& results) {

				output.success("Current TPS: " + TpsColor(Tick_per_second) + " " + TpsColor(Tick_per_minute));
		},
		CommandPermissionLevel::GameMasters);
}
#include "lang.h"

void RegisterCommands() {
	loadCNAME();
	Translation::load("plugins\\LLHelper\\language.json", Settings::LANGUAGE, defaultLangData);
	Event::RegCmdEvent::subscribe([](Event::RegCmdEvent e) {
		TransferCommand::setup(e.mCommandRegistry);
		HelperCommand::setup(e.mCommandRegistry);
		ItemCommand::setup(e.mCommandRegistry);
		CnameCommand::setup(e.mCommandRegistry);
		VanishCommand::setup(e.mCommandRegistry);
		SkickCommand::setup(e.mCommandRegistry);
		BanCommand::setup(e.mCommandRegistry);
		GmodeCommand::setup(e.mCommandRegistry);
		CrashCommand::setup(e.mCommandRegistry);
		RunasCommand::setup(e.mCommandRegistry);
		return true;
		});
	if (Settings::ENABLE_TPS)
		TpsCommand();
}

THook(void, "?_onClientAuthenticated@ServerNetworkHandler@@AEAAXAEBVNetworkIdentifier@@AEBVCertificate@@@Z",
	ServerNetworkHandler* snh, NetworkIdentifier& neti, Certificate& cert) {
	original(snh, neti, cert);
	auto xuid = ExtendedCertificate::getXuid(cert);
	auto be1 = getBanEntry(xuid);
	auto IP = neti.getIP();
	auto be2 = getBanEntry(IP);
	//auto nh = mc->getServerNetworkHandler();
	if (be1.set) {
		if (be1.val() != 0 && be1.val() < time(0)) {
			removeBanEntry(xuid);
		}
		else {
			snh->disconnectClient(neti, "You are banned", true);
		}
	}
	if (be2.set) {
		if (be2.val() != 0 && be2.val() < time(0)) {
			removeBanEntry(IP);
		}
		else {
			snh->disconnectClient(neti, "You are banned", true);
		}
	}
}

