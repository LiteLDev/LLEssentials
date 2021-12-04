#include "pch.h"
#include <EventAPI.h>
#include "Command.h"
#include <stddef.h>
#include <iostream>
#include <string>
#include "Helper.h"
#include <string_view>
#include <MC/ExtendedCertificate.hpp>
#include <MC/NetworkIdentifier.hpp>
#include <MC/ServerNetworkHandler.hpp>

std::unique_ptr<KVDB> db;
playerMap<string> ORIG_NAME;
std::unordered_map<string, string> CNAME;

void loadCNAME() {
	db = std::make_unique<KVDB>("plugins\\LLHelper\\data", false);
	db->iter([](string_view k, string_view v) {
		if (!k._Starts_with("b_"))
			CNAME.emplace(k, v);
		return true;
		});
}
bool oncmd_gmode(CommandOrigin const& ori, CommandOutput& outp, CommandSelector<Player>& s, int mode) {
	auto res = s.results(ori);
	if (!Command::checkHasTargets(res, outp)) return false;
	for (auto i : res) {
		i->setPlayerGameType(mode);
	}
	outp.success(tr("gmode.success"));
	return true;
}

enum class BANOP :int {
	ban = 1,
	unban = 2,
	banip = 3
};
enum class BANOP_LIST :int {
	list = 1
};

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

bool onCMD_BanList(CommandOrigin const& ori, CommandOutput& outp, MyEnum<BANOP_LIST>) {
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
		outp.success(tr("ban.list.success"));
		return true;
		});
	outp.success(tr("ban.list.success"));
	return true;
}
bool onCMD_Ban(CommandOrigin const& ori, CommandOutput& outp, MyEnum<BANOP> op, string& entry, optional<int>& time) {
	LOWERSTRING(entry);
	switch (op.val)
	{
	case BANOP::banip: {
		addBanEntry(entry, time.set ? time.val() : 0);
		outp.success(entry + tr("ban.banip.success"));
		return true;
	}
	case BANOP::ban: {
		addBanEntry(PlayerDB::getXuid(entry), time.set ? time.val() : 0);
		Level::runcmdEx("skick "+ entry);
		outp.success(entry + tr("ban.ban.success"));
		return true;
	}
				   break;
	case BANOP::unban: {
		if (getBanEntry(entry).set) {
			removeBanEntry(entry);
			outp.success(entry + tr("ban.unban.success"));
			return true;
		}
		else {
			std::string XID = PlayerDB::getXuid(entry);
			if (XID == "") {
				outp.error(tr("ban.unban.error"));
				return false;
			}
			else {
				removeBanEntry(XID);
				return true;
			}
		}
	}
					 break;
	default:
		break;
	}
	return false;
}

bool onCMD_skick(CommandOrigin const& ori, CommandOutput& outp, string& target) {
	string playername = target;
	std::vector<Player*> plist = Level::getAllPlayers();
	Player* A = nullptr;
	for (auto p : plist) {
		if (p->getRealName() == playername) {
			A = p;
			break;
		}
	}
	if (A) {
		A->kick("You are kicked by admin");
		outp.addMessage(target + tr("skick.success"));
		return true;
	}
	else
	{
		//no player
	}
}

bool oncmd_vanish(CommandOrigin const& ori, CommandOutput& outp) {
	auto sp = ori.getPlayer();
	VarULong ul(ZigZag(sp->getUniqueID().id));
	WBStream ws;
	ws.apply(ul);
	MyPkt<14> pk{ ws };
	std::vector<Player*> plist = Level::getAllPlayers();
	for (auto p : plist) {
		if (p != sp) {
			auto spp = (ServerPlayer*)p;
			spp->sendNetworkPacket(pk);
		}
	}
	outp.addMessage(tr("vanish.success"));
	return true;
}

enum class CNAMEOP :int {
	set = 1,
	remove = 2
};

bool onCMD_CNAME(CommandOrigin const& ori, CommandOutput& p, MyEnum<CNAMEOP> op, string& src, optional<string>& name) {
	std::vector<Player*> pList = Level::getAllPlayers();
	Player* player = nullptr;
	for (auto p : pList) {
		if (p->getRealName() == src) {
			player = p;
			break;
		}
	}
	if (op == CNAMEOP::set) {
		if (!name.set) {
			p.error(tr("cname.set.null"));
			return false;
		}
		std::string& str = name.val();
		for (int i = 0; i < str.size(); ++i) {
			if (str[i] == '^') str[i] = '\n';
		}
		CNAME[src] = str;
		db->put(src, str);
		if (!player) {
			p.success(tr("cname.set.notonline"));
			return false;
		}
		if (!player) {
			p.success(tr("cname.set.notonline"));
			return false;
		}
		p.success(tr("cname.set.success"));
		player->setName(str);
		ORIG_NAME[(ServerPlayer*)player] = player->getName().c_str();
	}
	if (op == CNAMEOP::remove) {
		CNAME.erase(src);
		db->del(src);
		if (!player) {
			p.success(tr("cname.rm.notonline"));
			return false;
		}
		if (!player) {
			p.success(tr("cname.rm.notonline"));
			return false;
		}
		p.success(tr("cname.rm.success"));
		player->setName(src);
		ORIG_NAME._map.erase((ServerPlayer*)player);
	}
	return true;
}

bool onCMD_Trans(CommandOrigin const& ori, CommandOutput& outp, CommandSelector<Player>& p, string& host, optional<int> port) {
	int P = port.set ? port.val() : 19132;
	auto res = p.results(ori);
	if (!Command::checkHasTargets(res, outp)) return false;
	WBStream ws;
	ws.apply(MCString(host), (unsigned short)P);
	MyPkt<0x55, false> trpk(ws);
	for (auto i : res) {
		((ServerPlayer*)i)->sendNetworkPacket(trpk);
	}
	return true;
}

static bool onReload(CommandOrigin const& ori, CommandOutput& outp) {
	loadCfg();
	outp.success(tr("hreload.success"));
	return true;
}

void getItemName(const Item* item, string* str) {
	SymCall("?getSerializedName@Item@@QEBA?AV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@XZ",
		void, const Item*, string*)(item, str);
}

bool oncmd_item(CommandOrigin const& ori, CommandOutput& outp) {
	//if (ori.getOriginType() == OriginType::Player) {
	ServerPlayer* wp = ori.getPlayer();
	if (wp) {
		const ItemStack* item = &wp->getCarriedItem();
		std::string itemName = "Air";
		if (item->getId() != 0) {
			getItemName(item->getItem(), &itemName);
		}
		outp.success(itemName + " " + std::to_string(item->getId()));
		return true;
	}
	else {
		outp.error("You are not a player");
		return false;
	}
	/*}
	else {
		outp.error("You are not a player");
		return false;
	}*/
}

void REGCMD() {
	loadCNAME();
	Translation::load("plugins\\LLHelper\\langpack\\helper.json");
	Event::addEventListener([](RegCmdEV e) {
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

