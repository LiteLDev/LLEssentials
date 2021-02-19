#include"pch.h"
#include<Llland.h>
#include"framework.h"
bool checkLandOwnerRange_stub(IVec2 vc, IVec2 vc2, int dim, unsigned long long xuid) {
	static bool inited = false;
	static decltype(&checkLandOwnerRange) ptr = nullptr;
	if (!inited) {
		auto handle = LoadLibraryA("LLland.dll");
		if (handle) {
			ptr = (decltype(ptr))GetProcAddress(handle, "checkLandOwnerRange");
		}
		else {
			//?handle@ServerNetworkHandler@@UEAAXAEBVNetworkIdentifier@@AEBVCommandBlockUpdatePacket@@@Z
			printf("error1\n");
		}
		if (!ptr) {
			printf("[Home/WARNING] cant find LLland ,home_land_distance wont work!!!\n");
		}
	}
	if (ptr) return ptr(vc, vc2, dim, xuid); else return true;
}