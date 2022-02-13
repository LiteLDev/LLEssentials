#pragma once

#include "LLMoney.h"

bool CallBeforeEvent(LLMoneyEvent event, xuid_t from, xuid_t to, money_t value);

void CallAfterEvent(LLMoneyEvent event, xuid_t from, xuid_t to, money_t value);