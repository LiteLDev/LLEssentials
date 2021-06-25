#include "pch.h"
#include "BDS.h"
#include "Helper.h"

void setPlayerGameType(Player* pl, int t) {
	SymCall("?setPlayerGameType@ServerPlayer@@UEAAXW4GameType@@@Z", void, Player*, int)(pl, t);
}

void* createPacket(int id) {
	void* ret;
	SymCall("?createPacket@MinecraftPackets@@SA?AV?$shared_ptr@VPacket@@@std@@W4MinecraftPacketIds@@@Z",
		void*, void**, int)(&ret, id);
	return ret;
}

void forceKick(Player* pl) {
	/*auto fc = [pl, msg] {
		void* network = (void*)((uintptr_t)pl + 2536); //ServerPlayer::isHostingPlayer
		SymCall("?disconnectClient@ServerNetworkHandler@@QEAAXAEBVNetworkIdentifier@@EAEBV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@_N@Z",
			void*, void*, void*, unsigned __int8, string, bool)
			(mc->getServerNetworkHandler(), network, 0, msg, 0);
	};
	func.push_back(fc);*/
	WPlayer wp = WPlayer(*pl);
	wp.forceKick();
}

void forEachPlayer(Level* lv, std::function<bool(Player*)> func) {
	SymCall("?forEachPlayer@Level@@QEBAXV?$function@$$A6A_NAEBVPlayer@@@Z@std@@@Z",
		void, void*, std::function<bool(Player*)>)(lv, func);
}