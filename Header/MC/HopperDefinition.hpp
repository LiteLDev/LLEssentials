// This Header is auto generated by BDSLiteLoader Toolchain
#pragma once
#include <Global.h>
#include "JsonUtil.hpp"
#define EXTRA_INCLUDE_PART_HOPPERDEFINITION
#include "Extra/HopperDefinitionAPI.hpp"
#undef EXTRA_INCLUDE_PART_HOPPERDEFINITION
struct HopperDefinition {
#include "Extra/HopperDefinitionAPI.hpp"

public:
    MCAPI static void buildSchema(class std::shared_ptr<class JsonUtil::JsonSchemaObjectNode<class JsonUtil::EmptyClass, struct HopperDefinition>>&);
};