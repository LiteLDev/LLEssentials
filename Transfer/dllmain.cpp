// dllmain.cpp : 定义 DLL 应用程序的入口点。
#include "pch.h"
#include "framework.h"
#include <mc/Player.h>
#define _ver "211023"

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
        loaderapi::registerPlugin("Transfer", "An Independence part of LLHelper", _ver, "https://github.com/LiteLDev/LiteLoaderPlugins", "GPLv3");
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}

static Logger LOG(stdio_commit{ "[Transfer] " });

bool onCMD_Trans(CommandOrigin const& ori, CommandOutput& outp, CommandSelector<Player>& p, string& host, optional<int> port) {
    int P = port.set ? port.val() : 19132;
    auto res = p.results(ori);
    if (!Command::checkHasTargets(res, outp)) return false;
    WBStream ws;
    ws.apply(MCString(host), (unsigned short)P);
    MyPkt<MinecraftPacketIds(0x55), false> trpk(ws);
    for (auto i : res) {
        ((ServerPlayer*)i)->sendNetworkPacket(trpk);
    }
    return true;
}

void entry() {
    LOG("plugin loaded");
    Event::addEventListener([](RegCmdEV e) {
        CMDREG::SetCommandRegistry(e.CMDRg);
        MakeCommand("transfer", "transfer player to another server", 1);
        CmdOverload(transfer, onCMD_Trans, "target", "host", "port");
        });
}

extern "C" {
    _declspec(dllexport) void onPostInit() {
        std::ios::sync_with_stdio(false);
        entry();
    }
}