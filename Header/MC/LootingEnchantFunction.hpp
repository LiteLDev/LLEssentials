// This Header is auto generated by BDSLiteLoader Toolchain
#pragma once
#include <Global.h>
#include "LootItemFunction.hpp"
#define EXTRA_INCLUDE_PART_LOOTINGENCHANTFUNCTION
#include "Extra/LootingEnchantFunctionAPI.hpp"
#undef EXTRA_INCLUDE_PART_LOOTINGENCHANTFUNCTION
class LootingEnchantFunction : public LootItemFunction {
#include "Extra/LootingEnchantFunctionAPI.hpp"
public:
    /*0*/ virtual ~LootingEnchantFunction();
    /*1*/ virtual void apply(class ItemStack&, class Random&, class LootTableContext&);
    /*3*/ virtual void apply(class ItemInstance&, class Random&, class LootTableContext&);
};