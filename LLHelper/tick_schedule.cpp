#include "pch.h"
//#include "TickDo.h"
#include "Helper.h"
long long ticks;
//std::vector<std::function<void()>> func;
void ScheduleCheck() {
	for (auto& i : CMDSCHEDULE) {
		if (!(ticks % std::atoi(i.first.c_str()))) {
			Level::runcmdEx(i.second);
		}
	}
}

THook(void, "?tick@Level@@UEAAXXZ", void* self) {
	original(self);
	/*size_t l = func.size();
	for (int i = 0; i < l; i++) {
		func[i]();
	}*/
	ScheduleCheck();
	//func.clear();
	ticks++;
}