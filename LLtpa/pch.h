﻿// pch.h: 这是预编译标头文件。

#ifndef PCH_H
#define PCH_H

// 添加要在此处预编译的标头
#include <SendPacketAPI.h>
#include <KVDBAPI.h>
#include <TranslationAPI.h>
//#include<stl/LRUMap.h>
#include<ctime>

#include <Utils/PlayerMap.h>
#include <PlayerInfoAPI.h>
#include <Utils/ViewHelper.h>
#include <filesystem>
#include <EventAPI.h>
#include <MC/ServerPlayer.hpp>
#include <MC/Level.hpp>
#include <ScheduleAPI.h>
#include <MC/NetworkIdentifier.hpp>
using std::shared_ptr, std::pair;
using std::make_shared;
#endif //PCH_H