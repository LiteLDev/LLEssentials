// This Header is auto generated by BDSLiteLoader Toolchain
#pragma once
#include <Global.h>
#define EXTRA_INCLUDE_PART_ONACTORLEAVEVOLUMEDEFINITION
#include "Extra/OnActorLeaveVolumeDefinitionAPI.hpp"
#undef EXTRA_INCLUDE_PART_ONACTORLEAVEVOLUMEDEFINITION
struct OnActorLeaveVolumeDefinition {
#include "Extra/OnActorLeaveVolumeDefinitionAPI.hpp"

public:
    MCAPI void initialize(class EntityContext&, class OnActorLeaveVolumeComponent&) const;

    MCAPI static std::string const NAME;
    MCAPI static void bindType();
};