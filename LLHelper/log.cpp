#include "pch.h"
#include "Helper.h"

THook(unsigned int, "?executeCommand@MinecraftCommands@@QEBA?AUMCRESULT@@V?$shared_ptr@VCommandContext@@@std@@_N@Z",
	MinecraftCommands* self, __int64 a2, std::shared_ptr<CommandContext> cmd, char a4) {
	if (LOG_CMD) {
		auto ptr = cmd.get();
		CommandOrigin& cmdo = ptr->getOrigin();
		if (cmdo.getOriginType() == OriginType::Player) {
			auto pl = SymCall("?getEntity@PlayerCommandOrigin@@UEBAPEAVActor@@XZ", Player*, void*)(&cmdo);
			LOG1 << "[" << gettime() << u8" INFO][BH] " << offPlayer::getRealName(pl) << " CMD " << ptr->getCmd() << endl;
		}
	}
		return original(self, a2, cmd, a4);
}

THook(void*, "?_onPlayerLeft@ServerNetworkHandler@@AEAAXPEAVServerPlayer@@_N@Z",
	void* _this, ServerPlayer* a2, bool a3) {
	auto playerPos = a2->getPos();
	auto px = (int)playerPos.x;
	auto py = (int)playerPos.y;
	auto pz = (int)playerPos.z;
	if (px < 0)px = px - 1;
	if (pz < 0)pz = pz - 1;
	auto dim = a2->getDimensionId();
	LOG1 << "[" << gettime() << u8" INFO][BH] " << offPlayer::getRealName(a2) << " left server  Pos:(" << px <<","<< py <<"," << pz <<","<<dim << ") xuid: " << offPlayer::getXUID(a2) <<endl;
	return original(_this, a2, a3);
}

THook(void*, "?onPlayerJoined@ServerScoreboard@@UEAAXAEBVPlayer@@@Z",
	void* _this, Player* a2) {
	auto n = (NetworkIdentifier*)((uintptr_t)a2 + 2712);
	if (auto it = CNAME.find(offPlayer::getRealName(a2)); it != CNAME.end()) {
		a2->setName(it->second);
		optional<WPlayer> aa = WPlayer(*(ServerPlayer*)a2);
		ORIG_NAME[aa.val().v] = offPlayer::getRealName(a2);
	}
	LOG1 << "[" << gettime() << u8" INFO][BH] " << offPlayer::getRealName(a2) << " joined server IP: " << liteloader::getIP(*n) << " xuid: "<< offPlayer::getXUID(a2) <<endl;
	return original(_this, a2);
}


THook(bool, "?useItemOn@GameMode@@UEAA_NAEAVItemStack@@AEBVBlockPos@@EAEBVVec3@@PEBVBlock@@@Z",
	void* self, ItemStack* item, BlockPos* bpos, uchar a1, Vec3* plpos, Block* block) {
	const BlockLegacy* b = offBlock::getLegacyBlock(block);
	std::string blockname = dAccess<std::string, 128>(b);
	Player* sp = dAccess<Player*, 8>(self);
	auto itemid = item->getId();
	if (logItems.count(itemid)) {
		LOG1 << "[" << gettime() << u8" INFO][ItemLog] "
			<< offPlayer::getRealName(sp)
			<< " used logitem(" << item->getName() << ")"
			<< " on " << blockname
			<< "(" << bpos->toString() << ")"
			<< endl;
	}
	if (banItems.count(itemid)) {
		forceKick(sp);
	}
	return original(self, item, bpos, a1, plpos, block);
}

THook(void, "?handle@ServerNetworkHandler@@UEAAXAEBVNetworkIdentifier@@AEBVTextPacket@@@Z",
	void* self, NetworkIdentifier* id, void* text) {
	if (LOG_CHAT) {
		auto pl = SymCall("?_getServerPlayer@ServerNetworkHandler@@AEAAPEAVServerPlayer@@AEBVNetworkIdentifier@@E@Z",
			Player*, void*, void*, char)(self, id, dAccess<char, 16>(text));
		std::string msg = dAccess<std::string, 88>(text);
		if (msg.length() >= MAX_CHAT_LEN)
			return;
		LOG1 << "[" << gettime() << u8" INFO][BH] <" << offPlayer::getRealName(pl) << "> " << msg << endl;
	}
	return original(self, id, text);
}