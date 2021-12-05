#include "pch.h"
#include "Helper.h"
#include <MC/Block.hpp>
#include <MC/GameMode.hpp>

void onPlayerLeft(LeftEvent e) {
	int px = e.Player->getPos().x;
	int py = e.Player->getPos().y;
	int pz = e.Player->getPos().z;
	if (px < 0)px = px - 1;
	if (pz < 0)pz = pz - 1;
	auto dim = e.Player->getDimensionId();
	Logger::Info("{} left server  Pos:({}, {}, {}, {}) xuid: {}", e.Player->getRealName(), px, py, pz, (short)dim, e.xuid);
}

void onPlayerJoin(JoinEvent ev) {
	Player* pl = ev.Player;
	if (auto it = CNAME.find(pl->getRealName()); it != CNAME.end()) {
		pl->setName(it->second);
		ORIG_NAME[ev.Player] = pl->getRealName();
	}
	Logger::Info("{} joined server IP: {} xuid: {}", pl->getRealName(), ev.IP, ev.xuid);
}

THook(bool, "?useItemOn@GameMode@@UEAA_NAEAVItemStack@@AEBVBlockPos@@EAEBVVec3@@PEBVBlock@@@Z",
	GameMode* self, ItemStack* item, BlockPos* bpos, unsigned char a1, Vec3* plpos, Block* block) {
	std::string blockname = block->getNameString();
	Player* sp = self->getPlayer();
	short itemid = item->getId();
	if (logItems.count(itemid)) {
		Logger::Info("[ItemLog] {} used logitem({}) on ({})", sp->getRealName(), item->getName(), blockname, bpos->toString());
	}
	if (banItems.count(itemid)) {
		sp->kick("Don't use banned item");
	}
	return original(self, item, bpos, a1, plpos, block);
}