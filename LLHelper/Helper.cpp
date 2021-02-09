#include "pch.h"
#include <unordered_map>

using namespace std;

using std::unordered_map;
void InitExplodeProtect();
bool EXP_PLAY;
unordered_map<int, string> CMDMAP;
bool regABILITY;
bool fix_crash_bed_explode, FIX_PUSH_CHEST;
int FAKE_SEED;
std::unordered_set<short> logItems, banItems;
int explosion_land_dist;
bool NO_EXPLOSION;
static bool StartGamePacketMod;
static int MAX_CHAT_LEN;
static bool LOG_CMD, LOG_CHAT;
using namespace std;
long a;



#pragma warning(disable:4996)
inline string gettime()
{
	time_t rawtime;
	tm* LocTime;
	char timestr[20];
	time(&rawtime);
	LocTime = localtime(&rawtime);
	strftime(timestr, 20, "%Y-%m-%d %H:%M:%S", LocTime);
	return string(timestr);
}
void loadCfg() {
	try {
		CMDMAP.clear();
		ConfigJReader jr("config/LLHelper.json");
		jr.bind("force_enable_expplay", EXP_PLAY, false);
		jr.bind("CMDMAP", CMDMAP);
		jr.bind("force_enable_ability", regABILITY, false);
		//jr.bind("fix_crash_bed_explode", fix_crash_bed_explode, false);
		jr.bind("FIX_PUSH_CHEST", FIX_PUSH_CHEST, false);
		jr.bind("FAKE_SEED", FAKE_SEED, 114514);
		//jr.bind("explosion_land_dist", explosion_land_dist, -1);
		jr.bind("NO_EXPLOSION", NO_EXPLOSION, false);
		//jr.bind("StartGamePacketMod", StartGamePacketMod, false);
		//jr.bind("NOFIXBDS_BONEMEAL_BUG", NOFIXBDS_BONEMEAL_BUG, false);
		//jr.bind("MAX_CHAT_LEN", MAX_CHAT_LEN, 96);
		//jr.bind("LOG_CHAT", LOG_CHAT, true);
		//jr.bind("LOG_CMD", LOG_CMD, true);
		//jr.bind("NOGREYTEXT", NOGREYTEXT, true);
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
		printf("[BDXHelper] json error %s\n", e.c_str());
		throw 0;
	}
}

namespace perm {
	char getPermissionLevel(Player* _this) {
		return  *(*(char**)((uintptr_t)_this + 2216));
	}
}

THook(void*, "?fireEventPlayerMessage@MinecraftEventing@@AEAAXAEBV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@000@Z",
	void* _this, std::string& player_name, std::string& xu, std::string& msg, std::string& chat_style) {
	std::cout << "[" << gettime() << u8" INFO][BH] <"<< player_name<<"> "<< msg << endl;
	return original(_this, player_name, xu , msg , chat_style);
}

THook(unsigned int, "?executeCommand@MinecraftCommands@@QEBA?AUMCRESULT@@V?$shared_ptr@VCommandContext@@@std@@_N@Z",
	MinecraftCommands* self, __int64 a2, std::shared_ptr<CommandContext> cmd, char a4) {
	auto ptr = cmd.get();
	CommandOrigin& cmdo = ptr->getOrigin();
	auto pl = SymCall("?getEntity@PlayerCommandOrigin@@UEBAPEAVActor@@XZ", Player*, void*)(&cmdo);
	std::cout << "[" << gettime() << u8" INFO][BH] "<< pl->getNameTag() << " CMD " << ptr->getCmd() << endl;
	return original(self, a2, cmd,a4);
}

THook(void*, "?_onPlayerLeft@ServerNetworkHandler@@AEAAXPEAVServerPlayer@@_N@Z",
	void* _this, ServerPlayer* a2, bool a3) {
	std::cout << "[" << gettime() << u8" INFO][BH] " << a2->getNameTag() << " left server " << endl;
	return original(_this, a2, a3);
}

THook(void*, "?onPlayerJoined@ServerScoreboard@@UEAAXAEBVPlayer@@@Z",
	void* _this, Player* a2) {
	std::cout << "[" << gettime() << u8" INFO][BH] " << a2->getNameTag() << " joined server " << endl;
	return original(_this, a2);
}

THook(void, "?explode@Level@@QEAAXAEAVBlockSource@@PEAVActor@@AEBVVec3@@M_N3M3@Z",
	Level* _this, BlockSource* a2, Actor* a3, Vec3* a4, float a5, bool a6, bool a7, float a8, bool a9) {
	if (NO_EXPLOSION) {
		return;
	}
}

THook(void, "?explode@RespawnAnchorBlock@@CAXAEAVPlayer@@AEBVBlockPos@@AEAVBlockSource@@AEAVLevel@@@Z",
	Player* a1, BlockPos* a2, BlockSource* a3, Level* a4) {
	if (NO_EXPLOSION) {
		return;
	}
}

THook(void*, "?write@StartGamePacket@@UEBAXAEAVBinaryStream@@@Z", void* a, void* b) {
	if (FAKE_SEED) {
		dAccess<int, 40>(a) = FAKE_SEED;
	}
	return original(a, b);
}

THook(bool, "?useItem@GameMode@@UEAA_NAEAVItemStack@@@Z",
	void* _this, ItemStack& item) {
	auto sp = *reinterpret_cast<Player**>(reinterpret_cast<unsigned long long>(_this) + 8);
	cout << perm::getPermissionLevel(sp) << endl;;
	return original(_this, item);
}

void entry() {
	loadCfg();
	if (regABILITY) {
		SymCall("?setup@AbilityCommand@@SAXAEAVCommandRegistry@@@Z", void, CommandRegistry&)(LocateS<CommandRegistry>());
	}
}