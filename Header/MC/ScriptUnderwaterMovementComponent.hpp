// This Header is auto generated by BDSLiteLoader Toolchain
#pragma once
#include <Global.h>
#include "AttributeScriptActorComponent.hpp"
#include "Scripting.hpp"
#define EXTRA_INCLUDE_PART_SCRIPTUNDERWATERMOVEMENTCOMPONENT
#include "Extra/ScriptUnderwaterMovementComponentAPI.hpp"
#undef EXTRA_INCLUDE_PART_SCRIPTUNDERWATERMOVEMENTCOMPONENT
class ScriptUnderwaterMovementComponent : public AttributeScriptActorComponent {
#include "Extra/ScriptUnderwaterMovementComponentAPI.hpp"
public:
    /*0*/ virtual ~ScriptUnderwaterMovementComponent();

public:
    MCAPI static class Scripting::ClassBindingBuilder<class ScriptUnderwaterMovementComponent> bind(struct Scripting::Version);
};