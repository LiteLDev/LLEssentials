#include "pch.h"
#include "Helper.h"
#include <unordered_map>

using namespace std;
Logger LOG("./liteloader.log");
unordered_map<string, string> CMDMAP, CMDSCHEDULE;
int FAKE_SEED, MAX_CHAT_LEN;
unordered_set<short> logItems, banItems;
bool LOG_CMD, LOG_CHAT, regABILITY, NO_EXPLOSION, EXP_PLAY, penderman, pfarm;
Minecraft* mc;

void loadCfg() {
	try {
		CMDMAP.clear();
		ConfigJReader jr("config/LLHelper.json");
		jr.bind("CMDMAP", CMDMAP);
		jr.bind("timer", CMDSCHEDULE);
		jr.bind("FAKE_SEED", FAKE_SEED, 114514);
		jr.bind("NO_EXPLOSION", NO_EXPLOSION, false);
		jr.bind("MAX_CHAT_LEN", MAX_CHAT_LEN, 96);
		jr.bind("LOG_CHAT", LOG_CHAT, true);
		jr.bind("LOG_CMD", LOG_CMD, true);
		jr.bind("NoEndermanTakeBlock", penderman, true);
		jr.bind("ProtectFarmBlock", pfarm, true);
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
	loadCfg();
}

THook(bool, "?useItem@GameMode@@UEAA_NAEAVItemStack@@@Z",
	void* self, ItemStack* item) {
	std::string id = std::to_string(item->getId());
	if (CMDMAP.count(id)) {
		auto sp = *reinterpret_cast<Player**>(reinterpret_cast<unsigned long long>(self) + 8);
		liteloader::runcmd("execute \"" + offPlayer::getRealName(sp) + "\" ~~~ " + CMDMAP[id]);
	}
}

THook(void, "?init@Minecraft@@QEAAXXZ", void* self) {
	original(self);
	mc = (Minecraft*)self;
}