// This Header is auto generated by BDSLiteLoader Toolchain
#pragma once
#include <Global.h>
#define EXTRA_INCLUDE_PART_BEHAVIORTREEDEFINITIONPTR
#include "Extra/BehaviorTreeDefinitionPtrAPI.hpp"
#undef EXTRA_INCLUDE_PART_BEHAVIORTREEDEFINITIONPTR
class BehaviorTreeDefinitionPtr {
#include "Extra/BehaviorTreeDefinitionPtrAPI.hpp"

public:
    MCAPI class BehaviorTreeDefinitionPtr& operator=(class BehaviorTreeDefinitionPtr&&);

    MCAPI static class BehaviorTreeDefinitionPtr const NONE;

protected:
    MCAPI void _deref();
};