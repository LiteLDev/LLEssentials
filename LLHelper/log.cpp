#include "pch.h"
#include "Helper.h"
#include <MC/Block.hpp>
extern Logger logger;

bool onPlayerLeft(Event::PlayerLeftEvent e) {
	int px = e.mPlayer->getPos().x;
	int py = e.mPlayer->getPos().y;
	int pz = e.mPlayer->getPos().z;
	if (px < 0)px = px - 1;
	if (pz < 0)pz = pz - 1;
	short dim = e.mPlayer->getDimensionId();
	logger.info("{} left server  Pos:({}, {}, {}, {}) xuid: {}", e.mPlayer->getRealName(), px, py, pz, dim, e.mXUID);
	return true;
}

bool onPlayerJoin(Event::PlayerPreJoinEvent ev) {
	Player* pl = ev.mPlayer;
	if (auto it = CNAME.find(pl->getRealName()); it != CNAME.end()) {
		pl->setName(it->second);
		ORIG_NAME[(ServerPlayer*)ev.mPlayer] = pl->getRealName();
	}
	logger.info("{} joined server IP: {} xuid: {}", pl->getRealName(), ev.mIP, ev.mXUID);
	return true;
}

THook(bool, "?useItemOn@GameMode@@UEAA_NAEAVItemStack@@AEBVBlockPos@@EAEBVVec3@@PEBVBlock@@@Z",
	GameMode* self, ItemStack* item, BlockPos* bpos, unsigned char a1, Vec3* plpos, Block* block) {
	std::string blockname = block->getName().getString();
	Player* sp = self->getPlayer();
	short itemid = item->getId();
	if (logItems.count(itemid)) {
		logger.info("[ItemLog] {} used logitem({}) on ({})", sp->getRealName(), item->getName(), blockname, bpos->toString());
	}
	if (banItems.count(itemid)) {
		sp->kick("Don't use banned item");
	}
	return original(self, item, bpos, a1, plpos, block);
}