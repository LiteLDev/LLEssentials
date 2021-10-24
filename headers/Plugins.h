#pragma once
#include <string>
#include <unordered_map>
#include <minwindef.h>

struct Plugin {
    //std::string id;
    std::string  name;
    std::string  introduction;
    std::string  version;

    std::string  git;
    std::string  license;
    std::string  website;

    std::wstring filePath;
    HMODULE      handler;
};

// 这些函数未导出,仅供LiteLoader.dll内部使用,开发者使用loaderapi中的内容!!!
bool registerPlugin(std::string name, std::string introduction, std::string version,
                    std::string git = "", std::string license = "", std::string website = "");
void completePluginInfo(std::string pluginName, std::wstring filePath, HMODULE handler);
std::unordered_map<std::string, Plugin>& getAllPlugins();