#pragma once
#include "pch.h"

namespace perm {
	char getPermissionLevel(Player* _this) {
		return  *(*(unsigned __int8**)((uintptr_t)_this + 2216));
	}
}