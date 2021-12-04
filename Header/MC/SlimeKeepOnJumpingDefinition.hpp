// This Header is auto generated by BDSLiteLoader Toolchain
#pragma once
#include <Global.h>
#include "JsonUtil.hpp"
#define EXTRA_INCLUDE_PART_SLIMEKEEPONJUMPINGDEFINITION
#include "Extra/SlimeKeepOnJumpingDefinitionAPI.hpp"
#undef EXTRA_INCLUDE_PART_SLIMEKEEPONJUMPINGDEFINITION
class SlimeKeepOnJumpingDefinition {
#include "Extra/SlimeKeepOnJumpingDefinitionAPI.hpp"
public:
    /*0*/ virtual ~SlimeKeepOnJumpingDefinition();

public:
    MCAPI void initialize(class EntityContext&, class SlimeKeepOnJumpingGoal&);

    MCAPI static void buildSchema(std::string const&, class std::shared_ptr<class JsonUtil::JsonSchemaObjectNode<class JsonUtil::EmptyClass, class SlimeKeepOnJumpingDefinition>>&);
};