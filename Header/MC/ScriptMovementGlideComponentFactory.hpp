// This Header is auto generated by BDSLiteLoader Toolchain
#pragma once
#include <Global.h>
#include "Scripting.hpp"
#define EXTRA_INCLUDE_PART_SCRIPTMOVEMENTGLIDECOMPONENTFACTORY
#include "Extra/ScriptMovementGlideComponentFactoryAPI.hpp"
#undef EXTRA_INCLUDE_PART_SCRIPTMOVEMENTGLIDECOMPONENTFACTORY
class ScriptMovementGlideComponentFactory {
#include "Extra/ScriptMovementGlideComponentFactoryAPI.hpp"
public:
    /*0*/ virtual ~ScriptMovementGlideComponentFactory();
    /*1*/ virtual class Scripting::StrongTypedObjectHandle<class ScriptActorComponent> createComponent(class WeakEntityRef, class Scripting::WeakLifetimeScope const&, std::string const&);
    /*2*/ virtual bool hasComponent(class WeakEntityRef) const;
};