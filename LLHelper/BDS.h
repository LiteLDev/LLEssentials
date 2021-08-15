#pragma once
//#include "tickdo.h"

void setPlayerGameType(Player* pl, int t);
void* createPacket(int id);
void forceKick(Player* pl);
void forEachPlayer(Level* lv, std::function<bool(Player*)> func);