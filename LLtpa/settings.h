#pragma once

#include <Utils/FileHelper.h>
#include <Nlohmann/json.hpp>

namespace Settings {
    extern int MAX_HOMES;
    extern clock_t TPexpire;
    extern clock_t TPratelimit;
    extern int HOME_DISTANCE_LAND;
    extern bool BACK_ENABLED;
    extern bool SUICIDE_ENABLED;
    extern bool TPA_ENABLED;
    extern bool HOME_ENABLED;
    extern std::string LANGUAGE;

    nlohmann::json globaljson();

    void initjson(nlohmann::json json);

    void WriteDefaultConfig(const std::string &fileName);

    void LoadConfigFromJson(const std::string &fileName);
} // namespace Settings

namespace TR {
    nlohmann::json globaljson();

    void initjson(nlohmann::json json);

    void WriteDefaultConfig(const std::string &fileName);

    void LoadConfigFromJson(const std::string &fileName);
}