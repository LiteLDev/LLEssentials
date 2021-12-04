// This Header is auto generated by BDSLiteLoader Toolchain
#pragma once
#include <Global.h>
#include "entt.hpp"
#define EXTRA_INCLUDE_PART_BLOCKCOMPONENTFACTORY
#include "Extra/BlockComponentFactoryAPI.hpp"
#undef EXTRA_INCLUDE_PART_BLOCKCOMPONENTFACTORY
class BlockComponentFactory {
#include "Extra/BlockComponentFactoryAPI.hpp"

public:
    MCAPI std::unique_ptr<struct BlockComponentDescription> createDescription(std::string const&) const;
    MCAPI void initializeFactory(class Experiments const&);

    MCAPI static class entt::meta_any constructComponent(std::string const&);
    MCAPI static class entt::meta_any getComponent(std::string const&, void*);
    MCAPI static class std::unordered_map<std::string, struct BlockComponentFactory::Constructor, struct std::hash<std::string>, struct std::equal_to<std::string>, class std::allocator<struct std::pair<std::string const, struct BlockComponentFactory::Constructor>>> mRegisteredCerealComponents;
    MCAPI static void registerAllCerealDescriptions();
};