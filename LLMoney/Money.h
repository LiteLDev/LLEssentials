#include "Nlohmann/json.hpp"

#define LLMONEY_VERSION ll::Version{ 2,7,0 }

namespace Settings
{

    std::string language = "en";
    int def_money = 0;
    float pay_tax = 0.0;
    bool enable_ranking = true;

    nlohmann::json globaljson();
    void initjson(nlohmann::json json);
    void WriteDefaultConfig(const std::string &fileName);
    void LoadConfigFromJson(const std::string &fileName);
    void reloadJson(const std::string &fileName);
} // namespace Settings