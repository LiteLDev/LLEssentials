#include "pch.h"
#include <EventAPI.h>
#include <stddef.h>
#include <iostream>
#include <string>
#include "Helper.h"
#include <string_view>
#include <MC/ExtendedCertificate.hpp>
#include <MC/NetworkIdentifier.hpp>
#include <MC/ServerNetworkHandler.hpp>
#include <MC/Item.hpp>
#include <SendPacketAPI.h>

std::unique_ptr<KVDB> db;
playerMap<string> ORIG_NAME;
std::unordered_map<string, string> CNAME;

void loadCNAME() {
	db = std::make_unique<KVDB>("plugins/LLHelper/data", false);
	db->iter([](string_view k, string_view v) {
		if (!k._Starts_with("b_"))
			CNAME.emplace(k, v);
		return true;
		});
}

void LOWERSTRING(string& S) {
	for (auto& i : S) {
		i = tolower(i);
	}
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
	void execute(CommandOrigin const& ori, CommandOutput& outp) {
		auto res = pl.results(ori);
		if (!Command::checkHasTargets(res, outp)) return;
		for (auto i : res) {
			i->setPlayerGameType(mode);
		}
		outp.success(tr("gmode.success"));
	}
	static void setup(CommandRegistry* registry) {
		using RegisterCommandHelper::makeMandatory;
		using RegisterCommandHelper::makeOptional;
		registry->registerCommand("gmode", "Switch your gamemode", CommandPermissionLevel::GameMasters, { (CommandFlagValue)0 }, { (CommandFlagValue)0x80 });
		registry->registerOverload<GmodeCommand>("skick", makeMandatory(&GmodeCommand::pl, "target"), makeMandatory(&GmodeCommand::mode, "mode"));
	}
};

class BanCommand : public Command {
	enum BANOP {
		ban = 1,
		unban = 2,
		banip = 3,
		list = 4
	} op;
	std::string entry;
	bool time_isSet;
	int time;
public:
	void execute(CommandOrigin const& ori, CommandOutput& outp) {
		LOWERSTRING(entry);
		switch (op)
		{
		case BANOP::banip: {
			addBanEntry(entry, time_isSet  ? time : 0);
			outp.success(entry + tr("ban.banip.success"));
		}
		case BANOP::ban: {
			addBanEntry(PlayerDB::getXuid(entry), time_isSet ? time : 0);
			Level::runcmdEx("skick " + entry);
			outp.success(entry + tr("ban.ban.success"));
		}
					   break;
		case BANOP::unban: {
			if (getBanEntry(entry).set) {
				removeBanEntry(entry);
				outp.success(entry + tr("ban.unban.success"));
			}
			else {
				std::string XID = PlayerDB::getXuid(entry);
				if (XID == "") {
					outp.error(tr("ban.unban.error"));
				}
				else {
					removeBanEntry(XID);
					outp.success("");
				}
			}
		}
						 break;
		case list: {
			db->iter([&](string_view key, string_view val)->bool {
				if (key._Starts_with("b_")) {
					string banned{ key.substr(2) };
					if (banned.find('.') != banned.npos) {
						outp.addMessage(banned + " " + std::to_string(*(time_t*)val.data()));
					}
					else {
						xuid_t xid;
						std::stringstream ss{ banned };
						ss >> xid;
						outp.addMessage(banned + " (" + PlayerDB::fromXuid(xid) + ") " + std::to_string(*(time_t*)val.data()));
					}
				}
				outp.addMessage(tr("ban.list.success"));
				});
			outp.success(tr("ban.list.success"));
		}
				 break;
		default:
			break;
		}
		outp.error("");
	}
	static void setup(CommandRegistry* registry) {
		using RegisterCommandHelper::makeMandatory;
		using RegisterCommandHelper::makeOptional;
		registry->registerCommand("ban", "Ban a player", CommandPermissionLevel::GameMasters, { (CommandFlagValue)0 }, { (CommandFlagValue)0x80 });
		registry->addEnum<BANOP>("OP", { {"ban", BANOP::ban}, {"unban", BANOP::unban}, {"banip", BANOP::banip}, {"list", BANOP::list}});
		registry->registerOverload<BanCommand>("ban", makeMandatory<CommandParameterDataType::ENUM>(&BanCommand::op, "op"), makeMandatory(&BanCommand::entry, "target"), makeOptional(&BanCommand::time, "time", &BanCommand::time_isSet));
	}
};

class SkickCommand : public Command {
	std::string target;
public:
	void execute(CommandOrigin const& ori, CommandOutput& outp) {
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
		else
		{
			outp.error(target + " not found");
		}
	}
	static void setup(CommandRegistry* registry) {
		using RegisterCommandHelper::makeMandatory;
		using RegisterCommandHelper::makeOptional;
		registry->registerCommand("skick", "Force kick", CommandPermissionLevel::GameMasters, { (CommandFlagValue)0 }, { (CommandFlagValue)0x80 });
		registry->registerOverload<SkickCommand>("skick", makeMandatory(&SkickCommand::target, "target"));
	}
};

class VanishCommand : public Command {
public:
	void execute(CommandOrigin const& ori, CommandOutput& outp) {
		ServerPlayer* sp = ori.getPlayer();
		VarULong ul(ZigZag(sp->getUniqueID().id));
		BinaryStream bs;
		bs.writeUnsignedInt64(ul);
		NetworkPacket	<14> pk{ bs.getAndReleaseData() };
		std::vector<Player*> plist = Level::getAllPlayers();
		for (auto p : plist) {
			if (p != sp) {
				ServerPlayer* spp = (ServerPlayer*)p;
				spp->sendNetworkPacket(pk);
			}
		}
		outp.addMessage(tr("vanish.success"));
	}
	static void setup(CommandRegistry* registry) {
		using RegisterCommandHelper::makeMandatory;
		using RegisterCommandHelper::makeOptional;
		registry->registerCommand("vanish", "Hide yourself", CommandPermissionLevel::GameMasters, { (CommandFlagValue)0 }, { (CommandFlagValue)0x80 });
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
	void execute(CommandOrigin const& ori, CommandOutput& outp) {
		std::vector<Player*> pList = Level::getAllPlayers();
		Player* player = nullptr;
		for (auto p : pList) {
			if (p->getRealName() == src) {
				player = p;
				break;
			}
		}
		if (op == CNAMEOP::set) {
			if (name_isSet) {
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
		registry->registerCommand("cname", "Custom name", CommandPermissionLevel::GameMasters, { (CommandFlagValue)0 }, { (CommandFlagValue)0x80 });
		registry->addEnum<CNAMEOP>("OP", { {"set", CNAMEOP::set}, {"rm", CNAMEOP::remove}});
		registry->registerOverload<CnameCommand>("cname", makeMandatory<CommandParameterDataType::ENUM>(&CnameCommand::op, "optinal", "OP"), makeMandatory(&CnameCommand::src, "player"), makeOptional(&CnameCommand::name, "name", & CnameCommand::name_isSet));
	}
};

class TransferCommand : public Command {
	CommandSelector<Player> p;
	std::string host;
	int port;
	bool port_isSet;

public:
	void execute(CommandOrigin const& ori, CommandOutput& outp) {
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
		registry->registerCommand("transfer", "Transfer player to another server", CommandPermissionLevel::GameMasters, { (CommandFlagValue)0 }, { (CommandFlagValue)0x80 });
		registry->registerOverload<TransferCommand>("transfer", makeMandatory(&TransferCommand::p, "player"), makeMandatory(&TransferCommand::host, "IP"), makeOptional(&TransferCommand::port, "port", &TransferCommand::port_isSet));
	}
};

class HelperCommand : public Command {
	enum HelperOP : int {
		reload = 0
	} action;

public:
	void execute(CommandOrigin const& ori, CommandOutput& outp) {
		switch (action) {
		case reload:
			loadCfg();
			outp.success(tr("hreload.success"));
			break;
		default:
			outp.error("Error");
		}
		
	}
	static void setup(CommandRegistry* registry) {
		using RegisterCommandHelper::makeMandatory;
		using RegisterCommandHelper::makeOptional;
		registry->registerCommand("helper", "LLHelper", CommandPermissionLevel::GameMasters, { (CommandFlagValue)0 }, { (CommandFlagValue)0x80 });
		registry->addEnum<HelperOP>("Action", {{"reload", HelperOP::reload}});
		registry->registerOverload<HelperCommand>("helper", makeMandatory<CommandParameterDataType::ENUM>(&HelperCommand::action, "optinal", "Action"));
	}
};

class ItemCommand : public Command {
public:
	void execute(CommandOrigin const& ori, CommandOutput& outp) {
		if (ori.getOriginType() == (int)OriginType::Player) {
			ServerPlayer* wp = ori.getPlayer();
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
		registry->registerCommand("item", "Show item information on your hand", CommandPermissionLevel::GameMasters, { (CommandFlagValue)0 }, { (CommandFlagValue)0x80 });
	}
};

void RegisterCommands() {
	loadCNAME();
	Translation::load("plugins\\LLHelper\\langpack\\helper.json");
	Event::RegCmdEvent::subscribe([](Event::RegCmdEvent e) {
		TransferCommand::setup(e.mCommandRegistry);
		HelperCommand::setup(e.mCommandRegistry);
		ItemCommand::setup(e.mCommandRegistry);
		CnameCommand::setup(e.mCommandRegistry);
		VanishCommand::setup(e.mCommandRegistry);
		SkickCommand::setup(e.mCommandRegistry);
		BanCommand::setup(e.mCommandRegistry);
		return true;
		});
	/*
	Event::addEventListener([](RegCmdEvent e) {
		CEnum<BANOP> _1("banop", { "ban","unban","banip" });
		CEnum<BANOP_LIST> _2("banoplist", { "list" });
		CEnum<CNAMEOP> _3("cnameop", { "set","rm" });
		MakeCommand("gmode", "set your gametype", 1);
		CmdOverload(gmode, oncmd_gmode, "target", "mode");
		MakeCommand("ban", "blacklist", 1);
		CmdOverload(ban, onCMD_Ban, "op", "target", "time");
		CmdOverload(ban, onCMD_BanList, "list");
		MakeCommand("transfer", "transfer player to another server", 1);
		CmdOverload(transfer, onCMD_Trans, "target", "host", "port");
		MakeCommand("hreload", "reload cmdhelper", 1);
		CmdOverload(hreload, onReload);
		MakeCommand("skick", "force kick", 1);
		CmdOverload(skick, onCMD_skick, "target");
		MakeCommand("cname", "custom name", 1);
		CmdOverload(cname, onCMD_CNAME, "op", "target", "name");
		MakeCommand("vanish", "hide yourself", 1);
		CmdOverload(vanish, oncmd_vanish);
		MakeCommand("item", "show item info on hand", 0);
		CmdOverload(item, oncmd_item);
		});
		*/
}

THook(void, "?_onClientAuthenticated@ServerNetworkHandler@@AEAAXAEBVNetworkIdentifier@@AEBVCertificate@@@Z", ServerNetworkHandler* snh, NetworkIdentifier& neti, Certificate& cert) {
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

