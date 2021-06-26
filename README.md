# LiteLoaderPlugins
<a href="https://github.com/LiteLDev/LiteLoaderPlugins/actions">![status](https://img.shields.io/github/workflow/status/LiteLDev/LiteLoaderPlugins/Build%20LiteLoaderPlugins?style=for-the-badge)</a>
<a href="https://t.me/liteloader">![Telegram](https://img.shields.io/badge/telegram-LiteLoader-%232CA5E0?style=for-the-badge&logo=Telegram)</a>  
Some example plugins for [LiteLoader](https://github.com/LiteLDev/BDSLiteLoader)

# Usage
[Documents](https://docs.litetitle.com/)
| Command | Description | Permission |
| --- | --- | --- |
| /gmode <player> <pode(0/1/2/3)> | Change gamemode | OP |
| /ban <ban/unban/list> [player] [time(second)] | Ban/unban a player | OP |
| /transfer <player> <IP> <port> | Transfer a player to another server | OP |
| /hreload | Reload LLHelper.json | OP |
| /skick <player>> | Force kick a player from server | OP |
| /cname <set/rm> <player> [nickname] | Set nickname for a player | OP |
| /vanish | invisibility(only effective for players who can see you) | OP |
| /tpa <to/here/ac/de/cancel/toggle> [player]	| Teleport to a player's location/teleport the player to your location/accept the teleport/refuse the teleport/cancel the teleport/change the status of whether to accept the teleport | Player |
| /warp <add/del/go/ls> [warp] | Add a warp/delete warp/go to warp/list warp | OP |
| /home <add/del/go/ls> [home] | Add a home/delete home/go home/list home | Player |

# Config
LLHelper:
```json
{
    "force_enable_expplay": false,//Enable experimental mode
    "CMDMAP": {//Use item to click block to execute a command
        "391": "me 114514"
    },
    "timer": {//Timed loop execution command
        "600": "say Welcome to the server"
    },
    "banItems": [],//Prohibited items, use ID
    "logItems": [//Items that will be recorded in the log after use, use ID
        7
    ],
    "force_enable_ability": false,//Turn on the /ability command, if the educational version is turned on, the server will be abnormal
    "FAKE_SEED": 114514,//Fake seed
    "NO_EXPLOSION": true,//Stop all explosions in the server
    "MAX_CHAT_LEN": 1919,//Maximum length of chat message
    "LOG_CHAT": true,//Log chat
    "LOG_CMD": true,//Log command
    "NoEndermanTakeBlock": true,//Stop the enderman from picking up the block
    "ProtectFarmBlock": true//Protect arable land from being trampled on
```
LLtpa:
```json
{
    "max_homes": 3,//The maximum number of homes the player can set
    "tpa_timeout": 20000,//tpa request timeout
    "tpa_ratelimit": 5000,//tpa request cooldown
    "BACK_ENABLED": true,//Enable /back command
    "SUICIDE_ENABLED": true//Enable /suicide command
}
```

# Notice
You need to download `sqlite3.dll` if you want to use LLMoney, [click here](https://sqlite.org/2021/sqlite-dll-win64-x64-3340100.zip)