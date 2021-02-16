#include "pch.h"
#include "tickdo.h"
#include "Helper.h"
long long ticks;

void ScheduleCheck() {
	for (auto& i : CMDSCHEDULE) {
		if (!(ticks % std::atoi(i.first.c_str()))) {
			liteloader::runcmdEx(i.second);
		}
	}
}

THook(void, "?tick@Level@@UEAAXXZ", void* self) {
	original(self);
	size_t l = func.size();
	if (l) {
		for (int i = 0; i < l; i++) {
			func[i]();
		}
	}
	ScheduleCheck();
	func.clear();
	ticks++;
}