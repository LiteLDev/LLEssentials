// This Header is auto generated by BDSLiteLoader Toolchain
#pragma once
#include <Global.h>
#include "Core.hpp"
#define EXTRA_INCLUDE_PART_DEBUGENDPOINT
#include "Extra/DebugEndPointAPI.hpp"
#undef EXTRA_INCLUDE_PART_DEBUGENDPOINT
class DebugEndPoint {
#include "Extra/DebugEndPointAPI.hpp"

public:
    MCAPI void initializeContentLogging(class ResourcePackManager&, class Core::Path const&);
};