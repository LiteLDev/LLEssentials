// This Header is auto generated by BDSLiteLoader Toolchain
#pragma once
#include <Global.h>
#include "Scripting.hpp"
#include "ScriptActorComponent.hpp"
#define EXTRA_INCLUDE_PART_NAVIGATIONSCRIPTACTORCOMPONENT
#include "Extra/NavigationScriptActorComponentAPI.hpp"
#undef EXTRA_INCLUDE_PART_NAVIGATIONSCRIPTACTORCOMPONENT
class NavigationScriptActorComponent : public ScriptActorComponent {
#include "Extra/NavigationScriptActorComponentAPI.hpp"
public:
    /*0*/ virtual ~NavigationScriptActorComponent();
    /*4*/ virtual class Scripting::Result<bool> getIsAmphibious() const;
    /*5*/ virtual class Scripting::Result<bool> getAvoidSun() const;
    /*6*/ virtual class Scripting::Result<bool> getCanPassDoors() const;
    /*7*/ virtual class Scripting::Result<bool> getCanOpenDoors() const;
    /*8*/ virtual class Scripting::Result<bool> getCanOpenIronDoors() const;
    /*9*/ virtual class Scripting::Result<bool> getCanBreakDoors() const;
    /*10*/ virtual class Scripting::Result<bool> getAvoidWater() const;
    /*11*/ virtual class Scripting::Result<bool> getAvoidDamageBlocks() const;
    /*12*/ virtual class Scripting::Result<bool> getCanFloat() const;
    /*13*/ virtual class Scripting::Result<bool> getCanSink() const;
    /*14*/ virtual class Scripting::Result<bool> getCanPathOverWater() const;
    /*15*/ virtual class Scripting::Result<bool> getCanPathOverLava() const;
    /*16*/ virtual class Scripting::Result<bool> getCanWalkInLava() const;
    /*17*/ virtual class Scripting::Result<bool> getAvoidPortals() const;
    /*18*/ virtual class Scripting::Result<bool> getCanWalk() const;
    /*19*/ virtual class Scripting::Result<bool> getCanSwim() const;
    /*20*/ virtual class Scripting::Result<bool> getCanBreach() const;
    /*21*/ virtual class Scripting::Result<bool> getCanJump() const;
    /*22*/ virtual class Scripting::Result<bool> getCanPathFromAir() const;
};