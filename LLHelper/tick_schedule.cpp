#include "pch.h"
//#include "TickDo.h"
#include "Helper.h"
long long ticks;
//std::vector<std::function<void()>> func;

#include <ScheduleAPI.h>
void ScheduleCheck() {
	Schedule::repeat([] {
		for (auto& i : Settings::CMDSCHEDULE) {
			if (!(ticks % std::atoi(i.first.c_str()))) {
				Level::runcmdEx(i.second);
			}
		}
		ticks += 5;
	}, 0.5);
}