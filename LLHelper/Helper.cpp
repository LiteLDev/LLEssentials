#include "pch.h"
#include "Helper.h"
#include <unordered_map>
#include "commad.h"

using namespace std;
#define _ver "210703"
static Logger LOG(stdio_commit{ "[LLHelper] " });
Logger1 LOG1(".\\logs\\LLHelper.log");
unordered_map<string, string> CMDMAP, CMDSCHEDULE;
int FAKE_SEED, MAX_CHAT_LEN;
unordered_set<short> logItems, banItems;
bool LOG_CMD, LOG_CHAT, regABILITY, NO_EXPLOSION, EXP_PLAY, penderman, pfarm;
//Minecraft* mc;

void loadCfg() {
	try {
		CMDMAP.clear();
		ConfigJReader jr("plugins\\LLHelper\\LLHelper.json");
		jr.bind("CMDMAP", CMDMAP);
		jr.bind("timer", CMDSCHEDULE);
		jr.bind("FAKE_SEED", FAKE_SEED, 114514);
		jr.bind("NO_EXPLOSION", NO_EXPLOSION, false);
		jr.bind("MAX_CHAT_LEN", MAX_CHAT_LEN, 96);
		jr.bind("LOG_CHAT", LOG_CHAT, true);
		jr.bind("LOG_CMD", LOG_CMD, true);
		jr.bind("NoEndermanTakeBlock", penderman, true);
		jr.bind("ProtectFarmBlock", pfarm, true);
		jr.bind("force_enable_ability", regABILITY, true);
		vector<int> items;
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

void entry() {
	filesystem::create_directory("plugins\\LLHelper");
	loadCfg();
	REGCMD();
	LOG("Loaded version: ", _ver);
}

THook(bool, "?baseUseItem@GameMode@@QEAA_NAEAVItemStack@@@Z",
	void* self, ItemStack* item) {
	std::string id = std::to_string(item->getId());
	if (CMDMAP.count(id)) {
		Player* pl = dAccess<Player*, 8>(self);
		std::cout << offPlayer::getRealName(pl) << "\n";
		liteloader::runcmdAs(pl, CMDMAP[id]);
	}
	return original(self, item);
}

THook(void, "?setup@ChangeSettingCommand@@SAXAEAVCommandRegistry@@@Z",
	void* self) {
	if (regABILITY)
		SymCall("?setup@AbilityCommand@@SAXAEAVCommandRegistry@@@Z"
			, void, void*)(self);
	return original(self);
}
/*
THook(void, "?init@Minecraft@@QEAAXXZ", void* self) {
	original(self);
	mc = (Minecraft*)self;
}
*/