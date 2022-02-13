#include<iostream>
#include<filesystem>
#include "Helper.h"
#include <LLAPI.h>

BOOL APIENTRY DllMain(HMODULE hModule,
                      DWORD ul_reason_for_call,
                      LPVOID lpReserved
) {
    switch (ul_reason_for_call) {
        case DLL_PROCESS_ATTACH:
            LL::registerPlugin("LLHelper", "A part of LLEssentials", LLHELPER_VERSION,
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