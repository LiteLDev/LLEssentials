#include "pch.h"
#include "lbpch.h"
#include "mc/OffsetHelper.h"
#include "mc/core.h"
#include "mc/block.h"
#include "mc/item.h"
#include "mc/mass.h"
#include "api/commands.h"
#include "api/Basic_Event.h"
#include "loader/Loader.h"
#include "mc/BlockSource.h"
#include "mc/Block.h"
#include "mc/Player.h"
#include <iostream>
#include <string>
using namespace std;

void entry()
{
    std::cout << "[CoResourcePack] Client Resource unlocked." << endl;
}


THook(void*, "?write@ResourcePacksInfoPacket@@UEBAXAEAVBinaryStream@@@Z", void* a, void* b)
{
    dAccess<bool, 48>(a) = true;
    return original(a, b);
}