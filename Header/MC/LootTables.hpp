// This Header is auto generated by BDSLiteLoader Toolchain
#pragma once
#include <Global.h>
#define EXTRA_INCLUDE_PART_LOOTTABLES
#include "Extra/LootTablesAPI.hpp"
#undef EXTRA_INCLUDE_PART_LOOTTABLES
class LootTables {
#include "Extra/LootTablesAPI.hpp"

public:
    MCAPI class LootTable* lookupByName(std::string const&, class ResourcePackManager&);
};