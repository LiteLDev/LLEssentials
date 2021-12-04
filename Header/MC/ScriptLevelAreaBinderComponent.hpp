// This Header is auto generated by BDSLiteLoader Toolchain
#pragma once
#include <Global.h>
#include "ScriptApi.hpp"
#define EXTRA_INCLUDE_PART_SCRIPTLEVELAREABINDERCOMPONENT
#include "Extra/ScriptLevelAreaBinderComponentAPI.hpp"
#undef EXTRA_INCLUDE_PART_SCRIPTLEVELAREABINDERCOMPONENT
class ScriptLevelAreaBinderComponent {
#include "Extra/ScriptLevelAreaBinderComponentAPI.hpp"
public:
    /*0*/ virtual ~ScriptLevelAreaBinderComponent();
    /*1*/ virtual bool serialize(class ScriptEngine&, class ScriptApi::ScriptObjectHandle const&) const;
    /*2*/ virtual bool deserialize(class ScriptEngine&, class ScriptApi::ScriptObjectHandle const&);

public:
    MCAPI class mce::UUID const& getIdentifier() const;

    MCAPI static std::string const TAG;
};