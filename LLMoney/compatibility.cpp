#include "pch.h"
#include "LLMoney.h"
#include <string>
using std::string;

// Old interface
// Just for compatibility
// Do not use
namespace Money
{
	LLMONEY_API money_t getMoney(xuid_t xuid) { return LLMoneyGet(xuid); }
	LLMONEY_API string getTransHist(xuid_t xuid, int timediff) { return LLMoneyGetHist(xuid, timediff); }
	LLMONEY_API bool createTrans(xuid_t from, xuid_t to, money_t val, string const& note) { return LLMoneyTrans(from, to, val, note); }
	LLMONEY_API bool setMoney(xuid_t xuid, money_t money) { return LLMoneySet(xuid, money); }
	LLMONEY_API bool reduceMoney(xuid_t xuid, money_t money) { return LLMoneyReduce(xuid, money); }
	LLMONEY_API void purgeHist(int difftime) { return LLMoneyClearHist(difftime); }
}