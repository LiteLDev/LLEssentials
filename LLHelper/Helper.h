#pragma once

#include <Utils/PlayerMap.h>

#pragma warning(disable:4996)

#define LLHELPER_VERSION ll::Version{ 2,7,0 }

/////////////////////// LL AutoUpgrade ///////////////////////

#define LL_RELAY_INDEX "https://upgrade.litebds.com/id.json"
#define LL_UPDATE_URL_PREFIX "https://cdn.jsdelivr.net/gh/LiteLDev/Upgrade"
#define LL_UPDATE_URL_PATH "/LLhelper/LLhelper.json"

#define LL_UPDATE_CHECK_INTERVAL (10 * 60)
#define LL_UPDATE_CONNECTION_TIMEOUT 60

#define LL_UPDATE_PROGRAM "plugins/LiteLoader/LLAutoUpdate.dll"

#define LL_UPDATE_CACHE_PATH "plugins/LiteLoader/Update/"
#define LL_UPDATE_INFO_RECORD "plugins/LiteLoader/Update/Update.ini"

#define LL_UPDATE_OTHER_FILES_RECORD "plugins/LLhelper/Versions.ini"

void loadCfg();

extern Minecraft* mc;
extern playerMap<string> ORIG_NAME;
extern std::unordered_map<string, string> CNAME;
