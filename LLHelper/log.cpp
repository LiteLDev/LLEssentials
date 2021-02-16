#include "pch.h"
#include "Helper.h"
#include "BDS.hpp"

THook(unsigned int, "?executeCommand@MinecraftCommands@@QEBA?AUMCRESULT@@V?$shared_ptr@VCommandContext@@@std@@_N@Z",
	MinecraftCommands* self, __int64 a2, std::shared_ptr<CommandContext> cmd, char a4) {
	auto ptr = cmd.get();
	CommandOrigin& cmdo = ptr->getOrigin();
	if (cmdo.getOriginType() == OriginType::Player) {
		auto pl = SymCall("?getEntity@PlayerCommandOrigin@@UEBAPEAVActor@@XZ", Player*, void*)(&cmdo);
		LOG << "[" << gettime() << u8" INFO][BH] " << pl->getNameTag() << " CMD " << ptr->getCmd() << endl;
	}
	return original(self, a2, cmd, a4);
}

THook(void*, "?_onPlayerLeft@ServerNetworkHandler@@AEAAXPEAVServerPlayer@@_N@Z",
	void* _this, ServerPlayer* a2, bool a3) {
	LOG << "[" << gettime() << u8" INFO][BH] " << a2->getNameTag() << " left server " << endl;
	return original(_this, a2, a3);
}

THook(void*, "?onPlayerJoined@ServerScoreboard@@UEAAXAEBVPlayer@@@Z",
	void* _this, Player* a2) {
	auto n = (NetworkIdentifier*)((uintptr_t)a2 + 2536);
	LOG << "[" << gettime() << u8" INFO][BH] " << a2->getNameTag() << " joined server IP: " << liteloader::getIP(*n) << endl;
	return original(_this, a2);
}

THook(bool, "?useItemOn@GameMode@@UEAA_NAEAVItemStack@@AEBVBlockPos@@EAEBVVec3@@PEBVBlock@@@Z",
	void* self, ItemStack* item, BlockPos* bpos, uchar a1, Vec3* plpos, Block* block) {
	const BlockLegacy* b = &(block->getLegacyBlock());
	auto blockname = (std::string&)*(__int64*)((__int64)((uintptr_t)b + 128));
	auto sp = *reinterpret_cast<Player**>(reinterpret_cast<unsigned long long>(self) + 8);
	auto itemid = item->getId();
	if (logItems.count(itemid)) {
		LOG << "[" << gettime() << u8" INFO][ItemLog] "
			<< sp->getNameTag()
			<< " used logitem(" << item->getName() << ")"
			<< " on " << blockname
			<< "(" << bpos->toString() << ")"
			<< endl;
	}
	if (banItems.count(itemid)) {
		forceKick(sp, u8"You used banned item!");
	}
	return original(self, item, bpos, a1, plpos, block);
}

THook(void, "?handle@ServerNetworkHandler@@UEAAXAEBVNetworkIdentifier@@AEBVTextPacket@@@Z",
	void* self, NetworkIdentifier* id, void* text) {
	auto pl = SymCall("?_getServerPlayer@ServerNetworkHandler@@AEAAPEAVServerPlayer@@AEBVNetworkIdentifier@@E@Z",
		Player*, void*, void*, char)(self, id, *(char*)((uintptr_t)text + 16));
	auto msg = std::string(*(std::string*)((uintptr_t)text + 80));
	if (msg.length() >= MAX_CHAT_LEN)
		return;
	LOG << "[" << gettime() << u8" INFO][BH] <" << pl->getNameTag() << "> " << msg << endl;
	return original(self, id, text);
}