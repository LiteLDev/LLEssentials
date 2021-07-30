#include "pch.h"
#include "Helper.h"

THook(unsigned int, "?executeCommand@MinecraftCommands@@QEBA?AUMCRESULT@@V?$shared_ptr@VCommandContext@@@std@@_N@Z",
	MinecraftCommands* self, __int64 a2, std::shared_ptr<CommandContext> cmd, char a4) {
	if (LOG_CMD) {
		auto ptr = cmd.get();
		CommandOrigin& cmdo = ptr->getOrigin();
		if (cmdo.getEntity()) {
			//if (cmdo.getOriginType() == OriginType::Player) {
			auto pl = SymCall("?getEntity@PlayerCommandOrigin@@UEBAPEAVActor@@XZ", Player*, void*)(&cmdo);
			LOG1 << "[" << gettime() << u8" INFO][BH] " << offPlayer::getRealName(pl) << " CMD " << ptr->getCmd() << endl;
		}
		//}
	}
	return original(self, a2, cmd, a4);
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

void onPlayerJoin(JoinEV e) {
	NetworkIdentifier* net = dAccess<NetworkIdentifier*, 2712>(e.Player);
	if (auto it = CNAME.find(offPlayer::getRealName(e.Player)); it != CNAME.end()) {
		e.Player->setName(it->second);
		optional<WPlayer> owp = WPlayer(*(ServerPlayer*)e.Player);
		ORIG_NAME[owp.val().v] = offPlayer::getRealName(e.Player);
	}
	LOG1 << "[" << gettime() << u8" INFO][BH] " << offPlayer::getRealName(e.Player) << " joined server IP: " << liteloader::getIP(*net) << " xuid: " << offPlayer::getXUID(e.Player) << "\n";
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