#pragma once

#include <Utils/FileHelper.h>
#include <Nlohmann/json.hpp>

namespace Settings {

    extern std::unordered_map<string, string> CMDMAP, CMDSCHEDULE;
    extern int FAKE_SEED;
    extern int MAX_CHAT_LEN;
    extern std::unordered_set<short> logItems, banItems;
    extern bool regABILITY;
    extern bool NO_EXPLOSION;
    extern bool EXP_PLAY;
    extern bool penderman;
    extern bool pfarm;
    extern std::string LANGUAGE;

    nlohmann::json GlobalJson();

    void InitJson(nlohmann::json json);

    void WriteDefaultConfig(const std::string &fileName);

    void LoadConfigFromJson(const std::string &fileName);
} // namespace Settings

//namespace TR {
//    nlohmann::json GlobalJson();
//
//    void InitJson(nlohmann::json json);
//
//    void WriteDefaultConfig(const std::string &fileName);
//
//    void LoadConfigFromJson(const std::string &fileName);
//}