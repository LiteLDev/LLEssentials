#pragma once
#include "pch.h"
#include <mc/mass.h>
#include <mc/mass.h>
#include <functional>
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

namespace helper {
	static Minecraft* mc;
	static std::vector<std::function<void()>> func;
	unsigned __int8 getPermissionLevel(Player* _this) {
		return  *(*(unsigned __int8**)((uintptr_t)_this + 2216));
	}
	void forceKick(Player* pl, string msg) {
		auto fc = [pl, msg] {
			void* network = (void*)((uintptr_t)pl + 2512);
			SymCall("?disconnectClient@ServerNetworkHandler@@QEAAXAEBVNetworkIdentifier@@EAEBV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@_N@Z",
				__int64, void*, void*, unsigned __int8, string, char)(mc->getServerNetworkHandler(), network, 0, msg, 0);
		};
		func.push_back(fc);
	}
}
THook(void, "?init@Minecraft@@QEAAXXZ", void* self) {
	original(self);
	helper::mc = (Minecraft*)self;
}
THook(void, "?tick@Level@@UEAAXXZ", void* self) {
	for (auto i : helper::func) {
		i();
	}
	return original(self);
}