#include <Utils/FileHelper.h>
#include <Nlohmann/json.hpp>
#include "settings.h"

#define TRJ(key,val)                                         \
if (json.find(key) != json.end()) {                          \
    const nlohmann::json& out = json.at(key);                \
    out.get_to(val);}                                        \


namespace Settings {

    extern int MAX_HOMES =5;
    extern clock_t TPexpire = CLOCKS_PER_SEC * 20;
    extern clock_t TPratelimit = CLOCKS_PER_SEC * 5;
    extern int HOME_DISTANCE_LAND = -1;
    extern bool BACK_ENABLED = true;
    extern bool SUICIDE_ENABLED = true;
    extern bool TPA_ENABLED = true;
    extern bool HOME_ENABLED = true;
    std::string LANGUAGE = "en-us";

    nlohmann::json globaljson() {
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
        return json;
    }
    void initjson(nlohmann::json json) {
        TRJ("language", LANGUAGE);
        TRJ("max_homes", MAX_HOMES);
        TRJ("tpa_timeout", TPexpire);
        TRJ("tpa_ratelimit", TPratelimit);
        TRJ("home_land_distance", HOME_DISTANCE_LAND);
        TRJ("suicide_enabled", SUICIDE_ENABLED);
        TRJ("back_enabled", BACK_ENABLED);
        TRJ("tpa_enabled", TPA_ENABLED);
        TRJ("home_enabled", HOME_ENABLED);
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

namespace TR {
    string tpfailrate = "Tpa speed too fast";
    string tpfailinreq = "A tpa request is in progress";
    string tpfailblocked = "The target player blocked the Tpa request";
    string tpnamerequired = "Need to specify target";
    string homeisfull = "Reached the upper limit of Home!";
    string homenotfound = "Can not find the warp";
    string homeguititle = "Home";
    string homeguicontent = "choose a home";
    string warpguititle = "Warp System";
    string warpguicontent = "choose a warp point";
    string tpareqA_B = " Sent a request to you that teleport to your position, using /tpa ac to accept or using /tpa de to deny";
    string tpareqB_A = " Sent a request to you that teleport you to his position, using /tpa ac to accept or using /tpa de to deny";
    string tpareasondeny = "Tpa request deny";
    string tpareasontimeout = "Tpa request timeout";
    string tpareasonaccept = "Tpa request accepted";
    string tpareasonnotonline = "Target player not online";
    string tpareasoncancel = "Tpa request cancelled";
    string tpabackuse = "Using /back to back to your death point";
    string tparequesttitle = "Tpa request";
    string tparequestaccept = "Accept";
    string tparequestdeny = "Deny";
    string tpaguititle = "Tpa Menu";
    string tpaguilabel = "Choose a player";
    string tpaguidropdown1 = "Mode";
    string tpaguidropdown2 = "Players";
    string tpaacerror = "No Tpa request";
    string tpadeerror = "No Tpa request";
    nlohmann::json globaljson() {
        nlohmann::json json;
        json["tp.fail.rate"] = tpfailrate;
        json["tp.fail.inreq"] = tpfailinreq;
        json["tp.fail.blocked"] = tpfailblocked;
        json["tp.name.required"] = tpnamerequired;
        json["home.is.full"] = homeisfull;
        json["home.not.found"] = homenotfound;
        json["home.gui.title"] = homeguititle;
        json["home.gui.content"] = homeguicontent;
        json["warp.gui.title"] = warpguititle;
        json["warp.gui.content"] = warpguicontent;
        json["tpa.req.A_B"] = tpareqA_B;
        json["tpa.req.B_A"] = tpareqB_A;
        json["tpa.reason.deny"] = tpareasondeny;
        json["tpa.reason.timeout"] = tpareasontimeout;
        json["tpa.reason.accept"] = tpareasonaccept;
        json["tpa.reason.notonline"] = tpareasonnotonline;
        json["tpa.reason.cancel"] = tpareasoncancel;
        json["tpa.back.use"] = tpabackuse;
        json["tpa.request.title"] = tparequesttitle;
        json["tpa.request.accept"] = tparequestaccept;
        json["tpa.request.deny"] = tparequestdeny;
        json["tpa.gui.title"] = tpaguititle;
        json["tpa.gui.label"] = tpaguilabel;
        json["tpa.gui.dropdown1"] = tpaguidropdown1;
        json["tpa.gui.dropdown2"] = tpaguidropdown2;
        json["tpa.ac.error"] = tpaacerror;
        json["tpa.de.error"] = tpadeerror;
        return json;
    }
    void initjson(nlohmann::json json) {
        TRJ("tp.fail.rate", tpfailrate);
        TRJ("tp.fail.inreq", tpfailinreq);
        TRJ("tp.fail.blocked", tpfailblocked);
        TRJ("tp.name.required", tpnamerequired);
        TRJ("home.is.full", homeisfull);
        TRJ("home.not.found", homenotfound);
        TRJ("home.gui.title", homeguititle);
        TRJ("home.gui.content", homeguicontent);
        TRJ("warp.gui.title", warpguititle);
        TRJ("warp.gui.content", warpguicontent);
        TRJ("tpa.req.A_B", tpareqA_B);
        TRJ("tpa.req.B_A", tpareqB_A);
        TRJ("tpa.reason.deny", tpareasondeny);
        TRJ("tpa.reason.timeout", tpareasontimeout);
        TRJ("tpa.reason.accept", tpareasonaccept);
        TRJ("tpa.reason.notonline", tpareasonnotonline);
        TRJ("tpa.reason.cancel", tpareasoncancel);
        TRJ("tpa.back.use", tpabackuse);
        TRJ("tpa.request.title", tparequesttitle);
        TRJ("tpa.request.accept", tparequestaccept);
        TRJ("tpa.request.deny", tparequestdeny);
        TRJ("tpa.gui.title", tpaguititle);
        TRJ("tpa.gui.label", tpaguilabel);
        TRJ("tpa.gui.dropdown1", tpaguidropdown1);
        TRJ("tpa.gui.dropdown2", tpaguidropdown2);
        TRJ("tpa.ac.error", tpaacerror);
        TRJ("tpa.de.error", tpadeerror);

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
}