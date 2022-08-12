#pragma once
#include <I18nAPI.h>

static const I18nBase::LangData defaultLangData = {
	{"en_US", {
		 {"gmode.success", "Your game mode is changed"},
		 {"ban.list.success", "Done"},
		 {"ban.banip.success", " is banned"},
		 {"ban.ban.success", "  is banned"},
		 {"ban.unban.success", " is unbanned"},
		 {"ban.unban.error", "not banned"},
		 {"skick.success", " is kicked"},
		 {"vanish.success", "Successfully opened. When you want to cancel, please join the server again."},
		 {"cname.set.notonline", "Player not online!we will only save the custom name"},
		 {"cname.set.success", "Set success"},
		 {"cname.rm.notonline", "Player not online!we will only delete the custom name"},
		 {"cname.rm.success", "Delete success"},
		 {"cname.set.null", "Null name"},
		 {"hreload.success", "Reloaded"},
	}},
	{"zh_CN", {
		 {"gmode.success", u8"成功更改游戏模式"},
		 {"ban.list.success", u8"完成"},
		 {"ban.banip.success", u8" 被封禁"},
		 {"ban.ban.success", u8"  被封禁"},
		 {"ban.unban.success", u8" 被解封"},
		 {"ban.unban.error", u8"没有被封禁"},
		 {"skick.success", u8" 被踢出"},
		 {"vanish.success", u8"隐身成功。当你想取消时，请再次加入服务器。"},
		 {"cname.set.notonline", u8"玩家不在线！只会保存自定义名称"},
		 {"cname.set.success", u8"设置成功！"},
		 {"cname.rm.notonline", u8"玩家不在线！只会删除自定义名称。"},
		 {"cname.rm.success", u8"删除成功s"},
		 {"cname.set.null", u8"未知名字"},
		 {"hreload.success", u8"重载成功"},
	}}
};