// This Header is auto generated by BDSLiteLoader Toolchain
#pragma once
#include <Global.h>
#include "Json.hpp"
#define EXTRA_INCLUDE_PART_FLOATRANGE
#include "Extra/FloatRangeAPI.hpp"
#undef EXTRA_INCLUDE_PART_FLOATRANGE
struct FloatRange {
#include "Extra/FloatRangeAPI.hpp"

public:
    MCAPI float getValue(class Random&) const;
    MCAPI bool parseJson(class Json::Value const&, float, float);
};