// This Header is auto generated by BDSLiteLoader Toolchain
#pragma once
#include <Global.h>
#include "JsonUtil.hpp"
#define EXTRA_INCLUDE_PART_WASDCONTROLLEDDEFINITION
#include "Extra/WASDControlledDefinitionAPI.hpp"
#undef EXTRA_INCLUDE_PART_WASDCONTROLLEDDEFINITION
struct WASDControlledDefinition {
#include "Extra/WASDControlledDefinitionAPI.hpp"

public:
    MCAPI void initialize(class EntityContext&);
    MCAPI void uninitialize(class EntityContext&);

    MCAPI static void buildSchema(class std::shared_ptr<class JsonUtil::JsonSchemaObjectNode<class JsonUtil::EmptyClass, struct WASDControlledDefinition>>&);
};