﻿#include <LLAPI.h>

BOOL APIENTRY DllMain(HMODULE hModule,
                      DWORD ul_reason_for_call,
                      LPVOID lpReserved
) {
    switch (ul_reason_for_call) {
        case DLL_PROCESS_ATTACH:
            LL::registerPlugin("AntiToolbox", "Stop toolbox player from joining your server", LL::Version{2, 2, 5},
                               "https://github.com/LiteLDev/LiteLoaderPlugins", "GPLv3");
        case DLL_THREAD_ATTACH:
        case DLL_THREAD_DETACH:
        case DLL_PROCESS_DETACH:
            break;
    }
    return TRUE;
}

void entry();

extern "C" {
_declspec(dllexport)
void onPostInit() {
    std::ios::sync_with_stdio(false);
    entry();
}
}