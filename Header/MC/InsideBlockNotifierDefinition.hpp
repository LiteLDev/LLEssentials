// This Header is auto generated by BDSLiteLoader Toolchain
#pragma once
#include <Global.h>
#include "JsonUtil.hpp"
#define EXTRA_INCLUDE_PART_INSIDEBLOCKNOTIFIERDEFINITION
#include "Extra/InsideBlockNotifierDefinitionAPI.hpp"
#undef EXTRA_INCLUDE_PART_INSIDEBLOCKNOTIFIERDEFINITION
class InsideBlockNotifierDefinition {
#include "Extra/InsideBlockNotifierDefinitionAPI.hpp"

public:
    MCAPI void initialize(class EntityContext&, class InsideBlockNotifierComponent&) const;

    MCAPI static void buildSchema(class std::shared_ptr<class JsonUtil::JsonSchemaObjectNode<class JsonUtil::EmptyClass, class InsideBlockNotifierDefinition>>&);
};