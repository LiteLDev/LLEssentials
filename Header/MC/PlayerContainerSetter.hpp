// This Header is auto generated by BDSLiteLoader Toolchain
#pragma once
#include <Global.h>
#define EXTRA_INCLUDE_PART_PLAYERCONTAINERSETTER
#include "Extra/PlayerContainerSetterAPI.hpp"
#undef EXTRA_INCLUDE_PART_PLAYERCONTAINERSETTER
class PlayerContainerSetter {
#include "Extra/PlayerContainerSetterAPI.hpp"
public:
    /*0*/ virtual ~PlayerContainerSetter();
    /*1*/ virtual void setArmor(int, class ItemStack const&);
    /*2*/ virtual void setOffhandSlot(class ItemStack const&);
    /*3*/ virtual void setPlayerUIItem(int, class ItemStack const&);
};