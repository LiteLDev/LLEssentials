// BDXTPA.cpp : 定义 DLL 的导出函数。
//

#include "pch.h"
#include "homeStorage.h"
#include "Tpa.h"

std::unique_ptr<KVDB> db;

#pragma region structs
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


#pragma endregion
#pragma region gvals
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
#pragma endregion

#pragma region TPA
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
				A->sendText(tr("tpa.reason.accept"), TextType::RAW);
				return true;
			}
			reqs.erase(rq);
			return false;
		}
		if (A) {
			A->sendText(res == TPCloseReason::deny ? tr("tpa.reason.deny") : tr("tpa.reason.timeout"), TextType::RAW);
		}
		if (B) {
			A->sendText(res == TPCloseReason::deny ? tr("tpa.reason.deny") : tr("tpa.reason.timeout"), TextType::RAW);
		}
		reqs.erase(rq);
		return true;
	}
	else {
		//no such player
	}
}
void DoMakeReq(ServerPlayer _a, ServerPlayer _b, direction dir) {
	auto a = _a.getRealName();
	auto b = _b.getRealName();
	CHash A = do_hash(a.c_str()), B = do_hash(b.c_str());
	tpaSetting[A].lastReq = clock();
	reqs.emplace_back(dir, a, b, clock());
	string prompt = a + (dir == A_B ? tr("tpa.req.A_B") : tr("tpa.req.B_A"));
	_b.sendText(prompt, TextType::RAW);
	/*
	using namespace GUI;
	shared_ptr<RawFormBinder> x;
	char buf[1024];
	string FM{ buf,(size_t)snprintf(buf,1024,_TR("tpa.form"), prompt.c_str()) };
	sendForm(_b, RawFormBinder{ FM,[](WPlayer wp,RawFormBinder::DType i) {
		auto [clicked,res,list] = i;
		if (clicked) {
			int idx = atoi(res);
			wp.runcmdA("tpa",(idx == 0 ? "ac" : "de"));
		}
	} ,{} });*/
}

void schTask() {
	Schedule::repeat([] {
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

bool oncmd_tpa(CommandOrigin const& ori, CommandOutput& outp, MyEnum<direction> dir, CommandSelector<Player>& target) {
	auto res = target.results(ori);
	if (!Command::checkHasTargets(res, outp) || (res.count() != 1)) return false;
	ServerPlayer* t = (ServerPlayer*)*res.begin();
	auto reqres = CanMakeReq(ori.getName(), t->getName());
	switch (reqres) {
	case TPFailReason::success:
	{
		DoMakeReq({ *(ServerPlayer*)ori.getEntity() }, *t, dir);
		return true;
	}
	break;
	case TPFailReason::ratelimit: {
		outp.error(tr("tp.fail.rate"));
		return false;
	}
								break;
	case TPFailReason::inreq: {
		outp.error(tr("tp.fail.inreq"));
		return false;
	}
							break;
	case TPFailReason::blocked: {
		outp.error(tr("tp.fail.blocked"));
		return false;
	}
							  break;
	}
	return false;
}

enum class TPAOP :int {
	ac = 1, de = 2, cancel = 3, toggle = 4, gui = 5
};

std::vector<string> playerList() {
	auto plist = Level::getAllPlayers();
	std::vector<string> pl;
	for (auto p : plist) {
		pl.push_back(p->getNameTag());
	}
	return pl;
}

bool oncmd_tpa2(CommandOrigin const& ori, CommandOutput& outp, MyEnum<TPAOP> op) {
	switch (op) {
	case TPAOP::ac: {
		auto it = DoFetchReq_receiver(ori.getName());
		if (!it.set) {
			return false;
		}
		DoCloseReq(it.val(), TPCloseReason::accept);
		break;
	}
	case TPAOP::de: {
		auto it = DoFetchReq_receiver(ori.getName());
		if (!it.set) {
			return false;
		}
		DoCloseReq(it.val(), TPCloseReason::deny);
		break;
	}
	case TPAOP::cancel: {
		auto it = DoFetchReq_sender(ori.getName());
		if (!it.set) {
			return false;
		}
		DoCloseReq(it.val(), TPCloseReason::cancel);

		break;
	}
	case TPAOP::toggle: {
		CHash hs = do_hash(ori.getName().c_str());
		auto state = !tpaSetting[hs].Accept;
		tpaSetting[hs].Accept = state;
		outp.addMessage("new state " + std::to_string(state));

		break;
	}
	case TPAOP::gui: {
		ServerPlayer* wp = ori.getPlayer();
		/*
		using namespace GUI;
		auto fm = std::make_shared<FullForm>();
		fm->title = tr("tpa.gui.title");
		std::string guiLabel = tr("tpa.gui.label");
		std::string guiDropdown1 = tr("tpa.gui.dropdown1");
		std::string guiDropdown2 = tr("tpa.gui.dropdown2");
		fm->addWidget({ GUILabel(guiLabel.c_str()) });
		fm->addWidget({ GUIDropdown(guiDropdown1.c_str() ,{"to","here"}) });
		fm->addWidget({ GUIDropdown(guiDropdown2.c_str() ,playerList()) });
		sendForm(wp, FullFormBinder{ fm,{[](WPlayer P, FullFormBinder::DType data) {
			if (!data.set) return;
				auto& [d1,d2] = data.val();
				Level::runcmdAs(P, "tpa " + d2[0] + " " + QUOTE(d2[1]));
		}} });*/
		break;
	}
	}
	return true;
}
#pragma endregion

#pragma region WARP

shared_ptr<Form::SimpleForm> WARPGUI;
void reinitWARPGUI() {
	if (!WARPGUI) WARPGUI = make_shared<Form::SimpleForm>();
	WARPGUI->title = tr("warp.gui.title");
	WARPGUI->content = tr("warp.gui.content");
	//WARPGUI->reset();
	for (auto& [k, v] : warps) {
		WARPGUI->append(Form::Button(string(k)));
	}
}

void sendWARPGUI(ServerPlayer* wp) {
	/*
	using namespace GUI;
	sendForm(wp, SimpleFormBinder(WARPGUI, [](WPlayer wp, SimpleFormBinder::DType d) {
		if (d.set) {
			wp.runcmdA("warp", "go", QUOTE(d.val().second));
		}
		}));*/
}

void saveWarps() {
	WBStream ws;
	ws.apply(warps);
	db->put("warps", ws);
	reinitWARPGUI();
}
enum WARPOP :int {
	go = 1, add = 2, ls = 3, del = 4, gui = 5
};
enum class HOMEOP :int {
	go = 1, add = 2, ls = 3, del = 4, gui = 5
};
bool oncmd_warp(CommandOrigin const& ori, CommandOutput& outp, MyEnum<WARPOP> op, optional<string>& val) {
	switch (op)
	{
	case gui: {
		sendWARPGUI(ori.getPlayer());
		return true;
		break;
	}
	case add: {
		if (ori.getPermissionsLevel() < 1) return false;
		warps.emplace(val.value(), ori.getPlayer());
		saveWarps();

		break;
	}
	case del: {
		if (ori.getPermissionsLevel() < 1) return false;
		warps.erase(val.value());
		saveWarps();

		break;
	}
	case ls: {
		for (auto& i : warps) {
			outp.addMessage(i.first + " " + i.second.toStr());
		}

		break;
	}
	case go: {
		auto it = warps.find(val.value());
		if (it == warps.end()) {
			outp.error(tr("home.not.found"));
			return false;
		}
		it->second.teleport(ori.getPlayer());

		break;
	}
	default:
		break;
	}
	return true;
}
#pragma endregion

#pragma region HOME

bool generic_home(CommandOrigin const& ori, CommandOutput& outp, Homes& hm, MyEnum<HOMEOP> op, optional<string>& val) {
	switch (op)
	{
	case HOMEOP::add: {
		if (ori.getPermissionsLevel() == 0 && hm.data.size() >= MAX_HOMES) {
			outp.error(tr("home.is.full"));
			return false;
		}
		ServerPlayer* wp = ori.getPlayer();
		Vec4 vc{ wp };
		IVec2 startVc{ wp->getPos() };
		IVec2 endVc{ wp->getPos() };
		startVc += -HOME_DISTANCE_LAND;
		endVc += HOME_DISTANCE_LAND;
		/*if (!checkLandOwnerRange_stub(startVc, endVc, vc.dimid, wp.getXuid())) {
			outp.error(tr("home.near.others.land"));
			return false;
		}*/
		hm.data.emplace_back(val.value(), vc);
		hm.save();
		outp.success("home point `" + val.value() + "` was set successfully!!");

		break;
	}
	case HOMEOP::del: {
		hm.data.remove_if([&](auto& x) {
			return x.name == val.value();
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
		for (auto& i : hm.data) {
			if (i.name == val.value()) {
				i.pos.teleport(ori.getPlayer());
				return true;
			}
		}
		outp.error(tr("home.not.found"));
		return false;
		break;
	}
	case HOMEOP::gui: {
		auto wp = ori.getPlayer();
		auto HomeGUI = make_shared<Form::SimpleForm>();
		HomeGUI->title = tr("home.gui.title");
		HomeGUI->content = tr("home.gui.content");
		for (auto& i : hm.data) {
			HomeGUI->append(Form::Button(string(i.name)));
		}
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
	return true;
}
bool oncmd_home(CommandOrigin const& ori, CommandOutput& outp, MyEnum<HOMEOP> op, optional<string>& val) {
	return generic_home(ori, outp, getHomeInCache(std::stoull(ori.getPlayer()->getXuid())), op, val);
}
bool oncmd_homeAs(CommandOrigin const& ori, CommandOutput& outp, string const& target, MyEnum<HOMEOP> op, optional<string>& val) {
	return generic_home(ori, outp, getHomeInCache(std::stoull(PlayerDB::getXuid(target))), op, val);
}
#pragma endregion
#pragma region BACK
bool oncmd_back(CommandOrigin const& ori, CommandOutput& outp) {
	ServerPlayer* sp = (ServerPlayer*)ori.getEntity();
	if (!deathPos._map.count(sp)) {
		outp.error(tr("home.not.found"));
		return false;
	}
	deathPos[sp].teleport({ sp });
	deathPos._map.erase(sp);

	return true;
}
#pragma endregion
bool oncmd_suicide(CommandOrigin const& ori, CommandOutput& outp) {
	ori.getPlayer()->kill();
	return true;
}
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
		Logger::Error("JSON ERROR", e);
		throw 0;
	}
}
static bool onReload(CommandOrigin const& ori, CommandOutput& outp) {
	loadCfg();
	return true;
}
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
	db = std::make_unique<KVDB>("plugins\\LLtpa\\data", true, 8);
	Translation::load("plugins/LLtpa/langpack/tpa.json");
	Logger::setTitle("TPA");
	loadall();
	reinitWARPGUI();
	schTask();
	Event::addEventListener([](RegCmdEV e) {
		CEnum<direction> _1("tpdir", { "to","here" });
		CEnum<WARPOP> _2("warpop", { "go","add","ls","del","gui" });
		CEnum<HOMEOP> _4("homeop", { "go","add","ls","del", "gui" });
		CEnum<TPAOP> _3("tpaop", { "ac","de","cancel","toggle", "gui" });
		if (TPA_ENABLED) {
			MakeCommand("tpa", "tpa system", 0);
			CmdOverload(tpa, oncmd_tpa, "dir", "target");
			CmdOverload(tpa, oncmd_tpa2, "op");
			MakeCommand("tpareload", "reload tpa", 1);
			CmdOverload(tpareload, onReload);
		}
		if (HOME_ENABLED) {
			MakeCommand("warp", "warp system", 0);
			MakeCommand("home", "home system", 0);
			MakeCommand("homeas", "run home as a player", 1);
			CmdOverload(warp, oncmd_warp, "op", "name");
			CmdOverload(home, oncmd_home, "op", "name");
			CmdOverload(homeas, oncmd_homeAs, "Pname", "op", "home_name");
		}
		if (BACK_ENABLED) {
			MakeCommand("back", "back to last deathpoint", 0);
			CmdOverload(back, oncmd_back);
		}
		if (SUICIDE_ENABLED) {
			MakeCommand("suicide", "kill yourself", 0);
			CmdOverload(suicide, oncmd_suicide);
		}
		});
	if (BACK_ENABLED) {
		Event::addEventListener([](PlayerDeathEV  ev) {
			ServerPlayer* sp = ev.Player;
			deathPos[sp] = Vec4{ sp };
			sp->sendText(tr("tpa.back.use"), TextType::RAW);
			});
	}
	Logger::Info("Loaded version: ", _ver);
}