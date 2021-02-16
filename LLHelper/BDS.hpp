#include "pch.h"
#include "Helper.h"

void forceKick(void* pl, string msg) {
	auto fc = [pl, msg] {
		void* network = (void*)((uintptr_t)pl + 2536); //ServerPlayer::isHostingPlayer
		SymCall("?disconnectClient@ServerNetworkHandler@@QEAAXAEBVNetworkIdentifier@@EAEBV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@_N@Z",
			void*, void*, void*, unsigned __int8, string, bool)
			(mc->getServerNetworkHandler(), network, 0, msg, 0);
	};
	func.push_back(fc);
}