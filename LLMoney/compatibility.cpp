#include "LLMoney.h"
#include <string>

using std::string;

// Old interface
// Just for compatibility
// Do not use
namespace Money
{
	money_t getMoney(xuid_t xuid) { return LLMoneyGet(xuid); }

	string getTransHist(xuid_t xuid, int timediff) { return LLMoneyGetHist(xuid, timediff); }

	bool createTrans(xuid_t from, xuid_t to, money_t val, string const &note)
	{
		return LLMoneyTrans(from, to, val, note);
	}

	bool setMoney(xuid_t xuid, money_t money) { return LLMoneySet(xuid, money); }

	bool reduceMoney(xuid_t xuid, money_t money) { return LLMoneyReduce(xuid, money); }

	void purgeHist(int difftime) { return LLMoneyClearHist(difftime); }
}