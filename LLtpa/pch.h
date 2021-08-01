// pch.h: 这是预编译标头文件。

#ifndef PCH_H
#define PCH_H

// 添加要在此处预编译的标头
#include<lbpch.h>
#include<loader/hash.h>
#include<mc/Player.h>
#include<api/regCommandHelper.h>
#include<stl/Bstream.h>
#include<stl/KVDB.h>
#include<stl/langPack.h>
//#include<stl/LRUMap.h>
#include<ctime>

#include<api/refl/playerMap.h>
#include<api/xuidreg/xuidreg.h>
#include<stl/viewhelper.h>
#include<rapidjson/document.h>
#include<rapidjson/error/en.h>
#include<api/gui/gui.h>
using std::shared_ptr, std::pair;
using std::make_shared;
#endif //PCH_H