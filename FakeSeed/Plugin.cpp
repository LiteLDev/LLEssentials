#include "pch.h"
#include "loader/Loader.h"
#include <iostream>
#include <fstream>
#include <string>
#include <filesystem>
using namespace std;

#define CONF_PATH "./plugins/FakeSeed/seed.txt"
int seed = -2138562307;

void entry()
{
    try
    {
        if (!filesystem::exists(CONF_PATH))
        {
            filesystem::create_directories("./plugins/FakeSeed");
            ofstream fout(CONF_PATH);
            fout << seed << endl;
        }
        else
        {
            ifstream fin(CONF_PATH);
            if (fin)
                fin >> seed;
        }
    }
    catch(...)  { }
    std::cout << "[FakeSeed] FackSeed Loaded." << endl;
    std::cout << "[FakeSeed] Seed is set to " << seed << endl;
}

THook(void*, "?write@StartGamePacket@@UEBAXAEAVBinaryStream@@@Z", void* a, void* b)
{
    dAccess<int, 48>(a) = seed;
    return original(a, b);
}