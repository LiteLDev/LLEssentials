// This Header is auto generated by BDSLiteLoader Toolchain
#pragma once
#include <Global.h>
#define EXTRA_INCLUDE_PART_UIPROFANITYCONTEXT
#include "Extra/UIProfanityContextAPI.hpp"
#undef EXTRA_INCLUDE_PART_UIPROFANITYCONTEXT
class UIProfanityContext {
#include "Extra/UIProfanityContextAPI.hpp"

public:
    MCAPI std::string filterProfanityFromString(enum ProfanityFilterContext, std::string const&, bool) const;
};