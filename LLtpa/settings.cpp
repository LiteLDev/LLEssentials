#include <Utils/FileHelper.h>
#include <Nlohmann/json.hpp>
#include "settings.h"

#define TRJ(key, val)                                         \
if (json.find(key) != json.end()) {                          \
    const nlohmann::json& out = json.at(key);                \
    out.get_to(val);}                                        \


namespace Settings {

    int MAX_HOMES = 5;
    clock_t TPexpire = CLOCKS_PER_SEC * 20;
    clock_t TPratelimit = CLOCKS_PER_SEC * 5;
    int HOME_DISTANCE_LAND = -1;
    bool BACK_ENABLED = true;
    bool SUICIDE_ENABLED = true;
    bool TPA_ENABLED = true;
    bool HOME_ENABLED = true;
    bool TOAST_ENABLED = true;

    std::string LANGUAGE = "en-us";

    nlohmann::json GlobalJson() {
        nlohmann::json json;
        json["language"] = LANGUAGE;
        json["max_homes"] = MAX_HOMES;
        json["tpa_timeout"] = TPexpire;
        json["tpa_ratelimit"] = TPratelimit;
        json["home_land_distance"] = HOME_DISTANCE_LAND;
        json["suicide_enabled"] = SUICIDE_ENABLED;
        json["back_enabled"] = BACK_ENABLED;
        json["tpa_enabled"] = TPA_ENABLED;
        json["home_enabled"] = HOME_ENABLED;
        json["toast_enabled"] = TOAST_ENABLED;
        return json;
    }

    void InitJson(nlohmann::json json) {
        TRJ("language", LANGUAGE);
        TRJ("max_homes", MAX_HOMES);
        TRJ("tpa_timeout", TPexpire);
        TRJ("tpa_ratelimit", TPratelimit);
        TRJ("home_land_distance", HOME_DISTANCE_LAND);
        TRJ("suicide_enabled", SUICIDE_ENABLED);
        TRJ("back_enabled", BACK_ENABLED);
        TRJ("tpa_enabled", TPA_ENABLED);
        TRJ("home_enabled", HOME_ENABLED);
        TRJ("toast_enabled", TOAST_ENABLED);
    }

    void WriteDefaultConfig(const std::string &fileName) {
        std::ofstream file(fileName);
        if (!file.is_open()) {
            std::cout << "Can't open file " << fileName << std::endl;
            return;
        }
        auto json = GlobalJson();
        file << json.dump(4);
        file.close();
    }

    void LoadConfigFromJson(const std::string &fileName) {
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

//namespace TR {
//    std::string tp_fail_rate = "Tpa speed too fast";
//    std::string tp_fail_in_req = "A tpa request is in progress";
//    std::string tp_fail_blocked = "The target player blocked the Tpa request";
//    std::string tp_name_require = "Need to specify target";
//    std::string home_is_full = "Reached the upper limit of Home!";
//    std::string home_not_found = "Can not find the warp";
//    std::string home_gui_title = "Home";
//    std::string home_gui_content = "choose a home";
//    std::string warp_gui_title = "Warp System";
//    std::string warp_gui_content = "choose a warp point";
//    std::string tpa_req_a_b = " Sent a request to you that teleport to your position, using /tpa ac to accept or using /tpa de to deny";
//    std::string tpa_req_b_a = " Sent a request to you that teleport you to his position, using /tpa ac to accept or using /tpa de to deny";
//    std::string tpa_reason_deny = "Tpa request deny";
//    std::string tpa_reason_timeout = "Tpa request timeout";
//    std::string tpa_reason_accept = "Tpa request accepted";
//    std::string tpa_reason_not_online = "Target player not online";
//    std::string tpa_reason_cancel = "Tpa request cancelled";
//    std::string tpa_back_use = "Using /back to back to your death point";
//    std::string tpa_request_title = "Tpa request";
//    std::string tpa_request_accept = "Accept";
//    std::string tpa_request_deny = "Deny";
//    std::string tpa_gui_title = "Tpa Menu";
//    std::string tpa_gui_label = "Choose a player";
//    std::string tpa_gui_dropdown_1 = "Mode";
//    std::string tpa_gui_dropdown_2 = "Players";
//    std::string tpa_ac_error = "No Tpa request";
//    std::string tpa_de_error = "No Tpa request";
//
//    nlohmann::json GlobalJson() {
//        nlohmann::json json;
//        json["tp.fail.rate"] = tp_fail_rate;
//        json["tp.fail.inreq"] = tp_fail_in_req;
//        json["tp.fail.blocked"] = tp_fail_blocked;
//        json["tp.name.required"] = tp_name_require;
//        json["home.is.full"] = home_is_full;
//        json["home.not.found"] = home_not_found;
//        json["home.gui.title"] = home_gui_title;
//        json["home.gui.content"] = home_gui_content;
//        json["warp.gui.title"] = warp_gui_title;
//        json["warp.gui.content"] = warp_gui_content;
//        json["tpa.req.A_B"] = tpa_req_a_b;
//        json["tpa.req.B_A"] = tpa_req_b_a;
//        json["tpa.reason.deny"] = tpa_reason_deny;
//        json["tpa.reason.timeout"] = tpa_reason_timeout;
//        json["tpa.reason.accept"] = tpa_reason_accept;
//        json["tpa.reason.notonline"] = tpa_reason_not_online;
//        json["tpa.reason.cancel"] = tpa_reason_cancel;
//        json["tpa.back.use"] = tpa_back_use;
//        json["tpa.request.title"] = tpa_request_title;
//        json["tpa.request.accept"] = tpa_request_accept;
//        json["tpa.request.deny"] = tpa_request_deny;
//        json["tpa.gui.title"] = tpa_gui_title;
//        json["tpa.gui.label"] = tpa_gui_label;
//        json["tpa.gui.dropdown1"] = tpa_gui_dropdown_1;
//        json["tpa.gui.dropdown2"] = tpa_gui_dropdown_2;
//        json["tpa.ac.error"] = tpa_ac_error;
//        json["tpa.de.error"] = tpa_de_error;
//        return json;
//    }
//
//    void InitJson(nlohmann::json json) {
//        TRJ("tp.fail.rate", tp_fail_rate);
//        TRJ("tp.fail.inreq", tp_fail_in_req);
//        TRJ("tp.fail.blocked", tp_fail_blocked);
//        TRJ("tp.name.required", tp_name_require);
//        TRJ("home.is.full", home_is_full);
//        TRJ("home.not.found", home_not_found);
//        TRJ("home.gui.title", home_gui_title);
//        TRJ("home.gui.content", home_gui_content);
//        TRJ("warp.gui.title", warp_gui_title);
//        TRJ("warp.gui.content", warp_gui_content);
//        TRJ("tpa.req.A_B", tpa_req_a_b);
//        TRJ("tpa.req.B_A", tpa_req_b_a);
//        TRJ("tpa.reason.deny", tpa_reason_deny);
//        TRJ("tpa.reason.timeout", tpa_reason_timeout);
//        TRJ("tpa.reason.accept", tpa_reason_accept);
//        TRJ("tpa.reason.notonline", tpa_reason_not_online);
//        TRJ("tpa.reason.cancel", tpa_reason_cancel);
//        TRJ("tpa.back.use", tpa_back_use);
//        TRJ("tpa.request.title", tpa_request_title);
//        TRJ("tpa.request.accept", tpa_request_accept);
//        TRJ("tpa.request.deny", tpa_request_deny);
//        TRJ("tpa.gui.title", tpa_gui_title);
//        TRJ("tpa.gui.label", tpa_gui_label);
//        TRJ("tpa.gui.dropdown1", tpa_gui_dropdown_1);
//        TRJ("tpa.gui.dropdown2", tpa_gui_dropdown_2);
//        TRJ("tpa.ac.error", tpa_ac_error);
//        TRJ("tpa.de.error", tpa_de_error);
//
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