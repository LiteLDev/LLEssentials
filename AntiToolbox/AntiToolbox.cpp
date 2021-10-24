#include "pch.h"
#define _ver "211023"

Logger<stdio_commit> LOG(stdio_commit("[AntiToolbox] "));
Logger1 LOG1("logs/toolbox_detected.log");
Logger1 LOG2("logs/toolbox_cannot_detect.log");

std::string Kick_message = u8"¡ìcDon't use toolbox!";
std::vector<std::string> Array;
bool FakeNameDetection = true;
std::vector<std::string> CmdArray;
bool EnableCustomCmd = false;
std::vector<std::string> Cantdetect_devices = { "OPPO","HUAWEI","MEIZU","HONOR","VIVO", "ZTE","IQOO" };

std::string getLogger() {
	return "[" + gettime() + " INFO][AntiToolbox] ";
}

void loadConfig() {
	std::string   config_file = "plugins/AntiToolbox/config.json";
	std::ifstream fs;
	fs.open(config_file, std::ios::in);
	if (!fs) {
		LOG(config_file, " not found, creating configuration file");
		std::filesystem::create_directory("plugins/AntiToolbox");
		std::ofstream of(config_file);
		if (of) {
			of << "{\n  \"KickMessage\": \"¡ìcDon't use toolbox!\",\n  \"WhiteList\": [\"Notch\", \"Jeb_\"],\n  \"FakeNameDetection\": true,\n  \"EnableCustomCmd\": false,\n  \"CustomCmd\": [\"ban ban %player%\", \"say Toolbox Detected: %player%\"]\n}";
		}
		else {
			LOG("Configuration file creation failed");
		}
	}
	else {
		std::string json;
		char        buf[1024];
		while (fs.getline(buf, 1024)) {
			json.append(buf);
		}
		rapidjson::Document document;
		document.Parse(json.c_str());
		if (document.HasMember("KickMessage")) {
			Kick_message = document["KickMessage"].GetString();
		}
		else {
			LOG("Config KickMessage not found");
		}
		if (document.HasMember("WhiteList")) {
			auto arraylist = document["WhiteList"].GetArray();
			for (rapidjson::Value::ConstValueIterator itr = arraylist.Begin(); itr != arraylist.End(); ++itr) {
				Array.push_back(itr->GetString());
			}
		}
		else {
			LOG("Config WhiteList not found");
		}
		if (document.HasMember("FakeNameDetection")) {
			FakeNameDetection = document["FakeNameDetection"].GetBool();
		}
		else {
			LOG("Config FakeNameDetection not found");
		}
		if (document.HasMember("EnableCustomCmd")) {
			EnableCustomCmd = document["EnableCustomCmd"].GetBool();
		}
		else {
			LOG("Config EnableCustomCmd not found");
		}
		if (document.HasMember("CustomCmd")) {
			auto arraylist = document["CustomCmd"].GetArray();
			for (rapidjson::Value::ConstValueIterator itr = arraylist.Begin(); itr != arraylist.End(); ++itr) {
				CmdArray.push_back(itr->GetString());
			}
		}
		else {
			LOG("Config CmdArray not found");
		}
	}
}

void customCmdExe(std::string player_name) {
	if (CmdArray.size() > 0) {
		auto spacePos = player_name.find(" ");
		if (spacePos != player_name.npos) {
			player_name = "\"" + player_name + "\"";
		}
	}
	for (std::string cmd : CmdArray) {
		auto position = cmd.find("%player%");
		if (position != cmd.npos) {
			cmd.replace(position, 9, player_name);
		}
		//std::cout << cmd << "\n";
		liteloader::runcmdEx(cmd);
	}
}

void onPlayerLogin(JoinEV ev) {
	if (FakeNameDetection) {
		std::string real_name = offPlayer::getRealName(ev.Player);
		std::string player_name = ev.Player->getNameTag();
		if (real_name != player_name) {
			LOG1 << getLogger() << "Fake Nametag detected: " << player_name << " RealName: " << real_name << "\n";
			if (!EnableCustomCmd) {
				WPlayer wp = WPlayer(*ev.Player);
				wp.kick(Kick_message);
			}
			else {
				customCmdExe(real_name);
			}
		}
	}
}

void entry() {
	loaderapi::registerPlugin("AntiToolbox", "Stop toolbox player from joining your server", _ver, "https://github.com/LiteLDev/LiteLoaderPlugins", "GPLv3");
	loadConfig();
	Event::addEventListener(onPlayerLogin);
	LOG("Loaded");
}

namespace ConnectionReq {
	unsigned short getDeviceOS(void* con_req) {
		return SymCall("?getDeviceOS@ConnectionRequest@@QEBA?AW4BuildPlatform@@XZ", unsigned short, void*)(con_req);
	}
}

std::vector<string> split(const string& str, const char pattern)
{
	std::vector<string> res;
	std::stringstream input(str);
	string temp;
	while (getline(input, temp, pattern))
	{
		res.push_back(temp);
	}
	return res;
}

THook(void, "?sendLoginMessageLocal@ServerNetworkHandler@@QEAAXAEBVNetworkIdentifier@@AEBVConnectionRequest@@AEAVServerPlayer@@@Z", ServerNetworkHandler* thi, NetworkIdentifier* networkId, ConnectionRequest* con_req, ServerPlayer* sp) {
	unsigned short device_os = ConnectionReq::getDeviceOS(con_req);
	if (device_os == 1) {
		std::string pkt = base64_decode(con_req->rawToken.get()->data);
		/*std::ofstream of("packet.txt");
		if (of) {
			of << pkt << "\n";
		}*/
		rapidjson::Document document;
		document.Parse(pkt.c_str());
		std::string device_model = document["DeviceModel"].GetString();
		std::string player_name = offPlayer::getRealName(sp);
		if (device_model == "") {
			LOG1 << getLogger() << "Null model detected: " << offPlayer::getRealName(sp) << ", using Horion client?\n";
			if (!EnableCustomCmd) {
				WPlayer wp = WPlayer(*sp);
				wp.kick(u8"¡ìcNull model");
			}
			else {
				customCmdExe(player_name);
			}
			return original(thi, networkId, con_req, sp);
		}
		const char* spl = " ";
		std::vector device_model_ = split(device_model, *spl);
		std::string device_company = device_model_[0];
		std::string device_company_ori = device_company;
		std::transform(device_company.begin(), device_company.end(), device_company.begin(), ::toupper);
		//std::cout << device_company << ":" << device_company_ori << "\n";
		if (device_company_ori != device_company) { //Toolbox detected
			for (std::string pl_name : Array) { // WhiteList detecting
				auto xuids = XIDREG::str2id(pl_name);
				xuid_t xuid = 1145141919;
				if (xuids.set) {
					xuid = xuids.val();
				}
				if (xuid == offPlayer::getXUID(sp)) { // WhiteList detected
					return original(thi, networkId, con_req, sp);
				}
			}
			LOG1 << getLogger() << "Toolbox detected: " << player_name << "\n";
			if (!EnableCustomCmd) {
				WPlayer wp = WPlayer(*sp);
				wp.kick(Kick_message);
			}
			else {
				customCmdExe(player_name);
			}
			return original(thi, networkId, con_req, sp);
		}
		for (std::string device_ : Cantdetect_devices) {
			if (device_company == device_) {
				LOG2 << getLogger() << "Cannot detect: " << offPlayer::getRealName(sp) << "\n";
				return original(thi, networkId, con_req, sp);
			}
		}
	}
	return original(thi, networkId, con_req, sp);
}