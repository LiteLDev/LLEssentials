#pragma once
#include "tickdo.h"

void setPlayerGameType(Player* pl, int t);
void* createPacket(int id);
void forceKick(void* pl, string msg);
void forEachPlayer(Level* lv, std::function<bool(Player*)> func);