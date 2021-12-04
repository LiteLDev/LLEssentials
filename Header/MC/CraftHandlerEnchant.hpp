// This Header is auto generated by BDSLiteLoader Toolchain
#pragma once
#include <Global.h>
#include "CraftHandlerBase.hpp"
#define EXTRA_INCLUDE_PART_CRAFTHANDLERENCHANT
#include "Extra/CraftHandlerEnchantAPI.hpp"
#undef EXTRA_INCLUDE_PART_CRAFTHANDLERENCHANT
class CraftHandlerEnchant : public CraftHandlerBase {
#include "Extra/CraftHandlerEnchantAPI.hpp"
public:
    /*0*/ virtual ~CraftHandlerEnchant();
    /*2*/ virtual int /*enum ItemStackNetResult*/ preHandleAction(int /*enum ItemStackRequestActionType*/);
    /*3*/ virtual void endRequestBatch();
    /*4*/ virtual int /*enum ItemStackNetResult*/ _handleCraftAction(class ItemStackRequestActionCraftBase const&);
    /*5*/ virtual void _postCraftRequest(bool);
    /*6*/ virtual class Recipes const* _getLevelRecipes() const;

private:
    MCAPI class EnchantingContainerManagerModel& _getEnchantingModel() const;
    MCAPI enum ItemStackNetResult _handleEnchant(class ItemStackRequestActionCraft<class TypedServerNetId<struct RecipeNetIdTag, unsigned int, 0>, 10> const&);
};