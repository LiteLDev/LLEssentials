// This Header is auto generated by BDSLiteLoader Toolchain
#pragma once
#include <Global.h>
#define EXTRA_INCLUDE_PART_WAITTICKSNODE
#include "Extra/WaitTicksNodeAPI.hpp"
#undef EXTRA_INCLUDE_PART_WAITTICKSNODE
class WaitTicksNode {
#include "Extra/WaitTicksNodeAPI.hpp"
public:
    /*0*/ virtual ~WaitTicksNode();
    /*1*/ virtual int /*enum BehaviorStatus*/ tick(class Actor&);
    /*2*/ virtual void initializeFromDefinition(class Actor&);
};