#include "pch.h"
#include "loader/Loader.h"
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