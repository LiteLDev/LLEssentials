// This Header is auto generated by BDSLiteLoader Toolchain
#pragma once
#include <Global.h>
#define EXTRA_INCLUDE_PART_COMBATREGENERATIONCOMPONENT
#include "Extra/CombatRegenerationComponentAPI.hpp"
#undef EXTRA_INCLUDE_PART_COMBATREGENERATIONCOMPONENT
class CombatRegenerationComponent {
#include "Extra/CombatRegenerationComponentAPI.hpp"

public:
    MCAPI void tick(class Actor&);

private:
    MCAPI void _applyCombatBuffsToMob(class Actor&, class Actor&);
};