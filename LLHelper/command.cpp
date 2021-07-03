#include "pch.h"
#include <api/Basic_Event.h>
#include <api/commands.h>
#include "commad.h"
#include <stddef.h>
#include <iostream>
#include <string>
#include "BDS.h"
#include "Helper.h"
#include <string_view>

LangPack LangP("plugins\\LLHelper\\langpack\\helper.json");
unique_ptr<KVDBImpl> db;
playerMap<string> ORIG_NAME;
unordered_map<string, string> CNAME;

void loadCNAME() {
	db = MakeKVDB("plugins\\LLHelper\\data", false);
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
		setPlayerGameType(i, mode);
	}
	outp.success(_TRS("gmode.success"));
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
				auto strname = XIDREG::id2str(xid);
				outp.addMessage(banned + " (" + (strname.set ? strname.val() : "") + ") " + std::to_string(*(time_t*)val.data()));
			}
		}
		outp.success(_TRS("ban.list..success"));
		return true;
		});
	outp.success(_TRS("ban.list.success"));
	return true;
}
bool onCMD_Ban(CommandOrigin const& ori, CommandOutput& outp, MyEnum<BANOP> op, string& entry, optional<int>& time) {
	LOWERSTRING(entry);
	switch (op.val)
	{
	case BANOP::banip: {
		addBanEntry(entry, time.set ? time.val() : 0);
		outp.success(QUOTE(entry) + _TRS("ban.banip.success"));
		return true;
	}
	case BANOP::ban: {
		addBanEntry(S(XIDREG::str2id(entry).val()), time.set ? time.val() : 0);
		liteloader::runcmdA("kick", QUOTE(entry));
		outp.success(QUOTE(entry) + _TRS("ban.ban.success"));
		return true;
	}
				   break;
	case BANOP::unban: {
		if (getBanEntry(entry).set) {
			removeBanEntry(entry);
			outp.success(QUOTE(entry) + _TRS("ban.unban.success"));
			return true;
		}
		else {
			auto XID = XIDREG::str2id(entry);
			if (!XID.set) {
				outp.error(_TRS("ban.unban.error"));
				return false;
			}
			else {
				removeBanEntry(S(XID.val()));
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
	vector<Player*> plist = liteloader::getAllPlayers();
	Player* A = nullptr;
	for (auto p : plist) {
		if (offPlayer::getRealName(p) == playername) {
			A = p;
			break;
		}
	}
	if (A) {
		forceKick(A);
		outp.addMessage(target + _TRS("skick.success"));
		return true;
	}
	else
	{
		//no player
	}
}

bool oncmd_vanish(CommandOrigin const& ori, CommandOutput& outp) {
	auto wp = MakeWP(ori).val();
	auto sp = MakeSP(ori);
	VarULong ul(ZigZag(wp->getUniqueID().id));
	WBStream ws;
	ws.apply(ul);
	MyPkt<14> pk{ ws };
	vector<Player*> plist = liteloader::getAllPlayers();
	for (auto p : plist) {
		if (p != sp) {
			auto spp = (ServerPlayer*)p;
			spp->sendNetworkPacket(pk);
		}
	}
	outp.addMessage(_TRS("vanish.success"));
	return true;
}

enum class CNAMEOP :int {
	set = 1,
	remove = 2
};

bool onCMD_CNAME(CommandOrigin const& ori, CommandOutput& p, MyEnum<CNAMEOP> op, string& src, optional<string>& name) {
	string playerName = src;
	vector<Player*> pList = liteloader::getAllPlayers();
	Player* player = nullptr;
	for (auto p : pList) {
		if (offPlayer::getRealName(p) == playerName) {
			player = p;
			break;
		}
	}
	if (op == CNAMEOP::set) {
		auto& str = name.val();
		for (int i = 0; i < str.size(); ++i) {
			if (str[i] == '^') str[i] = '\n';
		}
		CNAME[src] = str;
		db->put(src, str);
		if (!player) {
			p.success(_TRS("cname.set.notonline"));
			return false;
		}
		optional<WPlayer> wPlayer = WPlayer(*(ServerPlayer*)player);
		if (!wPlayer.set) {
			p.success(_TRS("cname.set.notonline"));
			return false;
		}
		p.success(_TRS("cname.set.success"));
		wPlayer.val()->setName(str);
		ORIG_NAME[wPlayer.val().v] = wPlayer.val().getName();
	}
	else {
		CNAME.erase(src);
		db->del(src);
		if (!player) {
			p.success(_TRS("cname.rm.notonline"));
			return false;
		}
		optional<WPlayer> wPlayer = WPlayer(*(ServerPlayer*)player);
		if (!wPlayer.set) {
			p.success(_TRS("cname.rm.notonline"));
			return false;
		}
		p.success(_TRS("cname.rm.success"));
		wPlayer.val()->setName(src);
		ORIG_NAME._map.erase(wPlayer.val().v);
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
	outp.success(_TRS("hreload.success"));
	return true;
}

void getItemName(const Item* item, string* str) {
	SymCall("?getSerializedName@Item@@QEBA?AV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@XZ",
		void, const Item*, string*)(item, str);
}

bool oncmd_item(CommandOrigin const& ori, CommandOutput& outp) {
	if (ori.getOriginType() == OriginType::Player) {
		auto wp = MakeWP(ori);
		if (wp.set) {
			ItemStack item = wp.val().get().getCarriedItem();
			std::string itemName;
			if (item.getId() != 0) {
				getItemName(item.getItem(), &itemName);
			}
			outp.success(itemName + " " + std::to_string(item.getId()));
			return true;
		}
	}
	else {
		outp.error("You are not a player");
		return false;
	}
}

void REGCMD() {
	loadCNAME();
	Event::addEventListener([](RegCmdEV e) {
		CMDREG::SetCommandRegistry(e.CMDRg);
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
	auto IP = liteloader::getIP(neti);
	auto be2 = getBanEntry(IP);
	//auto nh = mc->getServerNetworkHandler();
	if (be1.set) {
		if (be1.val() != 0 && be1.val() < time(0)) {
			removeBanEntry(xuid);
		}
		else {
			snh->onDisconnect(neti);
		}
	}
	if (be2.set) {
		if (be2.val() != 0 && be2.val() < time(0)) {
			removeBanEntry(IP);
		}
		else {
			snh->onDisconnect(neti);
		}
	}
}

