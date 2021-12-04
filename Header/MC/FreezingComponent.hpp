// This Header is auto generated by BDSLiteLoader Toolchain
#pragma once
#include <Global.h>
#define EXTRA_INCLUDE_PART_FREEZINGCOMPONENT
#include "Extra/FreezingComponentAPI.hpp"
#undef EXTRA_INCLUDE_PART_FREEZINGCOMPONENT
class FreezingComponent {
#include "Extra/FreezingComponentAPI.hpp"

public:
    MCAPI void addAdditionalSaveData(class CompoundTag&);
    MCAPI void decreaseFreezingEffect();
    MCAPI float getFreezingEffectStrength() const;
    MCAPI void increaseFreezingEffect();
    MCAPI bool isFullyFrozen() const;
    MCAPI bool isFullyUnfrozen() const;
    MCAPI void readAdditionalSaveData(class Actor&, class CompoundTag const&, class DataLoadHelper&);
    MCAPI void resetFreezingEffect();
};