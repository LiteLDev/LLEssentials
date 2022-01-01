#include "pch.h"
#include <filesystem>

std::string Kick_message = u8"§cDon't use toolbox!";
std::vector<std::string> Array;
bool FakeNameDetection = true;
std::vector<std::string> CmdArray;
bool EnableCustomCmd = false;
Logger antiToolboxLogger("AntiToolbox");

void loadConfig() {
	std::string   config_file = "plugins/AntiToolbox/config.json";
	std::ifstream fs;
	fs.open(config_file, std::ios::in);
	if (!fs) {
		antiToolboxLogger.warn("{} not found, creating configuration file", config_file);
		std::filesystem::create_directory("plugins/AntiToolbox");
		std::ofstream of(config_file);
		if (of) {
			of << "{\n  \"KickMessage\": \"§cDon't use toolbox!\",\n  \"WhiteList\": [\"Notch\", \"Jeb_\"],\n  \"FakeNameDetection\": true,\n  \"EnableCustomCmd\": false,\n  \"CustomCmd\": [\"ban ban %player%\", \"say Toolbox Detected: %player%\"]\n}";
		}
		else {
			antiToolboxLogger.error("Configuration file creation failed");
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
			antiToolboxLogger.warn("Config KickMessage not found");
		}
		if (document.HasMember("WhiteList")) {
			auto arraylist = document["WhiteList"].GetArray();
			for (rapidjson::Value::ConstValueIterator itr = arraylist.Begin(); itr != arraylist.End(); ++itr) {
				Array.push_back(itr->GetString());
			}
		}
		else {
			antiToolboxLogger.warn("Config WhiteList not found");
		}
		if (document.HasMember("FakeNameDetection")) {
			FakeNameDetection = document["FakeNameDetection"].GetBool();
		}
		else {
			antiToolboxLogger.warn("Config FakeNameDetection not found");
		}
		if (document.HasMember("EnableCustomCmd")) {
			EnableCustomCmd = document["EnableCustomCmd"].GetBool();
		}
		else {
			antiToolboxLogger.warn("Config EnableCustomCmd not found");
		}
		if (document.HasMember("CustomCmd")) {
			auto arraylist = document["CustomCmd"].GetArray();
			for (rapidjson::Value::ConstValueIterator itr = arraylist.Begin(); itr != arraylist.End(); ++itr) {
				CmdArray.push_back(itr->GetString());
			}
		}
		else {
			antiToolboxLogger.warn("Config CmdArray not found");
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
		Level::runcmdEx(cmd);
	}
}

bool onPlayerLogin(Event::PlayerJoinEvent ev) {
	if (FakeNameDetection) {
		std::string real_name = ev.mPlayer->getRealName();
		std::string player_name = ev.mPlayer->getNameTag();
		if (real_name != player_name) {
			antiToolboxLogger.info("Fake Nametag detected: {} RealName: {}", player_name, real_name);
			if (!EnableCustomCmd) {
				ev.mPlayer->kick(Kick_message);
			}
			else {
				customCmdExe(real_name);
			}
		}
	}
	return true;
}

void entry() {
	antiToolboxLogger.setFile("logs/AntiToolbox.log", true);
	loadConfig();
	Event::PlayerJoinEvent::subscribe(onPlayerLogin);
	antiToolboxLogger.info("Loaded");
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
	unsigned short device_os = con_req->getDeviceOS();
	if (device_os == 1) {
		std::string pkt = base64_decode(con_req->rawToken.get()->data);
		/*std::ofstream of("packet.txt");
		if (of) {
			of << pkt << "\n";
		}*/
		rapidjson::Document document;
		document.Parse(pkt.c_str());
		std::string device_model = document["DeviceModel"].GetString();
		std::string player_name = sp->getRealName();
		if (device_model == "") {
			antiToolboxLogger.info("Null model detected: {}, using Horion client?", player_name);
			if (!EnableCustomCmd) {
				sp->kick(u8"§cNull model");
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
				std::string xuid = PlayerInfo::getXuid(pl_name);
				if (xuid == sp->getXuid()) { // WhiteList detected
					return original(thi, networkId, con_req, sp);
				}
			}
			antiToolboxLogger.info("Toolbox detected: {}", player_name);
			if (!EnableCustomCmd) {
				sp->kick(Kick_message);
			}
			else {
				customCmdExe(player_name);
			}
			return original(thi, networkId, con_req, sp);
		}
	}
	return original(thi, networkId, con_req, sp);
}