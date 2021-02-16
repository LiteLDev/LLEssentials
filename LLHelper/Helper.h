#pragma once
#include "pch.h"
#include <mc/mass.h>
#include <mc/mass.h>
#include <functional>
#pragma warning(disable:4996)

extern unordered_map<string, string> CMDMAP, CMDSCHEDULE;
extern int FAKE_SEED, MAX_CHAT_LEN;
extern unordered_set<short> logItems, banItems;
extern bool LOG_CMD, LOG_CHAT, regABILITY, NO_EXPLOSION, EXP_PLAY, penderman, pfarm;
extern Minecraft* mc;

inline string gettime()
{
	time_t rawtime;
	tm* LocTime;
	char timestr[20];
	time(&rawtime);
	LocTime = localtime(&rawtime);
	strftime(timestr, 20, "%Y-%m-%d %H:%M:%S", LocTime);
	return string(timestr);
}