// This Header is auto generated by BDSLiteLoader Toolchain
#pragma once
#include <Global.h>
#define EXTRA_INCLUDE_PART_OREVEINIFIERNOISES
#include "Extra/OreVeinifierNoisesAPI.hpp"
#undef EXTRA_INCLUDE_PART_OREVEINIFIERNOISES
class OreVeinifierNoises {
#include "Extra/OreVeinifierNoisesAPI.hpp"

public:
    MCAPI static std::unique_ptr<class OreVeinifierNoises> make(class XoroshiroPositionalRandomFactory const&);
};