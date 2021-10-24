// dllmain.cpp : 定义 DLL 应用程序的入口点。
#include "pch.h"
#include "framework.h"
#define _ver "211023"

BOOL APIENTRY DllMain(HMODULE hModule,
	DWORD  ul_reason_for_call,
	LPVOID lpReserved
)
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
	case DLL_PROCESS_DETACH:
		break;
	}
	return TRUE;
}

static Logger LOG(stdio_commit{ "[ServerSettings] " });
std::string form = "";

void entry() {
	loaderapi::registerPlugin("ServerSettings", "Add server settings menu for BDS", _ver, "https://github.com/LiteLDev/LiteLoaderPlugins", "GPLv3");
	LOG("Loaded");
	std::ifstream fs;
	fs.open("plugins/ServerSettings/config.json", std::ios::in);
	if (fs) {
		char        buf[1024];
		while (fs.getline(buf, 1024)) {
			form.append(buf);
		}
	}
	else {
		LOG("Read config.json failed");
		form = "{\"type\":\"custom_form\",\"title\":\"LiteLoaderBDS Settings\",\"icon\":{\"type\":\"url\",\"data\":\"https://forum.litebds.com/assets/logo-6pndg21x.png\"},\"content\":[{\"type\":\"label\",\"text\":\"Hello Bedrock Dedicated Server\\nHello LiteLoaderBDS!\"}]}";
	}
}

THook(void, "?handle@?$PacketHandlerDispatcherInstance@VServerSettingsRequestPacket@@$0A@@@UEBAXAEBVNetworkIdentifier@@AEAVNetEventCallback@@AEAV?$shared_ptr@VPacket@@@std@@@Z", void* a0, NetworkIdentifier ni, void* a1, void* a2) {
	WBStream wb;
	wb.apply((VarInts<int>)5928, (MCString)form);
	MyPkt<MinecraftPacketIds(0x67)> pkt(wb);
	Handler::schedule(DelayedTask([pkt]() {
		for (Player* pl : liteloader::getAllPlayers()) {
			ServerPlayer* sp = (ServerPlayer*)pl;
			sp->sendNetworkPacket((Packet&)pkt);
		}
		}, 20));
	return original(a0, ni, a1, a2);
}

extern "C" {
	_declspec(dllexport) void onPostInit() {
		std::ios::sync_with_stdio(false);
		entry();
	}
}

