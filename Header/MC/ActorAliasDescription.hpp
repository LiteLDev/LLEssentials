// This Header is auto generated by BDSLiteLoader Toolchain
#pragma once
#include <Global.h>
#include "Json.hpp"
#define EXTRA_INCLUDE_PART_ACTORALIASDESCRIPTION
#include "Extra/ActorAliasDescriptionAPI.hpp"
#undef EXTRA_INCLUDE_PART_ACTORALIASDESCRIPTION
class ActorAliasDescription {
#include "Extra/ActorAliasDescriptionAPI.hpp"
public:
    /*0*/ virtual ~ActorAliasDescription();
    /*1*/ virtual char const* getJsonName() const;

public:
    MCAPI void parse(class Json::Value&, bool);
};