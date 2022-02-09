// pch.h: 这是预编译标头文件。
// 下方列出的文件仅编译一次，提高了将来生成的生成性能。
// 这还将影响 IntelliSense 性能，包括代码完成和许多代码浏览功能。
// 但是，如果此处列出的文件中的任何一个在生成之间有更新，它们全部都将被重新编译。
// 请勿在此处添加要频繁更新的文件，这将使得性能优势无效。

#ifndef PCH_H
#define PCH_H

// 添加要在此处预编译的标头
#include <iostream>
#include <streambuf>
#include <map>
#include <fstream>
#include <sstream>
#include <MC/Player.hpp>
#include <MC/Level.hpp>
#include <MC/Block.hpp>
#include <MC/BlockSource.hpp>
#include <MC/BlockSource.hpp>
#include <regCommandAPI.h>
#include <ctime>
#include <chrono>
#include <unordered_set>
#include <KVDBAPI.h>
#include <PlayerInfoAPI.h>
#include <Utils/ViewHelper.h>
#include <MC/Certificate.hpp>
#include <string>
#include <Utils/VarInt.h>
#include <Utils/PlayerMap.h>
#include <TranslationAPI.h>
#include <MC/ItemStack.hpp>
#include <EventAPI.h>
#include <MC/ServerPlayer.hpp>
#include <MC/GameMode.hpp>
#include "settings.h"
#endif //PCH_H
