#include "pch.h"
#include "Event.h"
#include "LLMoney.h"
#include <vector>
using namespace std;

vector<LLMoneyCallback> beforeCallbacks, afterCallbacks;

bool CallBeforeEvent(LLMoneyEvent event, xuid_t from, xuid_t to, money_t value)
{
	bool isCancelled = false;
	for (auto& callback : beforeCallbacks)
	{
		if (!callback(event, from, to, value))
		{
			isCancelled = true;
			break;
		}
	}
	return !isCancelled;
}

void CallAfterEvent(LLMoneyEvent event, xuid_t from, xuid_t to, money_t value)
{
	for (auto& callback : afterCallbacks)
	{
		callback(event, from, to, value);
	}
}

void LLMoneyListenBeforeEvent(LLMoneyCallback callback)
{
	beforeCallbacks.push_back(callback);
}

void LLMoneyListenAfterEvent(LLMoneyCallback callback)
{
	afterCallbacks.push_back(callback);
}