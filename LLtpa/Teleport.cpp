// BDXTPA.cpp : 定义 DLL 的导出函数。
//

#include "pch.h"
#include "homeStorage.h"
#include "Tpa.h"
#include <MC/FormUI.hpp>
#include <RegCommandAPI.h>
#include <MC/NetworkIdentifier.hpp>
#include <MC/Types.hpp>
#include <Dedicated/Core.h>

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
using std::unordered_map;
static std::list<TPReq> reqs;
static unordered_map<CHash, TPASet> tpaSetting;
static unordered_map<string, Vec4> warps;

static clock_t TPexpire = CLOCKS_PER_SEC * 10;
static clock_t TPratelimit = CLOCKS_PER_SEC * 2;
static int MAX_HOMES = 5;
static int HOME_DISTANCE_LAND = 0;
static bool BACK_ENABLED, SUICIDE_ENABLED, TPA_ENABLED, HOME_ENABLED;


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
	if (tpaSetting[A].lastReq >= clock() - TPratelimit) {
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
	string playernamea = rq->A;
	string playernameb = rq->B;
	vector<Player*> plist = Level::getAllPlayers();
	Player* fplA = nullptr;
	Player* fplB = nullptr;
	for (auto p : plist) {
		if (p->getRealName() == playernamea) {
			fplA = p;
			break;
		}
	}
	for (auto p : plist) {
		if (p->getRealName() == playernameb) {
			fplB = p;
			break;
		}
	}
	if (fplA && fplB) {
		ServerPlayer* A = (ServerPlayer*)fplA;
		ServerPlayer* B = (ServerPlayer*)fplB;
		if (res == TPCloseReason::cancel) {
			reqs.erase(rq);
			return true;
		}
		if (res == TPCloseReason::accept) {
			if (A && B) {
				Vec4 AP{ rq->dir == A_B ? B : A };
				AP.teleport(rq->dir == A_B ? A : B);
				reqs.erase(rq);
				A->sendTextPacket(tr("tpa.reason.accept"), TextType::RAW);
				return true;
			}
			reqs.erase(rq);
			return false;
		}
		if (A) {
			A->sendTextPacket(res == TPCloseReason::deny ? tr("tpa.reason.deny") : tr("tpa.reason.timeout"), TextType::RAW);
		}
		if (B) {
			A->sendTextPacket(res == TPCloseReason::deny ? tr("tpa.reason.deny") : tr("tpa.reason.timeout"), TextType::RAW);
		}
		reqs.erase(rq);
		return true;
	}
	else {
		//no such player
	}
}
void DoMakeReq(ServerPlayer* _a, ServerPlayer* _b, direction dir) {
	std::string a = _a->getRealName();
	std::string b = _b->getRealName();
	CHash A = do_hash(a.c_str()), B = do_hash(b.c_str());
	tpaSetting[A].lastReq = clock();
	reqs.emplace_back(dir, a, b, clock());
	string prompt = a + (dir == A_B ? tr("tpa.req.A_B") : tr("tpa.req.B_A"));
	_b->sendTextPacket(prompt, TextType::RAW);
	//摸了，还没写
	/*using namespace Form;
	char buf[1024];
	string FM{ buf,(size_t)snprintf(buf,1024,tr("tpa.form").c_str(), prompt.c_str()) };
	CustomForm form(FM);
	form.sendTo(_b, [](const std::map<string, std::shared_ptr<CustomFormElement>>& map) {

		});*/
	//original
	/*
	sendForm(_b, RawFormBinder{ FM,[](WPlayer wp,RawFormBinder::DType i) {
		auto [clicked,res,list] = i;
		if (clicked) {
			int idx = atoi(res);
			wp.runcmdA("tpa",(idx == 0 ? "ac" : "de"));
		}
	} ,{} });*/
}

void schTask() {
	Schedule::repeat::repeat([] {
		clock_t expire = clock() - TPexpire;
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
				DoMakeReq({ (ServerPlayer*)ori.getEntity() }, t, dir);
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
					return;
				}
				DoCloseReq(it.val(), TPCloseReason::accept);
				break;
			}
			case TPAOP::de: {
				auto it = DoFetchReq_receiver(ori.getName());
				if (!it.set) {
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
				outp.error(u8"这摸鱼，多是一件美事啊");
				//摸了
				/*
				ServerPlayer* wp = ((ServerPlayer*)ori.getEntity());
				using namespace Form;
				CustomForm* fm{};
				fm->title = tr("tpa.gui.title");
				std::string guiLabel = tr("tpa.gui.label");
				std::string guiDropdown1 = tr("tpa.gui.dropdown1");
				std::string guiDropdown2 = tr("tpa.gui.dropdown2");
				fm->append({ Label("", guiLabel.c_str()) });
				fm->append({ Dropdown("", guiDropdown1.c_str() ,{"to","here"}) });
				fm->append({ Dropdown("", guiDropdown2.c_str() ,playerList()) });
				fm->sendTo(wp, [](const std::map<string, std::shared_ptr<CustomFormElement>>& map) {

					});*/
				//origin
				/*sendForm(wp, FullFormBinder{fm,{[](WPlayer P, FullFormBinder::DType data) {
					if (!data.set) return;
						auto& [d1,d2] = data.val();
						Level::runcmdAs(P, "tpa " + d2[0] + " " + QUOTE(d2[1]));
				}} });*/
				break;
			}
			}
		}
	}
	static void setup(CommandRegistry* registry) {
		using RegisterCommandHelper::makeMandatory;
		using RegisterCommandHelper::makeOptional;
		registry->registerCommand("tpa", "Teleport", CommandPermissionLevel::Any, { (CommandFlagValue)0 }, { (CommandFlagValue)0x80 });
		registry->addEnum<direction>("TPAOP2", { {"to", direction::A_B}, {"from", direction::B_A}});
		registry->addEnum<TpaCommand::TPAOP>("TPAOP", { {"ac", TPAOP::ac}, {"de", TPAOP::de}, {"cancel", TPAOP::cancel}, {"gui", TPAOP::gui}, {"toggle", TPAOP::toggle}});
		registry->registerOverload<TpaCommand>("tpa", makeMandatory<CommandParameterDataType::ENUM>(&TpaCommand::dir, "direction", "TPAOP2", &TpaCommand::dir_isSet), makeMandatory(&TpaCommand::target, "player"));
		registry->registerOverload<TpaCommand>("tpa", makeMandatory<CommandParameterDataType::ENUM>(&TpaCommand::op, "op", "TPAOP", &TpaCommand::tpaop_isSet));
	}
};

Form::SimpleForm* WARPGUI;
void reinitWARPGUI() { //broken
	WARPGUI->title = tr("warp.gui.title");
	WARPGUI->content = tr("warp.gui.content");
	for (auto& [k, v] : warps) {
		WARPGUI->append(Form::Button(string(k)));
	}
}

void sendWARPGUI(ServerPlayer* wp) {
	using namespace Form;
	WARPGUI->sendTo(wp, [wp](int i) { //broken origin见old分支
		wp->runcmd("warp go" + std::to_string(i));
		});
}

void saveWarps() {
	WBStream ws;
	ws.apply(warps);
	db->put("warps", ws);
	//reinitWARPGUI();
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
			outp.error(u8"这摸鱼，多是一件美事啊");
			//sendWARPGUI(((ServerPlayer*)ori.getEntity()));
			return;
		}
		case add: {
			if (ori.getPermissionsLevel() < 1) return;
			warps.emplace(val, ((ServerPlayer*)ori.getEntity()));
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
			it->second.teleport(((ServerPlayer*)ori.getEntity()));

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
		registry->addEnum<WarpCommand::WARPOP>("WARPOP", { {"add", WARPOP::add}, {"del", WARPOP::del}, {"go", WARPOP::go}, {"gui", WARPOP::gui}, {"ls", WARPOP::ls}});
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
		Homes& hm = getHomeInCache(std::stoull(((ServerPlayer*)ori.getEntity())->getXuid()));
		switch (op)
		{
		case HOMEOP::add: {
			if (!val_isSet) {
				outp.error("Please input home's name");
				return;
			}
			if (ori.getPermissionsLevel() == 0 && hm.data.size() >= MAX_HOMES) {
				outp.error(tr("home.is.full"));
				return;
			}
			ServerPlayer* wp = ((ServerPlayer*)ori.getEntity());
			Vec4 vc{ wp };
			IVec2 startVc{ wp->getPos() };
			IVec2 endVc{ wp->getPos() };
			startVc += -HOME_DISTANCE_LAND;
			endVc += HOME_DISTANCE_LAND;
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
					i.pos.teleport(((ServerPlayer*)ori.getEntity()));
					return;
				}
			}
			outp.error(tr("home.not.found"));
			return;
			break;
		}
		case HOMEOP::gui: {
			outp.error(u8"这摸鱼，多是一件美事啊");
			//摸了
			/*
			auto wp = ((ServerPlayer*)ori.getEntity());
			Form::SimpleForm* HomeGUI{};
			HomeGUI->title = tr("home.gui.title");
			HomeGUI->content = tr("home.gui.content");
			for (auto& i : hm.data) {
				HomeGUI->append(Form::Button(string(i.name)));
			}*/
			//origin
			/*
			GUI::sendForm(wp, GUI::SimpleFormBinder::SimpleFormBinder(HomeGUI, [](ServerPlayer* wp, GUI::SimpleFormBinder::DType d) {
				if (d.set) {
					wp.runcmdA("home", "go", QUOTE(d.val().second));
				}
				}));*/
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
		ServerPlayer* sp = (ServerPlayer*)ori.getEntity();
		if (!deathPos._map.count(sp)) {
			outp.error(tr("home.not.found"));
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
	try {
		ConfigJReader jr("plugins\\LLtpa\\tpa.json");
		jr.bind("max_homes", MAX_HOMES, 5);
		jr.bind("tpa_timeout", TPexpire, CLOCKS_PER_SEC * 20);
		jr.bind("tpa_ratelimit", TPratelimit, CLOCKS_PER_SEC * 5);
		jr.bind("home_land_distance", HOME_DISTANCE_LAND, -1);
		jr.bind("BACK_ENABLED", BACK_ENABLED, true);
		jr.bind("SUICIDE_ENABLED", SUICIDE_ENABLED, true);
		jr.bind("TPA_ENABLED", TPA_ENABLED, true);
		jr.bind("HOME_ENABLED", HOME_ENABLED, true);
	}
	catch (string e) {
		logger.error("JSON ERROR", e);
		throw 0;
	}
}

class ReloadCommand : public Command {
public:
	void execute(CommandOrigin const& ori, CommandOutput& outp) const {
		loadCfg();
		outp.success("Reloaded");
	}
	static void setup(CommandRegistry* registry) {
		using RegisterCommandHelper::makeMandatory;
		using RegisterCommandHelper::makeOptional;
		registry->registerCommand("tpareload", "Reload LLTpa's config", CommandPermissionLevel::GameMasters, { (CommandFlagValue)0 }, { (CommandFlagValue)0x80 });
		registry->registerOverload<ReloadCommand>("tpareload");
	}
};

void loadall() {
	string val;
	if (db->get("warps", val)) {
		RBStream rs{ val };
		rs.apply(warps);
	}
	loadCfg();
}

void tpa_entry() {
	std::filesystem::create_directory("plugins\\LLtpa");
	std::filesystem::create_directory("plugins\\LLtpa\\data");
	std::filesystem::create_directory("plugins\\LLtpa\\langpack");
	db = KVDB::create("plugins\\LLtpa\\data", true, 8);
	Translation::load("plugins/LLtpa/langpack/tpa.json");
	loadall();
	//reinitWARPGUI();
	schTask();
	Event::RegCmdEvent::subscribe([](const Event::RegCmdEvent& e) {
		if (TPA_ENABLED)	TpaCommand::setup(e.mCommandRegistry);
		if (HOME_ENABLED) {
			HomeCommand::setup(e.mCommandRegistry);
		}
		WarpCommand::setup(e.mCommandRegistry);
		if (BACK_ENABLED) BackCommand::setup(e.mCommandRegistry);
		if (SUICIDE_ENABLED) SuicideCommand::setup(e.mCommandRegistry);
		ReloadCommand::setup(e.mCommandRegistry);
		return true;
		});
	if (BACK_ENABLED) {
		Event::PlayerDieEvent::subscribe([](const Event::PlayerDieEvent&  ev) {
			ServerPlayer* sp = (ServerPlayer*)ev.mPlayer;
			deathPos[sp] = Vec4{ sp };
			sp->sendTextPacket(tr("tpa.back.use"), TextType::RAW);
			return true;
			});
	}
	logger.info("Loaded version: {}", _ver);
}