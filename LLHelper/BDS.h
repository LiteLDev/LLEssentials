#pragma once
#include "tickdo.h"

void setPlayerGT(Player* pl, int t);
void* createPacket(int id);

void forceKick(void* pl, string msg);