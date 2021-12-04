// This Header is auto generated by BDSLiteLoader Toolchain
#pragma once
#include <Global.h>
#define EXTRA_INCLUDE_PART_KEYFRAMELERPMODE
#include "Extra/KeyFrameLerpModeAPI.hpp"
#undef EXTRA_INCLUDE_PART_KEYFRAMELERPMODE
class KeyFrameLerpMode {
#include "Extra/KeyFrameLerpModeAPI.hpp"

public:
    MCAPI struct glm::mat<4, 4, float, 0> const& getPrecomputedCubicCoeffs() const;
    MCAPI class KeyFrameLerpMode& operator=(class KeyFrameLerpMode const&);
    MCAPI void setLerpStyle(enum KeyFrameLerpStyle);
};