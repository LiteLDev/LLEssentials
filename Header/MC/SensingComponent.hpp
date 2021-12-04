// This Header is auto generated by BDSLiteLoader Toolchain
#pragma once
#include <Global.h>
#define EXTRA_INCLUDE_PART_SENSINGCOMPONENT
#include "Extra/SensingComponentAPI.hpp"
#undef EXTRA_INCLUDE_PART_SENSINGCOMPONENT
class SensingComponent {
#include "Extra/SensingComponentAPI.hpp"

public:
    MCAPI bool canSee(class Mob&, class Actor const&);
    MCAPI void reset();
    MCAPI bool withinFOV(class Mob&, class Vec3 const&, float);
};