#pragma once

#include <Utils/FileHelper.h>
#include <Nlohmann/json.hpp>

namespace Settings {

    extern std::unordered_map<string, string> CMDMAP, CMDSCHEDULE;
    extern int64_t FAKE_SEED;
    extern int MAX_CHAT_LEN;
    extern std::unordered_set<short> logItems, banItems;
    extern bool REG_ABILITY;
    extern bool NO_EXPLOSION;
    extern bool EXP_PLAY;
    extern bool PROTECT_ENDERMAN;
    extern bool PROTECT_FARM;
    extern std::string LANGUAGE;
    extern bool ENABLE_TPS;

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