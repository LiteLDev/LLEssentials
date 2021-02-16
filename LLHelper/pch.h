// pch.h: 这是预编译标头文件。
// 下方列出的文件仅编译一次，提高了将来生成的生成性能。
// 这还将影响 IntelliSense 性能，包括代码完成和许多代码浏览功能。
// 但是，如果此处列出的文件中的任何一个在生成之间有更新，它们全部都将被重新编译。
// 请勿在此处添加要频繁更新的文件，这将使得性能优势无效。

#ifndef PCH_H
#define PCH_H

// 添加要在此处预编译的标头
using namespace std;
#include <iostream>
#include <loader/Loader.h>
#include<streambuf>
#include <map>
#include "rapidjson/rapidjson.h"
#include "rapidjson/document.h"
#include <fstream>
#include <sstream>
#include "mc/Player.h"
#include "mc/Level.h"
#include "mc/mass.h"
#include "mc/Block.h"
#include "mc/BlockSource.h"
#include "mc/Item.h"
#include "mc/command/command.h"
#include <api/types/helper.h>
#include <api/types/types.h>
#include <ctime>
#include <chrono>
#include<unordered_set>
#include<JsonLoader.h>
#include "BDS.h"
#endif //PCH_H
