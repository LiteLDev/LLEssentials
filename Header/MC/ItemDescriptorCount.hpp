// This Header is auto generated by BDSLiteLoader Toolchain
#pragma once
#include <Global.h>
#define EXTRA_INCLUDE_PART_ITEMDESCRIPTORCOUNT
#include "Extra/ItemDescriptorCountAPI.hpp"
#undef EXTRA_INCLUDE_PART_ITEMDESCRIPTORCOUNT
class ItemDescriptorCount {
#include "Extra/ItemDescriptorCountAPI.hpp"

public:
    MCAPI short getStackSize() const;
    MCAPI void setStackSize(short);
};