# LiteLoaderPlugins
<a href="https://github.com/LiteLDev/LiteLoaderPlugins/actions">![status](https://img.shields.io/github/workflow/status/LiteLDev/LiteLoaderPlugins/Build%20LiteLoaderPlugins?style=for-the-badge)</a>
<a href="https://t.me/liteloader">![Telegram](https://img.shields.io/badge/telegram-LiteLoader-%232CA5E0?style=for-the-badge&logo=Telegram)</a>  
[English](README.md) | 简体中文  
一些[LiteLoader](https://github.com/LiteLDev/BDSLiteLoader)的示例插件

# 用法
[Documents](https://docs.litetitle.com/)
| 命令 | 说明 | 权限等级 |
| --- | --- | --- |
| /gmode <玩家> <模式(0/1/2/3)> | 切换玩家游戏模式 | OP |
| /ban <ban/unban/list> [玩家] [时间(秒)] | 封禁/解封一名玩家 | OP |
| /transfer <玩家> <IP> <端口> | 将一名玩家转移到其它服务器 | OP |
| /hreload | 重载LLHelper配置文件 | OP |
| /skick <玩家> | 以暴力的方式强制踢出一名玩家 | OP |
| /cname <set/rm> <玩家> [假名] | 给玩家设置假名 | OP |
| /vanish | 隐身(仅对可以看见你的玩家有效) | OP |
| /tpa <to/here/ac/de/cancel/toggle> [玩家]	| 传送到一名玩家的位置/将玩家传送到你的位置/接受传送/拒绝传送/取消传送/改变是否接受传送的状态 | 玩家 |
| /warp <add/del/go/ls> [地标] | 添加一个地标/删除地标/前往地标/列出地标 | OP |
| /home <add/del/go/ls> [家] | 添加一个家/删除家/前往家/列出家 | 玩家 |
| /item | 查询你手上的物品信息 | 玩家 |

# 配置文件
LLHelper:
```json
{
    "force_enable_expplay": false,//开启实验性模式
    "CMDMAP": {//点地执行命令，前为ID后为命令
        "391": "me 114514"
    },
    "timer": {//定时执行命令
        "600": "say Welcome to the server"
    },
    "banItems": [],//禁用的物品，使用ID
    "logItems": [//使用后会被记录到日志的物品，使用ID
        7
    ],
    "force_enable_ability": false,//开启/ability命令，如果开启了教育版会导致服务器异常
    "FAKE_SEED": 114514,//假种子
    "NO_EXPLOSION": true,//禁止服务器内的所有爆炸
    "MAX_CHAT_LEN": 1919,//聊天信息的最大长度
    "LOG_CHAT": true,//记录聊天
    "LOG_CMD": true,//记录命令
    "NoEndermanTakeBlock": true,//禁止末影人拿起方块
    "ProtectFarmBlock": true//保护耕地不被踩踏
}
```
LLtpa:
```json
{
    "max_homes": 3,//玩家可以设置的家的最大数量
    "tpa_timeout": 20000,//tpa请求超时时间
    "tpa_ratelimit": 5000,//tpa请求冷却时间
    "BACK_ENABLED": true,//开启/back命令
    "SUICIDE_ENABLED": true//开启/suicide命令
}
```

# 注意
如果你想要使用LLMoney，你需要下载`sqlite3.dll`，[点击下载](https://sqlite.org/2021/sqlite-dll-win64-x64-3340100.zip)