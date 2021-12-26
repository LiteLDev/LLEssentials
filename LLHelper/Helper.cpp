#include "pch.h"
#include "Helper.h"
#include <unordered_map>

std::unordered_map<string, string> CMDMAP, CMDSCHEDULE;
int FAKE_SEED, MAX_CHAT_LEN;
std::unordered_set<short> logItems, banItems;
bool regABILITY, NO_EXPLOSION, EXP_PLAY, penderman, pfarm;
Logger logger("Helper");

void loadCfg() {
	try {
		CMDMAP.clear();
		ConfigJReader jr("plugins\\LLHelper\\LLHelper.json");
		jr.bind("CMDMAP", CMDMAP);
		jr.bind("timer", CMDSCHEDULE);
		jr.bind("FAKE_SEED", FAKE_SEED, 114514);
		jr.bind("NO_EXPLOSION", NO_EXPLOSION, false);
		jr.bind("MAX_CHAT_LEN", MAX_CHAT_LEN, 96);
		jr.bind("NoEndermanTakeBlock", penderman, true);
		jr.bind("ProtectFarmBlock", pfarm, true);
		jr.bind("force_enable_ability", regABILITY, true);
		std::vector<int> items;
		logItems.clear();
		banItems.clear();
		jr.bind("logItems", items, {});
		for (auto i : items) logItems.insert(i);
		items.clear();
		jr.bind("banItems", items, {});
		for (auto i : items) banItems.insert(i);
	}
	catch (string e) {
		printf("[LLHelper] json error %s\n", e.c_str());
		throw 0;
	}
}

bool onPlayerLeft(Event::PlayerLeftEvent);
bool onPlayerJoin(Event::PlayerPreJoinEvent);
bool onPlayerUseItemOn(Event::PlayerUseItemOnEvent);
void RegisterCommands();

void entry() {
	Event::PlayerLeftEvent::subscribe(onPlayerLeft);
	Event::PlayerPreJoinEvent::subscribe(onPlayerJoin);
	Event::PlayerUseItemEvent::subscribe([] (Event::PlayerUseItemEvent e) {
		std::string id = std::to_string(e.mItemStack->getId());
		if (CMDMAP.count(id)) {
			e.mPlayer->runcmd(CMDMAP[id]);
		}
		return true;
		});
	Event::PlayerUseItemOnEvent::subscribe(onPlayerUseItemOn);
	loadCfg();
	RegisterCommands();
	logger.setFile("logs/Helper.log", true);
	logger.info("Loaded version: {}", _ver);
}
// enable ability
THook(void, "?setup@ChangeSettingCommand@@SAXAEAVCommandRegistry@@@Z",
	void* self) {
	if (regABILITY)
		SymCall("?setup@AbilityCommand@@SAXAEAVCommandRegistry@@@Z"
			, void, void*)(self);
	return original(self);
}
// setup custom name
THook(string&, "?getNameTag@Actor@@UEBAAEBV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@XZ", void* x) {
	if (auto it = ORIG_NAME._map.find((ServerPlayer*)x); it != ORIG_NAME._map.end()) {
		return it->second;
	}
	return original(x);
}