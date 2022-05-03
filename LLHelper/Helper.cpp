#include "settings.h"
#include "Helper.h"
#include <unordered_map>
#include <ScheduleAPI.h>
#include <filesystem>
#include <LoggerAPI.h>
#include <EventAPI.h>
#include <MC/ServerPlayer.hpp>
#include <MC/Level.hpp>
#include <MC/ItemStack.hpp>
#include <thread>
#include <chrono>

vector<unsigned int> taskList;
Logger logger("Helper");
unsigned short ticks = 0;
unsigned short Tick_per_second;
unsigned short Tick_per_minute;
std::list<unsigned short> ticks_per_minute;

void loadCfg() {
	//config
	if (!std::filesystem::exists("plugins/LLHelper"))
		std::filesystem::create_directories("plugins/LLHelper");
	for (unsigned int taskId : taskList) { //Remove all tasks
		ScheduleTask task(taskId);
		task.cancel();
	}
	if (std::filesystem::exists("plugins/LLHelper/LLHelper.json")) {
		try {
			Settings::LoadConfigFromJson("plugins/LLHelper/LLHelper.json");
		}
		catch (std::exception& e) {
			logger.error("Config File isInvalid, Err {}", e.what());
			Sleep(1000 * 100);
			exit(1);
		}
		catch (...) {
			logger.error("Config File isInvalid");
			Sleep(1000 * 100);
			exit(1);
		}
	}
	else {
		logger.info("Config with default values created");
		Settings::WriteDefaultConfig("plugins/LLHelper/LLHelper.json");
	}
	//tr
//    if (!std::filesystem::exists("plugins/LLHelper/langpack"))
//        std::filesystem::create_directories("plugins/LLHelper/langpack");
//    if (std::filesystem::exists("plugins/LLHelper/langpack/en-us.json")) {
//        try {
//            TR::LoadConfigFromJson("plugins/LLHelper/langpack/en-us.json");
//        }
//        catch (std::exception &e) {
//            logger.error("Config File isInvalid, Err {}", e.what());
//            Sleep(1000 * 100);
//            exit(1);
//        }
//        catch (...) {
//            logger.error("Config File isInvalid");
//            Sleep(1000 * 100);
//            exit(1);
//        }
//    } else {
//        logger.info("Config with default values created");
//        TR::WriteDefaultConfig("plugins/LLHelper/langpack/en-us.json");
//    }
}

void scheduleTask() {
	for (auto timer : Settings::CMDSCHEDULE) {
		std::string taskCmd = timer.second;
		unsigned long long taskTick = std::stoull(timer.first);
		ScheduleTask tsk = Schedule::repeat([taskCmd] {
			Level::runcmdEx(taskCmd);
			}, taskTick);
		taskList.push_back(tsk.getTaskId());
	}
	if (Settings::ENABLE_TPS) {
		Schedule::repeat([]() {
			ticks++;
			}, 1);
		std::thread([] {
			while (true) {
				std::this_thread::sleep_for(std::chrono::seconds(1));
				if (ticks > 20) {
					ticks = 20;
				}
				Tick_per_second = ticks;
				ticks_per_minute.push_back(ticks);
				ticks = 0;
				if (ticks_per_minute.size() >= 60) {
					ticks_per_minute.clear();
					continue;
				}
				unsigned short ticks_minute = 0;
				for (unsigned short i : ticks_per_minute) {
					ticks_minute = ticks_minute + i;
				}
				Tick_per_minute = ticks_minute / ticks_per_minute.size();
			}
			})
			.detach();
	}
}

bool onPlayerLeft(Event::PlayerLeftEvent);

bool onPlayerJoin(Event::PlayerPreJoinEvent);

bool onPlayerUseItemOn(Event::PlayerUseItemOnEvent);

void RegisterCommands();

void entry() {
	Event::PlayerLeftEvent::subscribe(onPlayerLeft);
	Event::PlayerPreJoinEvent::subscribe(onPlayerJoin);
	Event::PlayerUseItemEvent::subscribe([](Event::PlayerUseItemEvent e) {
		std::string id = std::to_string(e.mItemStack->getId());
		if (Settings::CMDMAP.count(id)) {
			e.mPlayer->runcmd(Settings::CMDMAP[id]);
		}
		return true;
		});
	Event::PlayerUseItemOnEvent::subscribe(onPlayerUseItemOn);
	Event::PlayerChatEvent::subscribe([](Event::PlayerChatEvent e) {
		if (e.mMessage.size() >= Settings::MAX_CHAT_LEN) {
			e.mPlayer->sendText(u8"§cDon't spam");
			return false;
		}
		return true;
		});
	Event::ServerStartedEvent::subscribe([](const Event::ServerStartedEvent& ev) {
		std::thread th([]() {
			CheckAutoUpdate(true, false);
			});
		th.detach();
		return true;
		});
	loadCfg();
	RegisterCommands();
	scheduleTask();
	logger.setFile("logs/Helper.log", true);
	logger.info("Loaded version: {}", LLHELPER_VERSION.toString());
}
// enable ability
THook(void, "?setup@ChangeSettingCommand@@SAXAEAVCommandRegistry@@@Z",
	void* self) {
	if (Settings::REG_ABILITY)
		SymCall("?setup@AbilityCommand@@SAXAEAVCommandRegistry@@@Z", void, void*)(self);
	return original(self);
}
// setup custom name
THook(string&, "?getNameTag@Actor@@UEBAAEBV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@XZ", void* x) {
	if (auto it = ORIG_NAME._map.find((ServerPlayer*)x); it != ORIG_NAME._map.end()) {
		return it->second;
	}
	return original(x);
}