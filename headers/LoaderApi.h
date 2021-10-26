#pragma once
#include <string>
#include <unordered_map>
#ifdef LITELOADER_EXPORTS
#    define LIAPI __declspec(dllexport)
#else
#    define LIAPI __declspec(dllimport)
#endif
#define LITELOADER_VERSION "1.2.5"
#define LITELOADER_VERSION_NUMBER 19
typedef unsigned char uchar;

struct Plugin;

namespace loaderapi {
// @return 加载器版本 LiteLoader version
LIAPI std::string getLoaderVersion();
// @return 加载器版本数字 LiteLoader version number
LIAPI unsigned short getLoaderVersionNum();
// @return 是否为调试模式 Is debug mode
LIAPI bool isDebugMode();
// @return 游戏服务器版本 BDS version
LIAPI std::string getServerVersion();

// @param name         插件名         Plugin name
// @param introduction 插件介绍       Plugin introduction
// @param version      插件版本       Plugin version (example: v1.0.0.0-Beta)
// @param git          *Git仓库(链接) Git repository(URI)
// @param license      *插件许可证    Plugin license
// @param website      *网站链接      Website
// @return             注册插件的对象指针,若注册失败返回0 The pointer of ysour Plugin object
// @throws exception   插件名重复
LIAPI Plugin* registerPlugin(std::string name, std::string introduction, std::string version,
                          std::string git = "", std::string license = "", std::string website = "");
// @param name 插件名 Plugin name
// @return     若未找到则返回0 If not found, return 0
LIAPI Plugin* tryGetPluginByName(std::string name);
// @param name 插件名 Plugin name
// @return     是否存在插件 If the plugin exists
LIAPI bool hasPlugin(std::string name);
// @return 所有插件信息 The information of all the plugins
LIAPI std::unordered_map<std::string, Plugin> getAllPlugins();

};  // namespace loaderapi