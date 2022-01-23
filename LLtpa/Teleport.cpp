// BDXTPA.cpp : 定义 DLL 的导出函数。
//

#include "pch.h"
#include "homeStorage.h"
#include "Tpa.h"
#include <RegCommandAPI.h>
#include <MC/NetworkIdentifier.hpp>
#include <MC/Types.hpp>
#include <Dedicated/Core.h>
#include <GuiAPI.h>
#include <MC/ServerPlayer.hpp>
std::unique_ptr<KVDB> db;
Logger logger("Teleport");

enum direction :int {
	A_B = 1,
	B_A = 2
};
struct TPReq {
	direction dir;
	string A, B;
	clock_t time;
	TPReq() {}
	TPReq(direction a, string_view b, string_view c, clock_t d) :dir(a), A(b), B(c), time(d) {}
};
struct TPASet {
	clock_t lastReq = 0;
	bool Accept = true;
};

#include<unordered_map>
#include "settings.h"
using std::unordered_map;
static std::list<TPReq> reqs;
static unordered_map<CHash, TPASet> tpaSetting;
static unordered_map<string, Vec4> warps;



playerMap<Vec4> deathPos;

optional<decltype(reqs.begin())> DoFetchReq(string_view a) {
	for (auto it = reqs.begin(); it != reqs.end(); ++it) {
		if (it->A == a || it->B == a) return { it };
	}
	return {};
}
optional<decltype(reqs.begin())> DoFetchReq_sender(string_view a) {
	auto rv = DoFetchReq(a);
	if (rv.set && rv.value()->A == a) return rv;
	return {};
}
optional<decltype(reqs.begin())> DoFetchReq_receiver(string_view a) {
	auto rv = DoFetchReq(a);
	if (rv.set && rv.value()->B == a) return rv;
	return {};
}
enum class TPFailReason :int {
	success = 0,
	ratelimit = 1,
	inreq = 2,
	blocked = 3
};
TPFailReason CanMakeReq(string_view a, string_view b) {
	CHash A = do_hash(a.data()), B = do_hash(b.data());
	if (tpaSetting[A].lastReq >= clock() - Settings::TPratelimit) {
		return TPFailReason::ratelimit;
	}
	if (DoFetchReq(a).set || DoFetchReq(b).set) return TPFailReason::inreq;
	if (!tpaSetting[B].Accept) return TPFailReason::blocked;
	return TPFailReason::success;
}
enum class TPCloseReason :int {
	timeout = 1,
	deny = 2,
	accept = 3,
	cancel = 4
};

void LOWERSTRING(string& S) {
	for (auto& i : S) {
		i = tolower(i);
	}
}

bool DoCloseReq(decltype(reqs.begin()) rq, TPCloseReason res) {
	vector<Player*> playerList = Level::getAllPlayers();
	ServerPlayer* playerA = nullptr;
	ServerPlayer* playerB = nullptr;
	for (auto p : playerList) {
		if (p->getRealName() == rq->A) {
			playerA = (ServerPlayer*)p;
			break;
		}
	}
	for (auto p : playerList) {
		if (p->getRealName() == rq->B) {
			playerB = (ServerPlayer*)p;
			break;
		}
	}
	if (res == TPCloseReason::cancel) {
		if (playerA)
			playerA->sendText(tr("tpa.reason.cancel"));
		if (playerB)
			playerB->sendText(tr("tpa.reason.cancel"));
		reqs.erase(rq);
		return true;
	}
	if (res == TPCloseReason::accept) {
		if (playerA && playerB) {
			Vec4 AP{ rq->dir == A_B ? playerB : playerA };
			AP.teleport(rq->dir == A_B ? playerA : playerB);
			reqs.erase(rq);
			playerA->sendTextPacket(tr("tpa.reason.accept"), TextType::RAW);
			playerB->sendTextPacket(tr("tpa.reason.accept"), TextType::RAW);
			return true;
		}
		// When tpa sender offline
		if (playerB)
			playerB->sendTextPacket(tr("tpa.reason.notonline"), TextType::RAW);
		reqs.erase(rq);
		return false;
	}
	if (playerA)
		playerA->sendTextPacket(res == TPCloseReason::deny ? tr("tpa.reason.deny") : tr("tpa.reason.timeout"), TextType::RAW);
	if (playerB)
		playerB->sendTextPacket(res == TPCloseReason::deny ? tr("tpa.reason.deny") : tr("tpa.reason.timeout"), TextType::RAW);
	reqs.erase(rq);
	return true;
}

void DoMakeReq(ServerPlayer* _a, ServerPlayer* _b, direction dir) {
	std::string a = _a->getRealName();
	std::string b = _b->getRealName();
	CHash A = do_hash(a.c_str()), B = do_hash(b.c_str());
	tpaSetting[A].lastReq = clock();
	reqs.emplace_back(dir, a, b, clock());
	string prompt = a + (dir == A_B ? tr("tpa.req.A_B") : tr("tpa.req.B_A"));
	_b->sendTextPacket(prompt, TextType::RAW);
	using namespace GUI;
	shared_ptr<RawFormBinder> x;
	char buf[1024];
	std::string form = "{\"type\":\"form\",\"title\":\"" + tr("tpa.request.title") + "\",\"content\":\"%s\",\"buttons\":[{\"text\":\"" + tr("tpa.request.accept") + "\"},{\"text\":\"" + tr("tpa.request.deny") + "\"}]}";
	string FM{ buf,(size_t)snprintf(buf,1024, form.c_str(), prompt.c_str()) };
	sendForm(*_b, RawFormBinder{ FM,[](ServerPlayer& wp,RawFormBinder::DType i) {
		auto [clicked,res,list] = i;
		if (clicked) {
			int idx = atoi(res);
			if (idx) {
				wp.runcmd("tpa de");
			}
			else {
				wp.runcmd("tpa ac");
			}
		}
	} ,{} });
}

void schTask() {
	Schedule::repeat([] {
		clock_t expire = clock() - Settings::TPexpire;
		for (auto it = reqs.begin(); it != reqs.end();) {
			if (it->time <= expire) {
				auto oldit = it;
				++it;
				DoCloseReq(oldit, TPCloseReason::timeout);
			}
			else break;
		}
		}, 10);
}

std::vector<string> playerList() {
	auto plist = Level::getAllPlayers();
	std::vector<string> pl;
	for (auto p : plist) {
		pl.push_back(p->getNameTag());
	}
	return pl;
}

class TpaCommand : public Command {
	bool dir_isSet;
	direction dir;
	bool tpaop_isSet;
	enum TPAOP :int {
		ac = 1,
		de = 2,
		cancel = 3,
		toggle = 4,
		gui = 5
	} op;
	CommandSelector<Player> target;
public:
	void execute(CommandOrigin const& ori, CommandOutput& outp) const {
		if (dir_isSet) {
			auto res = target.results(ori);
			if (!Command::checkHasTargets(res, outp) || (res.count() != 1)) return;
			ServerPlayer* t = (ServerPlayer*)*res.begin();
			auto reqres = CanMakeReq(ori.getName(), t->getName());
			switch (reqres) {
			case TPFailReason::success:
			{
				DoMakeReq({ ori.getPlayer() }, t, dir);
				return;
			}
			break;
			case TPFailReason::ratelimit: {
				outp.error(tr("tp.fail.rate"));
				return;
			}
										break;
			case TPFailReason::inreq: {
				outp.error(tr("tp.fail.inreq"));
				return;
			}
									break;
			case TPFailReason::blocked: {
				outp.error(tr("tp.fail.blocked"));
				return;
			}
									  break;
			}
		}
		if (tpaop_isSet) {
			switch (op) {
			case TPAOP::ac: {
				auto it = DoFetchReq_receiver(ori.getName());
				if (!it.set) {
					outp.error(tr("tpa.ac.error"));
					return;
				}
				DoCloseReq(it.val(), TPCloseReason::accept);
				break;
			}
			case TPAOP::de: {
				auto it = DoFetchReq_receiver(ori.getName());
				if (!it.set) {
					outp.error(tr("tpa.de.error"));
					return;
				}
				DoCloseReq(it.val(), TPCloseReason::deny);
				break;
			}
			case TPAOP::cancel: {
				auto it = DoFetchReq_sender(ori.getName());
				if (!it.set) {
					return;
				}
				DoCloseReq(it.val(), TPCloseReason::cancel);
				break;
			}
			case TPAOP::toggle: {
				CHash hs = do_hash(ori.getName().c_str());
				auto state = !tpaSetting[hs].Accept;
				tpaSetting[hs].Accept = state;
				outp.success("new state " + std::to_string(state));
				break;
			}
			case TPAOP::gui: {
				using namespace GUI;
				auto fm = std::make_shared<FullForm>();
				fm->title = tr("tpa.gui.title");
				std::string guiLabel = tr("tpa.gui.label");
				std::string guiDropdown1 = tr("tpa.gui.dropdown1");
				std::string guiDropdown2 = tr("tpa.gui.dropdown2");
				fm->addWidget({ GUILabel(guiLabel.c_str()) });
				fm->addWidget({ GUIDropdown(guiDropdown1.c_str() ,{"to","here"}) });
				fm->addWidget({ GUIDropdown(guiDropdown2.c_str() ,playerList()) });
				sendForm(*ori.getPlayer(), FullFormBinder{ fm,{[](ServerPlayer& P, FullFormBinder::DType data) {
					if (!data.set) return;
						auto& [d1,d2] = data.val();
						P.runcmd("tpa " + d2[0] + " \"" + d2[1]+"\"");
				}} });
				break;
			}
			}
		}
	}
	static void setup(CommandRegistry* registry) {
		using RegisterCommandHelper::makeMandatory;
		using RegisterCommandHelper::makeOptional;
		registry->registerCommand("tpa", "Teleport", CommandPermissionLevel::Any, { (CommandFlagValue)0 }, { (CommandFlagValue)0x80 });
		registry->addEnum<direction>("TPAOP2", { {"to", direction::A_B}, {"here", direction::B_A} });
		registry->addEnum<TpaCommand::TPAOP>("TPAOP", { {"ac", TPAOP::ac}, {"de", TPAOP::de}, {"cancel", TPAOP::cancel}, {"gui", TPAOP::gui}, {"toggle", TPAOP::toggle} });
		registry->registerOverload<TpaCommand>("tpa", makeMandatory<CommandParameterDataType::ENUM>(&TpaCommand::dir, "direction", "TPAOP2", &TpaCommand::dir_isSet), makeMandatory(&TpaCommand::target, "player"));
		registry->registerOverload<TpaCommand>("tpa", makeMandatory<CommandParameterDataType::ENUM>(&TpaCommand::op, "op", "TPAOP", &TpaCommand::tpaop_isSet));
	}
};

shared_ptr<GUI::SimpleForm> WARPGUI;
void reinitWARPGUI() {
	using namespace GUI;
	if (!WARPGUI) WARPGUI = make_shared<SimpleForm>();
	WARPGUI->title = tr("warp.gui.title");
	WARPGUI->content = tr("warp.gui.content");
	WARPGUI->reset();
	for (auto& [k, v] : warps) {
		WARPGUI->addButton(GUIButton(string(k)));
	}
}

void sendWARPGUI(ServerPlayer* wp) {
	using namespace GUI;
	sendForm(*wp, SimpleFormBinder(WARPGUI, [](ServerPlayer& wp, SimpleFormBinder::DType d) {
		if (d.set) {
			wp.runcmd("warp go \"" + d.val().second + "\"");
		}
		}));
}

void saveWarps() {
	WBStream ws;
	ws.apply(warps);
	db->put("warps", ws);
	reinitWARPGUI();
}

class WarpCommand : public Command {
	enum WARPOP :int {
		go = 1,
		add = 2,
		ls = 3,
		del = 4,
		gui = 5
	} op;
	bool val_isSet;
	std::string val;
public:
	void execute(CommandOrigin const& ori, CommandOutput& outp) const {
		switch (op)
		{
		case gui: {
			sendWARPGUI(ori.getPlayer());
			return;
		}
		case add: {
			if (ori.getPermissionsLevel() < 1) return;
			warps.emplace(val, ori.getPlayer());
			saveWarps();

			break;
		}
		case del: {
			if (ori.getPermissionsLevel() < 1) return;
			warps.erase(val);
			saveWarps();

			break;
		}
		case ls: {
			for (auto& i : warps) {
				outp.success(i.first + " " + i.second.toStr());
			}

			break;
		}
		case go: {
			auto it = warps.find(val);
			if (it == warps.end()) {
				outp.error(tr("home.not.found"));
				return;
			}
			it->second.teleport(ori.getPlayer());

			break;
		}
		default:
			break;
		}
	}

	static void setup(CommandRegistry* registry) {
		using RegisterCommandHelper::makeMandatory;
		using RegisterCommandHelper::makeOptional;
		registry->registerCommand("warp", "Teleport", CommandPermissionLevel::Any, { (CommandFlagValue)0 }, { (CommandFlagValue)0x80 });
		registry->addEnum<WarpCommand::WARPOP>("WARPOP", { {"add", WARPOP::add}, {"del", WARPOP::del}, {"go", WARPOP::go}, {"gui", WARPOP::gui}, {"ls", WARPOP::ls} });
		registry->registerOverload<WarpCommand>("warp", makeMandatory<CommandParameterDataType::ENUM>(&WarpCommand::op, "op", "WARPOP"), makeOptional(&WarpCommand::val, "warp", &WarpCommand::val_isSet));
	}
};

class HomeCommand : public Command {
	enum HOMEOP :int {
		go = 1,
		add = 2,
		ls = 3,
		del = 4,
		gui = 5
	} op;
	bool val_isSet;
	std::string val;
public:
	void execute(CommandOrigin const& ori, CommandOutput& outp) const {
		Homes& hm = getHomeInCache(std::stoull(ori.getPlayer()->getXuid()));
		switch (op)
		{
		case HOMEOP::add: {
			if (!val_isSet) {
				outp.error("Please input home's name");
				return;
			}
			if (ori.getPermissionsLevel() == 0 && hm.data.size() >= Settings::MAX_HOMES) {
				outp.error(tr("home.is.full"));
				return;
			}
			ServerPlayer* wp = ori.getPlayer();
			Vec4 vc{ wp };
			IVec2 startVc{ wp->getPos() };
			IVec2 endVc{ wp->getPos() };
			startVc += -Settings::HOME_DISTANCE_LAND;
			endVc += Settings::HOME_DISTANCE_LAND;
			/*if (!checkLandOwnerRange_stub(startVc, endVc, vc.dimid, wp.getXuid())) {
				outp.error(tr("home.near.others.land"));
				return false;
			}*/
			hm.data.emplace_back(val, vc);
			hm.save();
			outp.success("home point `" + val + "` was set successfully!!");

			break;
		}
		case HOMEOP::del: {
			if (!val_isSet) {
				outp.error("Please input home's name");
				return;
			}
			hm.data.remove_if([&](auto& x) {
				return x.name == val;
				});
			hm.save();

			break;
		}
		case HOMEOP::ls: {
			for (auto& i : hm.data) {
				outp.addMessage(i.name + " " + i.pos.toStr());
			}
			break;
		}
		case HOMEOP::go: {
			if (!val_isSet) {
				outp.error("Please input home's name");
				return;
			}
			for (auto& i : hm.data) {
				if (i.name == val) {
					i.pos.teleport(ori.getPlayer());
					return;
				}
			}
			outp.error(tr("home.not.found"));
			return;
			break;
		}
		case HOMEOP::gui: {
			auto wp = ori.getPlayer();
			auto HomeGUI = make_shared<GUI::SimpleForm>();
			HomeGUI->title = tr("home.gui.title");
			HomeGUI->content = tr("home.gui.content");
			HomeGUI->reset();
			for (auto& i : hm.data) {
				HomeGUI->addButton(GUI::GUIButton(string(i.name)));
			}
			GUI::sendForm(*wp, GUI::SimpleFormBinder::SimpleFormBinder(HomeGUI, [](ServerPlayer& wp, GUI::SimpleFormBinder::DType d) {
				if (d.set) {
					wp.runcmd("home go \"" + d.val().second + "\"");
				}
				}));
			break;
		}
		default:
			break;
		}
	}

	static void setup(CommandRegistry* registry) {
		using RegisterCommandHelper::makeMandatory;
		using RegisterCommandHelper::makeOptional;
		registry->registerCommand("home", "Teleport", CommandPermissionLevel::Any, { (CommandFlagValue)0 }, { (CommandFlagValue)0x80 });
		registry->addEnum<HomeCommand::HOMEOP>("HOMEOP", { {"add", HOMEOP::add}, {"del", HOMEOP::del}, {"go", HOMEOP::go}, {"gui", HOMEOP::gui}, {"ls", HOMEOP::ls} });
		registry->registerOverload<HomeCommand>("home", makeMandatory<CommandParameterDataType::ENUM>(&HomeCommand::op, "op", "HOMEOP"), makeOptional(&HomeCommand::val, "home", &HomeCommand::val_isSet));
	}
};

class BackCommand : public Command {
public:
	void execute(CommandOrigin const& ori, CommandOutput& outp) const {
		ServerPlayer* sp = ori.getPlayer();
		if (!deathPos._map.count(sp)) {
			outp.error(tr("home.not.found"));
			return;
		}
		deathPos[sp].teleport({ sp });
		deathPos._map.erase(sp);
	}
	static void setup(CommandRegistry* registry) {
		using RegisterCommandHelper::makeMandatory;
		using RegisterCommandHelper::makeOptional;
		registry->registerCommand("back", "Back to last deathpoint", CommandPermissionLevel::Any, { (CommandFlagValue)0 }, { (CommandFlagValue)0x80 });
		registry->registerOverload<BackCommand>("back");
	}
};

class SuicideCommand : public Command {
public:
	void execute(CommandOrigin const& ori, CommandOutput& outp) const {
		ori.getPlayer()->kill();
	}
	static void setup(CommandRegistry* registry) {
		using RegisterCommandHelper::makeMandatory;
		using RegisterCommandHelper::makeOptional;
		registry->registerCommand("suicide", "Goodbye", CommandPermissionLevel::Any, { (CommandFlagValue)0 }, { (CommandFlagValue)0x80 });
		registry->registerOverload<SuicideCommand>("suicide");
	}
};

void loadCfg() {
	//config
	if (!std::filesystem::exists("plugins/LLtpa"))
		std::filesystem::create_directories("plugins/LLtpa");
	if (std::filesystem::exists("plugins/LLtpa/tpa.json")) {
		try {
			Settings::LoadConfigFromJson("plugins/LLtpa/tpa.json");
		}
		catch (std::exception& e) {
			logger.error("Config File isInvalid, Err {}", e.what());
			Sleep(1000 * 100);
			exit(1);
		}
		catch (...) {
			logger.error("Config File isInvalid");
			Sleep(1000 * 100);
			exit(1);
		}
	}
	else {
		logger.info("Config with default values created");
		Settings::WriteDefaultConfig("plugins/LLtpa/tpa.json");
	}
	//tr
	if (!std::filesystem::exists("plugins/LLtpa/langpack"))
		std::filesystem::create_directories("plugins/LLtpa/langpack");
	if (std::filesystem::exists("plugins/LLtpa/langpack/en-us.json")) {
		try {
			TR::LoadConfigFromJson("plugins/LLtpa/langpack/en-us.json");
		}
		catch (std::exception& e) {
			logger.error("Config File isInvalid, Err {}", e.what());
			Sleep(1000 * 100);
			exit(1);
		}
		catch (...) {
			logger.error("Config File isInvalid");
			Sleep(1000 * 100);
			exit(1);
		}
	}
	else {
		logger.info("Config with default values created");
		TR::WriteDefaultConfig("plugins/LLtpa/langpack/en-us.json");
	}
}

class LLtpaCommand : public Command {
	enum LLtpaOP : int {
		reload = 0,
		update = 1
	} op;
	std::string isForce;
	bool isForce_set;

public:
	void execute(CommandOrigin const& ori, CommandOutput& outp) const {
		switch (op) {
		case LLtpaOP::reload:
			loadCfg();
			outp.success("Reloaded");
			break;
		case LLtpaOP::update:
			bool force = false;
			if (isForce_set) {
				if (isForce == "true") {
					force = true;
				}
				else {
					force = false;
				}
			}
			std::thread th([force]() {
				CheckAutoUpdate(true, force);
				});
			th.detach();
		}
	}
	static void setup(CommandRegistry* registry) {
		using RegisterCommandHelper::makeMandatory;
		using RegisterCommandHelper::makeOptional;
		registry->registerCommand("lltpa", "LLtpa manage command", CommandPermissionLevel::GameMasters, { (CommandFlagValue)0 }, { (CommandFlagValue)0x80 });
		registry->addEnum<LLtpaOP>("LLtpaOP", { {"reload", LLtpaOP::reload}, {"update", LLtpaOP::update} });
		registry->registerOverload<LLtpaCommand>("lltpa", makeMandatory<CommandParameterDataType::ENUM>(&LLtpaCommand::op, "OP", "LLtpaOP"), makeOptional(&LLtpaCommand::isForce, "isForce", &LLtpaCommand::isForce_set));
	}
};

void init() {
	string val;
	if (db->get("warps", val)) {
		RBStream rs{ val };
		rs.apply(warps);
	}
	loadCfg();
	Translation::load("plugins/LLtpa/langpack/" + Settings::LANGUAGE + ".json");
	reinitWARPGUI();
}

void tpa_entry() {
	db = KVDB::create("plugins\\LLtpa\\data", true, 8);
	init();
	schTask();
	Event::RegCmdEvent::subscribe([](const Event::RegCmdEvent& e) {
		if (Settings::TPA_ENABLED)	TpaCommand::setup(e.mCommandRegistry);
		if (Settings::HOME_ENABLED) {
			HomeCommand::setup(e.mCommandRegistry);
		}
		WarpCommand::setup(e.mCommandRegistry);
		if (Settings::BACK_ENABLED) BackCommand::setup(e.mCommandRegistry);
		if (Settings::SUICIDE_ENABLED) SuicideCommand::setup(e.mCommandRegistry);
		LLtpaCommand::setup(e.mCommandRegistry);
		return true;
		});
	if (Settings::BACK_ENABLED) {
		Event::PlayerDieEvent::subscribe([](const Event::PlayerDieEvent& ev) {
			ServerPlayer* sp = (ServerPlayer*)ev.mPlayer;
			deathPos[sp] = Vec4{ sp };
			sp->sendTextPacket(tr("tpa.back.use"), TextType::RAW);
			return true;
			});
	}
	Event::ServerStartedEvent::subscribe([](const Event::ServerStartedEvent& ev) {
		std::thread th([]() {
			CheckAutoUpdate(true, false);
			});
		th.detach();
		return true;
		});
	logger.info("Loaded version: {}", _ver);
}

