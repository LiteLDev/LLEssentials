#include <Utils/FileHelper.h>
#include <Nlohmann/json.hpp>
#include "settings.h"

namespace Settings {

	std::unordered_map<string, string> CMDMAP, CMDSCHEDULE;
	int64_t FAKE_SEED = 114514;
	int MAX_CHAT_LEN = 96;
	std::unordered_set<short> logItems, banItems;
	bool REG_ABILITY = true;
	bool NO_EXPLOSION = false;
	bool EXP_PLAY = true;
	bool PROTECT_ENDERMAN = true;
	bool PROTECT_FARM = true;
	std::string LANGUAGE = "en_US";
	bool ENABLE_TPS = true;

	nlohmann::json GlobalJson() {
		nlohmann::json json;
		json["language"] = LANGUAGE;
		json["command_map"] = CMDMAP;
		json["timer"] = CMDSCHEDULE;
		json["ban_items"] = banItems;
		json["log_items"] = logItems;
		json["force_enable_ability"] = REG_ABILITY;
		json["fake_seed"] = FAKE_SEED;
		json["no_explosion"] = NO_EXPLOSION;
		json["max_chat_length"] = MAX_CHAT_LEN;
		json["no_enderman_take_block"] = PROTECT_ENDERMAN;
		json["protect_farm_block"] = PROTECT_FARM;
		json["enable_tps"] = ENABLE_TPS;
		return json;
	}

	void InitJson(nlohmann::json json) {
		if (json.find("language") != json.end()) {
			const nlohmann::json& out = json.at("language");
			out.get_to(LANGUAGE);
		}
		if (json.find("command_map") != json.end()) {
			const nlohmann::json& out = json.at("command_map");
			out.get_to(CMDMAP);
		}
		if (json.find("timer") != json.end()) {
			const nlohmann::json& out = json.at("timer");
			out.get_to(CMDSCHEDULE);
		}
		if (json.find("ban_items") != json.end()) {
			const nlohmann::json& out = json.at("ban_items");
			out.get_to(banItems);
		}
		if (json.find("log_items") != json.end()) {
			const nlohmann::json& out = json.at("log_items");
			out.get_to(logItems);
		}
		if (json.find("force_enable_ability") != json.end()) {
			const nlohmann::json& out = json.at("force_enable_ability");
			out.get_to(REG_ABILITY);
		}
		if (json.find("fake_seed") != json.end()) {
			const nlohmann::json& out = json.at("fake_seed");
			out.get_to(FAKE_SEED);
		}
		if (json.find("no_explosion") != json.end()) {
			const nlohmann::json& out = json.at("no_explosion");
			out.get_to(NO_EXPLOSION);
		}
		if (json.find("max_chat_length") != json.end()) {
			const nlohmann::json& out = json.at("max_chat_length");
			out.get_to(MAX_CHAT_LEN);
		}
		if (json.find("no_enderman_take_block") != json.end()) {
			const nlohmann::json& out = json.at("no_enderman_take_block");
			out.get_to(PROTECT_ENDERMAN);
		}
		if (json.find("protect_farm_block") != json.end()) {
			const nlohmann::json& out = json.at("protect_farm_block");
			out.get_to(PROTECT_FARM);
		}
		if (json.find("enable_tps") != json.end()) {
			const nlohmann::json& out = json.at("enable_tps");
			out.get_to(ENABLE_TPS);
		}
	}

	void WriteDefaultConfig(const std::string& fileName) {
		std::ofstream file(fileName);
		if (!file.is_open()) {
			std::cout << "Can't open file " << fileName << std::endl;
			return;
		}
		auto json = GlobalJson();
		file << json.dump(4);
		file.close();
	}

	void LoadConfigFromJson(const std::string& fileName) {
		std::ifstream file(fileName);
		if (!file.is_open()) {
			std::cout << "Can't open file " << fileName << std::endl;
			return;
		}
		nlohmann::json json;
		file >> json;
		file.close();
		InitJson(json);
		WriteDefaultConfig(fileName);
	}
} // namespace Settings
//
//#define TRJ(key, val)                                         \
//if (json.find(key) != json.end()) {                          \
//    const nlohmann::json& out = json.at(key);                \
//    out.get_to(val);}                                         \
//
//namespace TR {
//    std::string gmode_success = "Your game mode is changed";
//    std::string ban_list_success = "Done";
//    std::string ban_ip_success = " is banned";
//    std::string ban_ban_success = " is banned";
//    std::string ban_unban_success = " is unbanned";
//    std::string ban_ban_error = "not banned";
//    std::string skick_success = "is kicked";
//    std::string vanish_success = "Successfully opened. When you want to cancel, please join the server again.";
//    std::string cname_set_not_online = "Player not online!we will only save the custom name";
//    std::string cname_set_success = "Set success";
//    std::string cname_rm_not_online = "Player not online!we will only delete the custom name";
//    std::string cname_rm_success = "Delete success";
//    std::string cname_set_null = "Null name";
//    std::string hreload_success = "Reloaded";
//
//    nlohmann::json GlobalJson() {
//        nlohmann::json json;
//        json["gmode.success"] = gmode_success;
//        json["ban.list.success"] = ban_list_success;
//        json["ban.banip.success"] = ban_ip_success;
//        json["ban.ban.success"] = ban_ban_success;
//        json["ban.unban.success"] = ban_unban_success;
//        json["ban.unban.error"] = ban_ban_error;
//        json["skick.success"] = skick_success;
//        json["vanish.success"] = vanish_success;
//        json["cname.set.notonline"] = cname_set_not_online;
//        json["cname.set.success"] = cname_set_success;
//        json["cname.rm.notonline"] = cname_rm_not_online;
//        json["cname.rm.success"] = cname_rm_success;
//        json["cname.set.null"] = cname_set_null;
//        json["hreload.success"] = hreload_success;
//        return json;
//    }
//
//    void InitJson(nlohmann::json json) {
//        TRJ("gmode.success", gmode_success);
//        TRJ("ban.list.success", ban_list_success);
//        TRJ("ban.banip.success", ban_ip_success);
//        TRJ("ban.ban.success", ban_ban_success);
//        TRJ("ban.unban.success", ban_unban_success);
//        TRJ("ban.unban.error", ban_ban_error);
//        TRJ("skick.success", skick_success);
//        TRJ("vanish.success", vanish_success);
//        TRJ("cname.set.notonline", cname_set_not_online);
//        TRJ("cname.set.success", cname_set_success);
//        TRJ("cname.rm.notonline", cname_rm_not_online);
//        TRJ("cname.rm.success", cname_rm_success);
//        TRJ("cname.set.null", cname_set_null);
//        TRJ("hreload.success", hreload_success);
//    }
//
//    void WriteDefaultConfig(const std::string &fileName) {
//        std::ofstream file(fileName);
//        if (!file.is_open()) {
//            std::cout << "Can't open file " << fileName << std::endl;
//            return;
//        }
//        auto json = GlobalJson();
//        file << json.dump(4);
//        file.close();
//    }
//
//    void LoadConfigFromJson(const std::string &fileName) {
//        std::ifstream file(fileName);
//        if (!file.is_open()) {
//            std::cout << "Can't open file " << fileName << std::endl;
//            return;
//        }
//        nlohmann::json json;
//        file >> json;
//        file.close();
//        InitJson(json);
//        WriteDefaultConfig(fileName);
//    }
//}