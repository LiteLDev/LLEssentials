#pragma once

bool CheckAutoUpdate(bool isUpdateManually, bool forceUpdate = false);
#define _ver "220120"
#define LLTPA_VERSION LL::Version{ 2,0, std::stoi(_ver)}

/////////////////////// LL AutoUpgrade ///////////////////////

#define LL_RELAY_INDEX "https://upgrade.litebds.com/id.json"
#define LL_UPDATE_URL_PREFIX "https://cdn.jsdelivr.net/gh/LiteLDev/Upgrade"
#define LL_UPDATE_URL_PATH "/LLtpa/LLtpa.json"

#define LL_UPDATE_CHECK_INTERVAL (10 * 60)
#define LL_UPDATE_CONNECTION_TIMEOUT 60

#define LL_UPDATE_PROGRAM "plugins/LiteLoader/LLAutoUpdate.dll"

#define LL_UPDATE_CACHE_PATH "plugins/LiteLoader/Update/"
#define LL_UPDATE_INFO_RECORD "plugins/LiteLoader/Update/Update.ini"

#define LL_UPDATE_OTHER_FILES_RECORD "plugins/LLtpa/Versions.ini"