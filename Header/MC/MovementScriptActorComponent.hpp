// This Header is auto generated by BDSLiteLoader Toolchain
#pragma once
#include <Global.h>
#include "Scripting.hpp"
#include "ScriptActorComponent.hpp"
#define EXTRA_INCLUDE_PART_MOVEMENTSCRIPTACTORCOMPONENT
#include "Extra/MovementScriptActorComponentAPI.hpp"
#undef EXTRA_INCLUDE_PART_MOVEMENTSCRIPTACTORCOMPONENT
class MovementScriptActorComponent : public ScriptActorComponent {
#include "Extra/MovementScriptActorComponentAPI.hpp"
public:
    /*0*/ virtual ~MovementScriptActorComponent();
    /*4*/ virtual class Scripting::Result<float> getMaxTurn() const;
};