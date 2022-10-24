#pragma once
#include <I18nAPI.h>

static const I18nBase::LangData defaultLangData = {
	{"en", {
		{"money.no.target", "Can not find target player."},
		{"money.invalid.arg", "Invalid command argument, or unknown error."},
		{"money.succ", "Command successfully executed."},
		{"money.not.enough", "You have insufficient balance."},
		{"money.no.perm", "You do not have the required permissions to execute this command."},
		{"money.pay.succ", "Transfer successful."},
		{"money.add.succ", "Balance successfully increased."},
		{"money.reduce.succ", "Balance successfully reduced."},
		{"money.set.succ", "Balance successfully set."},
		{"money.dontuseinconsole", "Don't use this command in console."}
	}},
	{"zh_CN", {
		{"money.no.target", u8"找不到目标"},
		{"money.invalid.arg", u8"参数错误或未知错误"},
		{"money.succ",u8"执行成功"},
		{"money.not.enough", u8"金钱不足"},
		{"money.no.perm", u8"你无权执行"},
		{"money.pay.succ", u8"支付成功"},
		{"money.add.succ", u8"添加成功"},
		{"money.reduce.succ", u8"移除成功"},
		{"money.set.succ", u8"设置成功"},
		{"money.dontuseinconsole", u8"不要在控制台使用这个指令"}
	}},
	{"zh_TW", {
		{"money.no.target", u8"找不到目標"},
		{"money.invalid.arg", u8"參數錯誤或未知錯誤"},
		{"money.succ", u8"執行成功"},
		{"money.not.enough", u8"金錢不足"},
		{"money.no.perm", u8"你沒有權限使用此指令!"},
		{"money.pay.succ", u8"支付成功"},
		{"money.add.succ", u8"添加成功"},
		{"money.reduce.succ", u8"移除成功"},
		{"money.set.succ", u8"設置成功"},
		{"money.dontuseinconsole", u8"不要在控制台使用這個指令"}
	}}
};
