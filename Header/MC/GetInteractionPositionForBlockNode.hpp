// This Header is auto generated by BDSLiteLoader Toolchain
#pragma once
#include <Global.h>
#define EXTRA_INCLUDE_PART_GETINTERACTIONPOSITIONFORBLOCKNODE
#include "Extra/GetInteractionPositionForBlockNodeAPI.hpp"
#undef EXTRA_INCLUDE_PART_GETINTERACTIONPOSITIONFORBLOCKNODE
class GetInteractionPositionForBlockNode {
#include "Extra/GetInteractionPositionForBlockNodeAPI.hpp"
public:
    /*0*/ virtual ~GetInteractionPositionForBlockNode();
    /*1*/ virtual int /*enum BehaviorStatus*/ tick(class Actor&);
    /*2*/ virtual void initializeFromDefinition(class Actor&);

private:
    MCAPI enum Facing::Name parseFacingNameFromString(std::string);
};