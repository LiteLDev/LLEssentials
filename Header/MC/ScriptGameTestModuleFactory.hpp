// This Header is auto generated by BDSLiteLoader Toolchain
#pragma once
#include <Global.h>
#define EXTRA_INCLUDE_PART_SCRIPTGAMETESTMODULEFACTORY
#include "Extra/ScriptGameTestModuleFactoryAPI.hpp"
#undef EXTRA_INCLUDE_PART_SCRIPTGAMETESTMODULEFACTORY
class ScriptGameTestModuleFactory {
#include "Extra/ScriptGameTestModuleFactoryAPI.hpp"
public:
    /*0*/ virtual ~ScriptGameTestModuleFactory();

public:
    MCAPI static std::string getModuleUUIDAsString();

private:
    MCAPI void _addV1();

    MCAPI static class mce::UUID ModuleUUID;
};