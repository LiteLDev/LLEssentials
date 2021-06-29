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
    std::cout << "[FakeSeed] FackSeed Loaded." << endl;
}

#define FAKE_SEED 12345
THook(void*, "?write@StartGamePacket@@UEBAXAEAVBinaryStream@@@Z", void* a, void* b) {
    if (FAKE_SEED) {
        dAccess<int, 48>(a) = FAKE_SEED;
    }
    return original(a, b);
}