#include "pch.h"
#include<streambuf>
#include <map>
#include "rapidjson/rapidjson.h"
#include "rapidjson/document.h"
#include <fstream>
#include <sstream>
#include "mc/Player.h"
#include <ctime>
#include <chrono>


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