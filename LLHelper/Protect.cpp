#include "pch.h"
#include "Helper.h"

THook(void, "?explode@Level@@UEAAXAEAVBlockSource@@PEAVActor@@AEBVVec3@@M_N3M3@Z",
	Level* _this, BlockSource* a2, Actor* a3, Vec3* a4, float a5, bool a6, bool a7, float a8, bool a9) {
	if (NO_EXPLOSION) {
		return;
	}
	return original(_this, a2, a3, a4,a5,a6,a7,a8,a9);
}

THook(void, "?explode@RespawnAnchorBlock@@CAXAEAVPlayer@@AEBVBlockPos@@AEAVBlockSource@@AEAVLevel@@@Z",
	Player* a1, BlockPos* a2, BlockSource* a3, Level* a4) {
	if (NO_EXPLOSION) {
		return;
	}
	return original(a1,a2,a3,a4);
}

THook(void*, "?write@StartGamePacket@@UEBAXAEAVBinaryStream@@@Z", void* a, void* b) {
	if (FAKE_SEED) {
		dAccess<int, 48>(a) = FAKE_SEED;
	}
	return original(a, b);
}

THook(void, "?transformOnFall@FarmBlock@@UEBAXAEAVBlockSource@@AEBVBlockPos@@PEAVActor@@M@Z"
	, void* __this, void* a2, void* a3, void* a4, float a5) {
	if (pfarm) {
		return;
	}
	return original(__this, a2, a3, a4, a5);
}

THook(bool, "?canUse@EndermanTakeBlockGoal@@UEAA_NXZ",
	void* __this) {
	if (penderman) {
		return false;
	}
	return original(__this);
}