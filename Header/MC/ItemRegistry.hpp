// This Header is auto generated by BDSLiteLoader Toolchain
#pragma once
#define AUTO_GENERATED
#include "../Global.h"
#include "Json.hpp"

#define BEFORE_EXTRA
// Include Headers or Declare Types Here

#undef BEFORE_EXTRA

class ItemRegistry {

#define AFTER_EXTRA
// Add Member There
public:
struct ItemHashAlias {
    ItemHashAlias() = delete;
    ItemHashAlias(ItemHashAlias const&) = delete;
    ItemHashAlias(ItemHashAlias const&&) = delete;
};
struct ItemAlias {
    ItemAlias() = delete;
    ItemAlias(ItemAlias const&) = delete;
    ItemAlias(ItemAlias const&&) = delete;
};

#undef AFTER_EXTRA

#ifndef DISABLE_CONSTRUCTOR_PREVENTION_ITEMREGISTRY
public:
    class ItemRegistry& operator=(class ItemRegistry const&) = delete;
    ItemRegistry(class ItemRegistry const&) = delete;
    ItemRegistry() = delete;
#endif

public:
    MCAPI static class gsl::basic_string_span<char const, -1> const MINECRAFT_NAMESPACE;
    MCAPI static std::string _parseItemDefinition(std::string const&, bool, class std::function<void (class WeakPtr<class Item>& , class Json::Value& , class SemVersion const& )>, bool, enum ItemVersion, enum PackType);
    MCAPI static void alterAvailableCreativeItems(class ActorInfoRegistry*, class LevelData&);
    MCAPI static void clearItemAndCreativeItemRegistry();
    MCAPI static void digestServerItemComponents(std::vector<struct std::pair<std::string, class CompoundTag>> const&);
    MCAPI static void finishedRegistration();
    MCAPI static class WeakPtr<class Item> getItem(class Block const&);
    MCAPI static class WeakPtr<class Item> getItem(class BlockLegacy const&);
    MCAPI static class WeakPtr<class Item> getItem(short);
    MCAPI static int getItemCount();
    MCAPI static class ItemEventResponseFactory* getItemResponseFactory();
    MCAPI static struct std::pair<class HashedString, int> getNameFromAlias(class HashedString const&, int);
    MCAPI static class HashedString getNameFromLegacyID(short);
    MCAPI static class std::unordered_map<class HashedString, class WeakPtr<class Item>, struct std::hash<class HashedString>, struct std::equal_to<class HashedString>, class std::allocator<struct std::pair<class HashedString const, class WeakPtr<class Item> > > > const& getNameToItemMap();
    MCAPI static void initCreativeItemsServer(class ActorInfoRegistry*, class BlockDefinitionGroup*, bool, class Experiments const&, class std::function<void (class ActorInfoRegistry* , class BlockDefinitionGroup* , class CreativeItemRegistry* , bool, class BaseGameVersion const& , class Experiments const& )>);
    MCAPI static void initServerData(class ResourcePackManager&, class Experiments const&, enum ItemVersion);
    MCAPI static bool isCreativeItem(class ItemInstance const&);
    MCAPI static class WeakPtr<class Item> lookupByName(int&, int&, std::string const&);
    MCAPI static class WeakPtr<class Item> lookupByName(int&, std::string const&);
    MCAPI static class WeakPtr<class Item> lookupByName(class HashedString const&);
    MCAPI static class WeakPtr<class Item> lookupByNameNoAlias(std::string const&);
    MCAPI static class WeakPtr<class Item> lookupByNameNoAlias(class HashedString const&);
    MCAPI static class WeakPtr<class Item> lookupByNameNoParsing(int&, class HashedString const&);
    MCAPI static class WeakPtr<class Item> lookupByNameNoParsing(class HashedString const&);
    MCAPI static bool mCheckForItemWorldCompatibility;
    MCAPI static class std::mutex mCompatibilityCheckLock;
    MCAPI static std::vector<class SharedPtr<class Item>> mDeadItemRegistry;
    MCAPI static std::unique_ptr<class ItemEventResponseFactory> mResponseFactory;
    MCAPI static bool mServerInitializingCreativeItems;
    MCAPI static class BaseGameVersion mWorldBaseGameVersion;
    MCAPI static void registerAlias(class HashedString const&, class HashedString const&, class BaseGameVersion const&);
    MCAPI static class Item& registerComplexAlias(class HashedString const&, class std::function<std::string (short)>);
    MCAPI static void registerItem(class SharedPtr<class Item>);
    MCAPI static void registerLegacyID(std::string const&, short);
    MCAPI static void registerLegacyMapping(std::string const&, std::string const&, class BaseGameVersion const&);
    MCAPI static unsigned __int64 remapToFullLegacyNameByHash(unsigned __int64);
    MCAPI static unsigned __int64 remapToLegacyNameByHash(unsigned __int64);
    MCAPI static void setOwningThreadId(class std::thread::id);
    MCAPI static void setWorldBaseGameVersion(class BaseGameVersion const&);
    MCAPI static void shutdown();
    MCAPI static void startRegistration();
    MCAPI static void unregisterItem(class HashedString const&);

protected:

private:
    MCAPI static void _loadItemDefinition(class Json::Value&, bool, class std::function<void (class WeakPtr<class Item>& , class Json::Value& , class SemVersion const& )>, bool, enum ItemVersion, enum PackType);
    MCAPI static std::vector<class HashedString> mAttachableDefinitions;
    MCAPI static class std::unordered_map<int, class WeakPtr<class Item>, struct std::hash<int>, struct std::equal_to<int>, class std::allocator<struct std::pair<int const, class WeakPtr<class Item> > > > mIdToItemMap;
    MCAPI static class std::unordered_map<class HashedString, struct ItemRegistry::ItemAlias, struct std::hash<class HashedString>, struct std::equal_to<class HashedString>, class std::allocator<struct std::pair<class HashedString const, struct ItemRegistry::ItemAlias> > > mItemAliasLookupMap;
    MCAPI static std::vector<class SharedPtr<class Item>> mItemRegistry;
    MCAPI static class std::unordered_map<short, class HashedString, struct std::hash<short>, struct std::equal_to<short>, class std::allocator<struct std::pair<short const, class HashedString> > > mLegacyIDToNameMap;
    MCAPI static short mMaxItemID;
    MCAPI static class std::unordered_map<class HashedString, class WeakPtr<class Item>, struct std::hash<class HashedString>, struct std::equal_to<class HashedString>, class std::allocator<struct std::pair<class HashedString const, class WeakPtr<class Item> > > > mNameToItemMap;
    MCAPI static class std::thread::id mOwnerThread;
    MCAPI static class std::unordered_map<unsigned __int64, struct ItemRegistry::ItemHashAlias, struct std::hash<unsigned __int64>, struct std::equal_to<unsigned __int64>, class std::allocator<struct std::pair<unsigned __int64 const, struct ItemRegistry::ItemHashAlias> > > mReverseAliasLookupMap;
    MCAPI static class std::unordered_map<unsigned __int64, struct ItemRegistry::ItemHashAlias, struct std::hash<unsigned __int64>, struct std::equal_to<unsigned __int64>, class std::allocator<struct std::pair<unsigned __int64 const, struct ItemRegistry::ItemHashAlias> > > mReverseFullNameAliasLookupMap;
    MCAPI static class std::unordered_map<class HashedString, class WeakPtr<class Item>, struct std::hash<class HashedString>, struct std::equal_to<class HashedString>, class std::allocator<struct std::pair<class HashedString const, class WeakPtr<class Item> > > > mTileItemNameToItemMap;
    MCAPI static class std::unordered_map<class HashedString, class WeakPtr<class Item>, struct std::hash<class HashedString>, struct std::equal_to<class HashedString>, class std::allocator<struct std::pair<class HashedString const, class WeakPtr<class Item> > > > mTileNamespaceToItemMap;

};