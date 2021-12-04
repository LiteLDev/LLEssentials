// This Header is auto generated by BDSLiteLoader Toolchain
#pragma once
#include <Global.h>
#include "JsonUtil.hpp"
#define EXTRA_INCLUDE_PART_NPCDEFINITION
#include "Extra/NpcDefinitionAPI.hpp"
#undef EXTRA_INCLUDE_PART_NPCDEFINITION
class NpcDefinition {
#include "Extra/NpcDefinitionAPI.hpp"

public:
    MCAPI void initialize(class EntityContext&, class NpcComponent&);

    MCAPI static void buildSchema(class std::shared_ptr<class JsonUtil::JsonSchemaObjectNode<class JsonUtil::EmptyClass, class NpcDefinition>>&);
};