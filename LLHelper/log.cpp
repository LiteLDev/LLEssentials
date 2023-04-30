#include "settings.h"
#include "GlobalVar.h"
#include <MC/Block.hpp>
#include <LoggerAPI.h>
#include <EventAPI.h>
#include <MC/Player.hpp>
#include <MC/ItemStack.hpp>
#include <MC/HashedString.hpp>

extern Logger logger;

bool onPlayerLeft(Event::PlayerLeftEvent e) {
	int px = e.mPlayer->getPosition().x;
	int py = e.mPlayer->getPosition().y;
	int pz = e.mPlayer->getPosition().z;
	if (px < 0)px = px - 1;
	if (pz < 0)pz = pz - 1;
	short dim = e.mPlayer->getDimensionId();
	logger.info("{} left server  Pos:({}, {}, {}, {}) xuid: {}", e.mPlayer->getRealName(), px, py, pz, dim, e.mPlayer->getXuid());
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

bool onPlayerUseItemOn(Event::PlayerUseItemOnEvent e) {
	std::string blockName = e.mBlockInstance.getBlock()->getName().getString();
	Player* sp = e.mPlayer;
	short itemId = e.mItemStack->getId();
	if (Settings::logItems.count(itemId)) {
		logger.info("[ItemLog] {} used logitem({}) on ({})", sp->getRealName(), e.mItemStack->getName(), blockName,
			e.mItemStack->toString());
	}
	if (Settings::banItems.count(itemId)) {
		logger.info("[ItemLog] {} used banitem({}) on ({})", sp->getRealName(), e.mItemStack->getName(), blockName,
			e.mItemStack->toString());
		sp->sendTextPacket("Don't use banned item");
		return false;
	}
	return true;
}