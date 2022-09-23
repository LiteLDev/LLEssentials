#include <minwindef.h>
#include "Tpa.h"
#include "LLAPI.h"

void tpa_entry();

BOOL APIENTRY DllMain(HMODULE hModule,
	DWORD ul_reason_for_call,
	LPVOID lpReserved
) {
	switch (ul_reason_for_call) {
	case DLL_PROCESS_ATTACH:
		ll::registerPlugin("LLtpa", "A part of LLEssentials, provides teleport function", LLTPA_VERSION,
			"https://github.com/LiteLDev/LiteLoaderPlugins", "GPLv3");
	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
	case DLL_PROCESS_DETACH:
		break;
	}
	return TRUE;
}

extern "C" {
	_declspec(dllexport)
		void onPostInit() {
		std::ios::sync_with_stdio(false);
		tpa_entry();
	}
}