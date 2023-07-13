#pragma once

#include <Utils/PlayerMap.h>

#pragma warning(disable:4996)

#define LLHELPER_VERSION ll::Version{ 2,15,0 }

void loadCfg();

extern Minecraft *mc;
extern playerMap<string> ORIG_NAME;
extern std::unordered_map<string, string> CNAME;
