// This Header is auto generated by BDSLiteLoader Toolchain
#pragma once
#include <Global.h>
#include "JsonUtil.hpp"
#define EXTRA_INCLUDE_PART_BLOCKBREAKSENSORDEFINITION
#include "Extra/BlockBreakSensorDefinitionAPI.hpp"
#undef EXTRA_INCLUDE_PART_BLOCKBREAKSENSORDEFINITION
class BlockBreakSensorDefinition {
#include "Extra/BlockBreakSensorDefinitionAPI.hpp"

public:
    MCAPI void initialize(class EntityContext&, class BlockBreakSensorComponent&);

    MCAPI static void buildSchema(class std::shared_ptr<class JsonUtil::JsonSchemaObjectNode<class JsonUtil::EmptyClass, class BlockBreakSensorDefinition>>&);
};