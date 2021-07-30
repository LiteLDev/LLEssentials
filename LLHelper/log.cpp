#include "pch.h"
#include "Helper.h"

bool onPlayerCmd(PlayerUseCmdEV e) {
	if (LOG_CMD) {
		LOG1 << "[" << gettime() << u8" INFO][BH] " << offPlayer::getRealName(e.Player) << " CMD " << e.cmd << "\n";
	}
	return true;
}

void onPlayerLeft(LeftEV e) {
	Vec3 player_pos = e.Player->getPos();
	int px = (int)player_pos.x;
	int py = (int)player_pos.y;
	int pz = (int)player_pos.z;
	if (px < 0)px = px - 1;
	if (pz < 0)pz = pz - 1;
	auto dim = e.Player->getDimensionId();
	LOG1 << "[" << gettime() << u8" INFO][BH] " << offPlayer::getRealName(e.Player) << " left server  Pos:(" << px << "," << py << "," << pz << "," << dim << ") xuid: " << offPlayer::getXUID(e.Player) << "\n";
}

THook(void*, "?onPlayerJoined@ServerScoreboard@@UEAAXAEBVPlayer@@@Z",
	void* _this, Player* a2) {
	auto n = (NetworkIdentifier*)((uintptr_t)a2 + 2712);
	if (auto it = CNAME.find(offPlayer::getRealName(a2)); it != CNAME.end()) {
		a2->setName(it->second);
		optional<WPlayer> aa = WPlayer(*(ServerPlayer*)a2);
		ORIG_NAME[aa.val().v] = offPlayer::getRealName(a2);
	}
	LOG1 << "[" << gettime() << u8" INFO][BH] " << offPlayer::getRealName(a2) << " joined server IP: " << liteloader::getIP(*n) << " xuid: " << offPlayer::getXUID(a2) << "\n";
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
			<< "\n";
	}
	if (banItems.count(itemid)) {
		forceKick(sp);
	}
	return original(self, item, bpos, a1, plpos, block);
}

bool onPlayerChat(ChatEV e) {
	if (e.msg.length() >= MAX_CHAT_LEN) {
		return false;
	}
	LOG1 << "[" << gettime() << u8" INFO][BH] <" << offPlayer::getRealName(e.pl) << "> " << e.msg << "\n";
}