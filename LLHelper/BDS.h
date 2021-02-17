#pragma once
#include "tickdo.h"

void setPlayerGameType(Player* pl, int t);
void* createPacket(int id);
void forceKick(void* pl, string msg);