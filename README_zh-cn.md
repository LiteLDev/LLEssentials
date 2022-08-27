# LiteLoaderPlugins
[![status](https://img.shields.io/github/workflow/status/LiteLDev/LiteLoaderPlugins/Build%20LiteLoaderPlugins?style=for-the-badge)](https://github.com/LiteLDev/LiteLoaderPlugins/actions")
[![Telegram](https://img.shields.io/badge/telegram-LiteLoader-%232CA5E0?style=for-the-badge&logo=Telegram)](https://t.me/liteloader)  
[English](README.md) | 简体中文  
[LiteLoaderBDS](https://github.com/LiteLDev/BDSLiteLoader)的Essentials

# 用法
## LLMoney
| 命令 | 说明 | 权限等级 |
| --- | --- | --- |
| /money query [玩家] | 查询你自己/他人的余额 | 玩家/OP |
| /money pay <玩家> <数量> | 转账给某人 | 玩家 |
| /money set <玩家> <数量> | 设置某人的余额 | OP |
| /money add <玩家> <数量> | 添加某人的余额 | OP |
| /money reduce <玩家> <数量> | 减少某人的余额 | OP |
| /money hist | 打印流水账 | 玩家 |
| /money purge | 清除流水账 | OP |
| /money top | 余额排行 | 玩家 |
| /money_s | 带有选择器支持的指令 | 玩家 |
## LLHelper
| 命令 | 说明 | 权限等级 |
| --- | --- | --- |
| /gmode <玩家> <模式(0/1/2/3)> | 切换玩家游戏模式 | OP |
| /ban <ban/unban/list> [玩家] [时间(秒)] | 封禁/解封一名玩家 | OP |
| /transfer <玩家> <IP> <端口> | 将一名玩家转移到其它服务器 | OP |
| /helper <reload/update> | 重载配置文件/检查插件更新 | OP |
| /skick <玩家> | 以暴力的方式强制踢出一名玩家 | OP |
| /cname <set/rm> <玩家> [假名] | 给玩家设置假名 | OP |
| /vanish | 隐身(仅对可以看见你的玩家有效) | OP |
| /crash <玩家> | 崩溃玩家的客户端 | OP |
| /runas <玩家> <指令> | 以目标玩家的身份执行指令 | OP |
| /tps | 查看服务器当前TPS | OP |
## LLTpa
| 命令 | 说明 | 权限等级 |
| --- | --- | --- |
| /tpa <to/here/ac/de/cancel/toggle> [玩家]	| 传送到一名玩家的位置/将玩家传送到你的位置/接受传送/拒绝传送/取消传送/改变是否接受传送的状态 | 玩家 |
| /warp <add/del/go/ls> [地标] | 添加一个地标/删除地标/前往地标/列出地标 | OP |
| /home <add/del/go/ls> [家] | 添加一个家/删除家/前往家/列出家 | 玩家 |
| /item | 查询你手上的物品信息 | 玩家 |
| /lltpa <reload/update> [是否强制: true or false] | 重载配置文件/检查插件更新 | OP |

# 配置文件
## LLHelper
```jsonc
{
    "language": "en-us", //语言
    "force_enable_expplay": false, //开启实验性模式
    "command_map": { //点地执行命令，前为ID后为命令
        "391": "me 114514"
    },
    "timer": {//定时执行命令
        "600": "say Welcome to the server"
    },
    "ban_items": [], //禁用的物品，使用ID
    "log_items": [ //使用后会被记录到日志的物品，使用ID
        7
    ],
    "force_enable_ability": false, //开启/ability命令，如果开启了教育版会导致服务器异常
    "fake_seed": 114514, //假种子
    "no_explosion": true, //禁止服务器内的所有爆炸
    "max_chat_length": 1919, //聊天信息的最大长度
    "no_enderman_take_block": true, //禁止末影人拿起方块
    "protect_farm_block": true //保护耕地不被踩踏
    "enable_tps": true //启用tps指令
}
```
## LLtpa
```jsonc
{
    "language": "en-us", //语言，改为zh-cn为中文
    "max_homes": 3, //玩家可以设置的家的最大数量
    "tpa_timeout": 20000, //tpa请求超时时间
    "tpa_ratelimit": 5000, //tpa请求冷却时间
    "back_enabled": true, //开启/back命令
    "suicide_enabled": true//开启/suicide命令
}
```
## LLMoney
```jsonc
{
    "language": "en-us", //语言，改为zh-cn为中文
    "def_money": 0, //默认金钱数
    "pay_tax": 0.0 //转账税率
}
```