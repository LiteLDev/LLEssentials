#include <Utils/FileHelper.h>
#include <Nlohmann/json.hpp>
#include "settings.h"
namespace Settings {

    std::unordered_map<string, string> CMDMAP, CMDSCHEDULE;
    int FAKE_SEED = 114514;
    int MAX_CHAT_LEN = 96;
    std::unordered_set<short> logItems, banItems;
    bool regABILITY = true;
    bool NO_EXPLOSION = false;
    bool EXP_PLAY = true;
    bool penderman = true;
    bool pfarm = true;
    std::string LANGUAGE = "en-us";

    nlohmann::json globaljson() {
        nlohmann::json json;
        json["language"] = LANGUAGE;
        json["command_map"] = CMDMAP;
        json["timer"] = CMDSCHEDULE;
        json["ban_items"] = banItems;
        json["log_items"] = logItems;
        json["force_enable_ability"] = regABILITY;
        json["fake_seed"] = FAKE_SEED;
        json["no_explosion"] = NO_EXPLOSION;
        json["max_chat_length"] = MAX_CHAT_LEN;
        json["no_enderman_take_block"] = penderman;
        json["protect_farm_block"] = pfarm;
        return json;
    }
    void initjson(nlohmann::json json) {
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
            out.get_to(regABILITY);
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
            out.get_to(penderman);
        }
        if (json.find("protect_farm_block") != json.end()) {
            const nlohmann::json& out = json.at("protect_farm_block");
            out.get_to(pfarm);
        }
    }
    void WriteDefaultConfig(const std::string& fileName) {
        std::ofstream file(fileName);
        if (!file.is_open()) {
            std::cout << "Can't open file " << fileName << std::endl;
            return;
        }
        auto json = globaljson();
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
        initjson(json);
        WriteDefaultConfig(fileName);
    }
} // namespace Settings