// This Header is auto generated by BDSLiteLoader Toolchain
#pragma once
#include <Global.h>
#include "Scripting.hpp"
#include "NavigationScriptActorComponent.hpp"
#define EXTRA_INCLUDE_PART_SCRIPTNAVIGATIONFLOATCOMPONENT
#include "Extra/ScriptNavigationFloatComponentAPI.hpp"
#undef EXTRA_INCLUDE_PART_SCRIPTNAVIGATIONFLOATCOMPONENT
class ScriptNavigationFloatComponent : public NavigationScriptActorComponent {
#include "Extra/ScriptNavigationFloatComponentAPI.hpp"
public:
    /*0*/ virtual ~ScriptNavigationFloatComponent();

public:
    MCAPI static class Scripting::ClassBindingBuilder<class ScriptNavigationFloatComponent> bind(struct Scripting::Version);
};