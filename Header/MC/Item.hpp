// This Header is auto generated by BDSLiteLoader Toolchain
#pragma once
#define AUTO_GENERATED
#include "../Global.h"
#include "Json.hpp"

#define BEFORE_EXTRA
// Include Headers or Declare Types Here

#undef BEFORE_EXTRA

class Item {

#define AFTER_EXTRA
// Add Member There
public:
class Tier {
public:
    Tier() = delete;
    Tier(Tier const&) = delete;
    Tier(Tier const&&) = delete;
};

#undef AFTER_EXTRA

#ifndef DISABLE_CONSTRUCTOR_PREVENTION_ITEM
public:
    class Item& operator=(class Item const&) = delete;
    Item(class Item const&) = delete;
    Item() = delete;
#endif

public:
    /*0*/ virtual ~Item();
    /*1*/ virtual bool initServer(class Json::Value&, class SemVersion const&);
    /*2*/ virtual void tearDown();
    /*3*/ virtual int getMaxUseDuration(class ItemStack const*) const;
    /*4*/ virtual void __unk_vfn_4();
    /*5*/ virtual void __unk_vfn_5();
    /*6*/ virtual void executeEvent(class ItemStackBase&, std::string const&, class RenderParams&) const;
    /*7*/ virtual void __unk_vfn_7();
    /*8*/ virtual void __unk_vfn_8();
    /*9*/ virtual void __unk_vfn_9();
    /*10*/ virtual void __unk_vfn_10();
    /*11*/ virtual bool isCamera() const;
    /*12*/ virtual void __unk_vfn_12();
    /*13*/ virtual bool isDamageable() const;
    /*14*/ virtual void __unk_vfn_14();
    /*15*/ virtual void __unk_vfn_15();
    /*16*/ virtual enum ItemColor getItemColor() const;
    /*17*/ virtual void __unk_vfn_17();
    /*18*/ virtual void __unk_vfn_18();
    /*19*/ virtual void __unk_vfn_19();
    /*20*/ virtual void __unk_vfn_20();
    /*21*/ virtual class ItemComponent* getComponent(class HashedString const&) const;
    /*22*/ virtual class ICameraItemComponent* getCamera() const;
    /*23*/ virtual class IFoodItemComponent* getFood() const;
    /*24*/ virtual class FuelItemComponent* getFuel() const;
    /*25*/ virtual class Item& setMaxStackSize(unsigned char);
    /*26*/ virtual class Item& setStackedByData(bool);
    /*27*/ virtual class Item& setMaxDamage(int);
    /*28*/ virtual class Item& setHandEquipped();
    /*29*/ virtual class Item& setUseAnimation(enum UseAnimation);
    /*30*/ virtual class Item& setMaxUseDuration(int);
    /*31*/ virtual class Item& setRequiresWorldBuilder(bool);
    /*32*/ virtual class Item& setExplodable(bool);
    /*33*/ virtual class Item& setFireResistant(bool);
    /*34*/ virtual class Item& setIsGlint(bool);
    /*35*/ virtual class Item& setShouldDespawn(bool);
    /*36*/ virtual std::unique_ptr<class CompoundTag> buildNetworkTag() const;
    /*37*/ virtual void initializeFromNetwork(class CompoundTag const&);
    /*38*/ virtual enum BlockShape getBlockShape() const;
    /*39*/ virtual bool canBeDepleted() const;
    /*40*/ virtual void __unk_vfn_40();
    /*41*/ virtual int getLevelDataForAuxValue(int) const;
    /*42*/ virtual bool isStackedByData() const;
    /*43*/ virtual short getMaxDamage() const;
    /*44*/ virtual int getAttackDamage() const;
    /*45*/ virtual bool isHandEquipped() const;
    /*46*/ virtual bool isGlint(class ItemStackBase const&) const;
    /*47*/ virtual void __unk_vfn_47();
    /*48*/ virtual int getPatternIndex() const;
    /*49*/ virtual void __unk_vfn_49();
    /*50*/ virtual void __unk_vfn_50();
    /*51*/ virtual void __unk_vfn_51();
    /*52*/ virtual void __unk_vfn_52();
    /*53*/ virtual void __unk_vfn_53();
    /*54*/ virtual void __unk_vfn_54();
    /*55*/ virtual void __unk_vfn_55();
    /*56*/ virtual void appendFormattedHovertext(class ItemStackBase const&, class Level&, std::string&, bool) const;
    /*57*/ virtual void __unk_vfn_57();
    /*58*/ virtual int getEnchantSlot() const;
    /*59*/ virtual int getEnchantValue() const;
    /*60*/ virtual int getArmorValue() const;
    /*61*/ virtual void __unk_vfn_61();
    /*62*/ virtual void __unk_vfn_62();
    /*63*/ virtual int getDamageChance(int) const;
    /*64*/ virtual float getViewDamping() const;
    /*65*/ virtual void __unk_vfn_65();
    /*66*/ virtual void __unk_vfn_66();
    /*67*/ virtual void __unk_vfn_67();
    /*68*/ virtual class mce::Color getColor(class CompoundTag const*, class ItemDescriptor const&) const;
    /*69*/ virtual void __unk_vfn_69();
    /*70*/ virtual void __unk_vfn_70();
    /*71*/ virtual void clearColor(class ItemStackBase&) const;
    /*72*/ virtual void clearColor(class CompoundTag*) const;
    /*73*/ virtual void setColor(class ItemStackBase&, class mce::Color const&) const;
    /*74*/ virtual void __unk_vfn_74();
    /*75*/ virtual void __unk_vfn_75();
    /*76*/ virtual struct ActorDefinitionIdentifier getActorIdentifier(class ItemStack const&) const;
    /*77*/ virtual void __unk_vfn_77();
    /*78*/ virtual void __unk_vfn_78();
    /*79*/ virtual int buildIdAux(short, class CompoundTag const*) const;
    /*80*/ virtual void __unk_vfn_80();
    /*81*/ virtual class ItemStack& use(class ItemStack&, class Player&) const;
    /*82*/ virtual bool dispense(class BlockSource&, class Container&, int, class Vec3 const&, unsigned char) const;
    /*83*/ virtual enum ItemUseMethod useTimeDepleted(class ItemStack&, class Level*, class Player*) const;
    /*84*/ virtual void releaseUsing(class ItemStack&, class Player*, int) const;
    /*85*/ virtual float getDestroySpeed(class ItemStackBase const&, class Block const&) const;
    /*86*/ virtual void hurtActor(class ItemStack&, class Actor&, class Mob&) const;
    /*87*/ virtual void hitActor(class ItemStack&, class Actor&, class Mob&) const;
    /*88*/ virtual void hitBlock(class ItemStack&, class Block const&, class BlockPos const&, class Mob&) const;
    /*89*/ virtual bool mineBlock(class ItemInstance&, class Block const&, int, int, int, class Actor*) const;
    /*90*/ virtual bool mineBlock(class ItemStack&, class Block const&, int, int, int, class Actor*) const;
    /*91*/ virtual void __unk_vfn_91();
    /*92*/ virtual std::string buildDescriptionId(class ItemDescriptor const&, class CompoundTag const*) const;
    /*93*/ virtual std::string buildEffectDescriptionName(class ItemStackBase const&) const;
    /*94*/ virtual std::string buildCategoryDescriptionName() const;
    /*95*/ virtual void readUserData(class ItemStackBase&, class IDataInput&, class ReadOnlyBinaryStream&) const;
    /*96*/ virtual void writeUserData(class ItemStackBase const&, class IDataOutput&) const;
    /*97*/ virtual unsigned char getMaxStackSize(class ItemDescriptor const&) const;
    /*98*/ virtual void __unk_vfn_98();
    /*99*/ virtual void refreshedInContainer(class ItemStackBase const&, class Level&) const;
    /*100*/ virtual class HashedString const& getCooldownType() const;
    /*101*/ virtual int getCooldownTime() const;
    /*102*/ virtual void fixupCommon(class ItemStackBase&) const;
    /*103*/ virtual void fixupCommon(class ItemStackBase&, class Level&) const;
    /*104*/ virtual short getDamageValue(class CompoundTag const*) const;
    /*105*/ virtual void setDamageValue(class ItemStackBase&, short) const;
    /*106*/ virtual enum InHandUpdateType getInHandUpdateType(class Player const&, class ItemInstance const&, class ItemInstance const&, bool, bool) const;
    /*107*/ virtual enum InHandUpdateType getInHandUpdateType(class Player const&, class ItemStack const&, class ItemStack const&, bool, bool) const;
    /*108*/ virtual void __unk_vfn_108();
    /*109*/ virtual bool isSameItem(class ItemStackBase const&, class ItemStackBase const&) const;
    /*110*/ virtual void initClient(class Json::Value&, class SemVersion const&);
    /*111*/ virtual std::string getInteractText(class Player const&) const;
    /*112*/ virtual int getAnimationFrameFor(class Mob*, bool, class ItemStack const*, bool) const;
    /*113*/ virtual bool isEmissive(int) const;
    /*114*/ virtual struct Brightness getLightEmission(int) const;
    /*115*/ virtual struct TextureUVCoordinateSet const& getIcon(class ItemStackBase const&, int, bool) const;
    /*116*/ virtual int getIconYOffset() const;
    /*117*/ virtual class Item& setIcon(std::string const&, int);
    /*118*/ virtual class Item& setIcon(struct TextureUVCoordinateSet const&);
    /*119*/ virtual class Item& setIconAtlas(std::string const&, int);
    /*120*/ virtual void __unk_vfn_120();
    /*121*/ virtual void playSoundIncrementally(class ItemStack const&, class Mob&) const;
    /*122*/ virtual void __unk_vfn_122();
    /*123*/ virtual float getFurnaceBurnIntervalMultipler(class ItemStackBase const&) const;
    /*124*/ virtual float getFurnaceXPmultiplier(class ItemStackBase const&) const;
    /*125*/ virtual std::string getAuxValuesDescription() const;
    /*126*/ virtual bool _checkUseOnPermissions(class Actor&, class ItemStackBase&, unsigned char const&, class BlockPos const&) const;
    /*127*/ virtual void __unk_vfn_127();
    /*128*/ virtual bool _useOn(class ItemStack&, class Actor&, class BlockPos, unsigned char, class Vec3 const&) const;
    /*
    inline bool isComponentBased() const{
        bool (Item::*rv)() const;
        *((void**)&rv) = dlsym("?isComponentBased@Item@@UEBA_NXZ");
        return (this->*rv)();
    }
    inline bool isBlockPlanterItem() const{
        bool (Item::*rv)() const;
        *((void**)&rv) = dlsym("?isBlockPlanterItem@Item@@UEBA_NXZ");
        return (this->*rv)();
    }
    inline bool isMultiColorTinted(class ItemStack const& a0) const{
        bool (Item::*rv)(class ItemStack const&) const;
        *((void**)&rv) = dlsym("?isMultiColorTinted@Item@@UEBA_NAEBVItemStack@@@Z");
        return (this->*rv)(std::forward<class ItemStack const&>(a0));
    }
    inline bool isBucket() const{
        bool (Item::*rv)() const;
        *((void**)&rv) = dlsym("?isBucket@Item@@UEBA_NXZ");
        return (this->*rv)();
    }
    inline bool isDyeable() const{
        bool (Item::*rv)() const;
        *((void**)&rv) = dlsym("?isDyeable@Item@@UEBA_NXZ");
        return (this->*rv)();
    }
    inline bool isActorPlacerItem() const{
        bool (Item::*rv)() const;
        *((void**)&rv) = dlsym("?isActorPlacerItem@Item@@UEBA_NXZ");
        return (this->*rv)();
    }
    inline bool requiresInteract() const{
        bool (Item::*rv)() const;
        *((void**)&rv) = dlsym("?requiresInteract@Item@@UEBA_NXZ");
        return (this->*rv)();
    }
    inline bool inventoryTick(class ItemStack& a0, class Level& a1, class Actor& a2, int a3, bool a4) const{
        bool (Item::*rv)(class ItemStack&, class Level&, class Actor&, int, bool) const;
        *((void**)&rv) = dlsym("?inventoryTick@Item@@UEBA_NAEAVItemStack@@AEAVLevel@@AEAVActor@@H_N@Z");
        return (this->*rv)(std::forward<class ItemStack&>(a0), std::forward<class Level&>(a1), std::forward<class Actor&>(a2), std::forward<int>(a3), std::forward<bool>(a4));
    }
    inline bool isFertilizer() const{
        bool (Item::*rv)() const;
        *((void**)&rv) = dlsym("?isFertilizer@Item@@UEBA_NXZ");
        return (this->*rv)();
    }
    inline bool isUseable() const{
        bool (Item::*rv)() const;
        *((void**)&rv) = dlsym("?isUseable@Item@@UEBA_NXZ");
        return (this->*rv)();
    }
    inline bool isDye() const{
        bool (Item::*rv)() const;
        *((void**)&rv) = dlsym("?isDye@Item@@UEBA_NXZ");
        return (this->*rv)();
    }
    inline bool shouldInteractionWithBlockBypassLiquid(class Block const& a0) const{
        bool (Item::*rv)(class Block const&) const;
        *((void**)&rv) = dlsym("?shouldInteractionWithBlockBypassLiquid@Item@@UEBA_NAEBVBlock@@@Z");
        return (this->*rv)(std::forward<class Block const&>(a0));
    }
    inline bool isThrowable() const{
        bool (Item::*rv)() const;
        *((void**)&rv) = dlsym("?isThrowable@Item@@UEBA_NXZ");
        return (this->*rv)();
    }
    inline bool canBeCharged() const{
        bool (Item::*rv)() const;
        *((void**)&rv) = dlsym("?canBeCharged@Item@@UEBA_NXZ");
        return (this->*rv)();
    }
    inline bool hasCustomColor(class ItemStackBase const& a0) const{
        bool (Item::*rv)(class ItemStackBase const&) const;
        *((void**)&rv) = dlsym("?hasCustomColor@Item@@UEBA_NAEBVItemStackBase@@@Z");
        return (this->*rv)(std::forward<class ItemStackBase const&>(a0));
    }
    inline bool uniqueAuxValues() const{
        bool (Item::*rv)() const;
        *((void**)&rv) = dlsym("?uniqueAuxValues@Item@@UEBA_NXZ");
        return (this->*rv)();
    }
    inline bool isArmor() const{
        bool (Item::*rv)() const;
        *((void**)&rv) = dlsym("?isArmor@Item@@UEBA_NXZ");
        return (this->*rv)();
    }
    inline bool validFishInteraction(int a0) const{
        bool (Item::*rv)(int) const;
        *((void**)&rv) = dlsym("?validFishInteraction@Item@@UEBA_NH@Z");
        return (this->*rv)(std::forward<int>(a0));
    }
    inline bool showsDurabilityInCreative() const{
        bool (Item::*rv)() const;
        *((void**)&rv) = dlsym("?showsDurabilityInCreative@Item@@UEBA_NXZ");
        return (this->*rv)();
    }
    inline bool isLiquidClipItem(int a0) const{
        bool (Item::*rv)(int) const;
        *((void**)&rv) = dlsym("?isLiquidClipItem@Item@@UEBA_NH@Z");
        return (this->*rv)(std::forward<int>(a0));
    }
    inline bool isComplex() const{
        bool (Item::*rv)() const;
        *((void**)&rv) = dlsym("?isComplex@Item@@UEBA_NXZ");
        return (this->*rv)();
    }
    inline bool hasCustomColor(class CompoundTag const* a0) const{
        bool (Item::*rv)(class CompoundTag const*) const;
        *((void**)&rv) = dlsym("?hasCustomColor@Item@@UEBA_NPEBVCompoundTag@@@Z");
        return (this->*rv)(std::forward<class CompoundTag const*>(a0));
    }
    inline bool canDestroySpecial(class Block const& a0) const{
        bool (Item::*rv)(class Block const&) const;
        *((void**)&rv) = dlsym("?canDestroySpecial@Item@@UEBA_NAEBVBlock@@@Z");
        return (this->*rv)(std::forward<class Block const&>(a0));
    }
    inline bool isDestructive(int a0) const{
        bool (Item::*rv)(int) const;
        *((void**)&rv) = dlsym("?isDestructive@Item@@UEBA_NH@Z");
        return (this->*rv)(std::forward<int>(a0));
    }
    inline bool isCandle() const{
        bool (Item::*rv)() const;
        *((void**)&rv) = dlsym("?isCandle@Item@@UEBA_NXZ");
        return (this->*rv)();
    }
    inline bool isMusicDisk() const{
        bool (Item::*rv)() const;
        *((void**)&rv) = dlsym("?isMusicDisk@Item@@UEBA_NXZ");
        return (this->*rv)();
    }
    inline bool isPattern() const{
        bool (Item::*rv)() const;
        *((void**)&rv) = dlsym("?isPattern@Item@@UEBA_NXZ");
        return (this->*rv)();
    }
    inline bool isValidRepairItem(class ItemStackBase const& a0, class ItemStackBase const& a1, class BaseGameVersion const& a2) const{
        bool (Item::*rv)(class ItemStackBase const&, class ItemStackBase const&, class BaseGameVersion const&) const;
        *((void**)&rv) = dlsym("?isValidRepairItem@Item@@UEBA_NAEBVItemStackBase@@0AEBVBaseGameVersion@@@Z");
        return (this->*rv)(std::forward<class ItemStackBase const&>(a0), std::forward<class ItemStackBase const&>(a1), std::forward<class BaseGameVersion const&>(a2));
    }
    inline bool isWearableThroughLootTable(class CompoundTag const* a0) const{
        bool (Item::*rv)(class CompoundTag const*) const;
        *((void**)&rv) = dlsym("?isWearableThroughLootTable@Item@@UEBA_NPEBVCompoundTag@@@Z");
        return (this->*rv)(std::forward<class CompoundTag const*>(a0));
    }
    inline class FuelItemComponent const* getFuel() const{
        class FuelItemComponent const* (Item::*rv)() const;
        *((void**)&rv) = dlsym("?getFuel@Item@@UEBAPEBVFuelItemComponent@@XZ");
        return (this->*rv)();
    }
    inline void saveAdditionalData(class ItemStackBase const& a0, class CompoundTag& a1) const{
        void (Item::*rv)(class ItemStackBase const&, class CompoundTag&) const;
        *((void**)&rv) = dlsym("?saveAdditionalData@Item@@UEBAXAEBVItemStackBase@@AEAVCompoundTag@@@Z");
        return (this->*rv)(std::forward<class ItemStackBase const&>(a0), std::forward<class CompoundTag&>(a1));
    }
    inline void playSoundIncrementally(class ItemInstance const& a0, class Mob& a1) const{
        void (Item::*rv)(class ItemInstance const&, class Mob&) const;
        *((void**)&rv) = dlsym("?playSoundIncrementally@Item@@UEBAXAEBVItemInstance@@AEAVMob@@@Z");
        return (this->*rv)(std::forward<class ItemInstance const&>(a0), std::forward<class Mob&>(a1));
    }
    inline void readAdditionalData(class ItemStackBase& a0, class CompoundTag const& a1) const{
        void (Item::*rv)(class ItemStackBase&, class CompoundTag const&) const;
        *((void**)&rv) = dlsym("?readAdditionalData@Item@@UEBAXAEAVItemStackBase@@AEBVCompoundTag@@@Z");
        return (this->*rv)(std::forward<class ItemStackBase&>(a0), std::forward<class CompoundTag const&>(a1));
    }
    inline bool canUseOnSimTick() const{
        bool (Item::*rv)() const;
        *((void**)&rv) = dlsym("?canUseOnSimTick@Item@@UEBA_NXZ");
        return (this->*rv)();
    }
    inline bool canDestroyInCreative() const{
        bool (Item::*rv)() const;
        *((void**)&rv) = dlsym("?canDestroyInCreative@Item@@UEBA_NXZ");
        return (this->*rv)();
    }
    inline bool _calculatePlacePos(class ItemStackBase& a0, class Actor& a1, unsigned char& a2, class BlockPos& a3) const{
        bool (Item::*rv)(class ItemStackBase&, class Actor&, unsigned char&, class BlockPos&) const;
        *((void**)&rv) = dlsym("?_calculatePlacePos@Item@@EEBA_NAEAVItemStackBase@@AEAVActor@@AEAEAEAVBlockPos@@@Z");
        return (this->*rv)(std::forward<class ItemStackBase&>(a0), std::forward<class Actor&>(a1), std::forward<unsigned char&>(a2), std::forward<class BlockPos&>(a3));
    }
    inline bool isValidAuxValue(int a0) const{
        bool (Item::*rv)(int) const;
        *((void**)&rv) = dlsym("?isValidAuxValue@Item@@UEBA_NH@Z");
        return (this->*rv)(std::forward<int>(a0));
    }
    inline  ~Item(){
         (Item::*rv)();
        *((void**)&rv) = dlsym("??1Item@@UEAA@XZ");
        return (this->*rv)();
    }
    inline std::string buildDescriptionName(class ItemStackBase const& a0) const{
        std::string (Item::*rv)(class ItemStackBase const&) const;
        *((void**)&rv) = dlsym("?buildDescriptionName@Item@@UEBA?AV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@AEBVItemStackBase@@@Z");
        return (this->*rv)(std::forward<class ItemStackBase const&>(a0));
    }
    inline class mce::Color getBaseColor(class ItemStack const& a0) const{
        class mce::Color (Item::*rv)(class ItemStack const&) const;
        *((void**)&rv) = dlsym("?getBaseColor@Item@@UEBA?AVColor@mce@@AEBVItemStack@@@Z");
        return (this->*rv)(std::forward<class ItemStack const&>(a0));
    }
    inline class mce::Color getSecondaryColor(class ItemStack const& a0) const{
        class mce::Color (Item::*rv)(class ItemStack const&) const;
        *((void**)&rv) = dlsym("?getSecondaryColor@Item@@UEBA?AVColor@mce@@AEBVItemStack@@@Z");
        return (this->*rv)(std::forward<class ItemStack const&>(a0));
    }
    inline int getMaxUseDuration(class ItemInstance const* a0) const{
        int (Item::*rv)(class ItemInstance const*) const;
        *((void**)&rv) = dlsym("?getMaxUseDuration@Item@@UEBAHPEBVItemInstance@@@Z");
        return (this->*rv)(std::forward<class ItemInstance const*>(a0));
    }
    inline bool isFood() const{
        bool (Item::*rv)() const;
        *((void**)&rv) = dlsym("?isFood@Item@@UEBA_NXZ");
        return (this->*rv)();
    }
    inline bool isGlint(class ItemStackBase const& a0) const{
        bool (Item::*rv)(class ItemStackBase const&) const;
        *((void**)&rv) = dlsym("?isGlint@Item@@UEBA_NAEBVItemStackBase@@@Z");
        return (this->*rv)(std::forward<class ItemStackBase const&>(a0));
    }
    */
    MCAPI Item(std::string const&, short);
    MCAPI void addOnResetBAIcallback(class std::function<void (void)> const&);
    MCAPI class Item& addTag(class HashedString const&);
    MCAPI bool allowOffhand() const;
    MCAPI class ItemDescriptor buildDescriptor(short, class CompoundTag const*) const;
    MCAPI bool calculatePlacePos(class ItemStackBase&, class Actor&, unsigned char&, class BlockPos&) const;
    MCAPI float destroySpeedBonus(class ItemStackBase const&) const;
    MCAPI void fixupOnLoad(class ItemStackBase&) const;
    MCAPI void fixupOnLoad(class ItemStackBase&, class Level&) const;
    MCAPI std::vector<struct CommandName> getCommandNames() const;
    MCAPI enum CreativeItemCategory getCreativeCategory() const;
    MCAPI std::string const& getCreativeGroup() const;
    MCAPI std::string const& getDescriptionId() const;
    MCAPI int getFrameCount() const;
    MCAPI std::string const& getFullItemName() const;
    MCAPI class HashedString const& getFullNameHash() const;
    MCAPI short getId() const;
    MCAPI class WeakPtr<class BlockLegacy> const& getLegacyBlock() const;
    MCAPI std::string const& getNamespace() const;
    MCAPI class HashedString const& getRawNameHash() const;
    MCAPI std::string const& getRawNameId() const;
    MCAPI class BaseGameVersion const& getRequiredBaseGameVersion() const;
    MCAPI std::string getSerializedName() const;
    MCAPI enum UseAnimation getUseAnimation() const;
    MCAPI bool hasTag(class HashedString const&) const;
    MCAPI bool hasTag(unsigned __int64 const&) const;
    MCAPI bool isElytra() const;
    MCAPI bool isExplodable() const;
    MCAPI bool isFireResistant() const;
    MCAPI bool isNameTag() const;
    MCAPI bool isSeed() const;
    MCAPI class Item& setAllowOffhand(bool);
    MCAPI class Item& setCategory(enum CreativeItemCategory);
    MCAPI class Item& setCreativeGroup(std::string const&);
    MCAPI class Item& setDescriptionId(std::string const&);
    MCAPI class Item& setFurnaceBurnIntervalMultiplier(float);
    MCAPI class Item& setFurnaceXPmultiplier(float);
    MCAPI class Item& setIsMirroredArt(bool);
    MCAPI class Item& setMinRequiredBaseGameVersion(class BaseGameVersion const&);
    MCAPI bool shouldDespawn() const;
    MCAPI bool updateCustomBlockEntityTag(class BlockSource&, class ItemStackBase&, class BlockPos const&) const;
    MCAPI bool useOn(class ItemStack&, class Actor&, int, int, int, unsigned char, class Vec3 const&) const;
    MCAPI static std::string const ICON_DESCRIPTION_PREFIX;
    MCAPI static std::string const TAG_DAMAGE;
    MCAPI static void addCreativeItem(class Block const&);
    MCAPI static void addCreativeItem(class ItemInstance const&);
    MCAPI static void addCreativeItem(class ItemStack const&);
    MCAPI static void addLooseCreativeItems(bool, class BaseGameVersion const&);
    MCAPI static void beginCreativeGroup(std::string const&, class ItemInstance const&);
    MCAPI static void beginCreativeGroup(std::string const&, short, short, class CompoundTag const*);
    MCAPI static void beginCreativeGroup(std::string const&, class Block const*, class CompoundTag const*);
    MCAPI static void endCreativeGroup();
    MCAPI static void endCreativeItemDefinitions(bool);
    MCAPI static struct TextureUVCoordinateSet const& getIconTextureUVSet(class TextureAtlasItem const&, int, int);
    MCAPI static class TextureAtlasItem const& getTextureItem(std::string const&);
    MCAPI static struct TextureUVCoordinateSet getTextureUVCoordinateSet(std::string const&, int);
    MCAPI static bool isElytra(class ItemDescriptor const&);
    MCAPI static bool isElytraBroken(int);
    MCAPI static bool isFlyEnabled(class ItemInstance const&);
    MCAPI static bool isSameTypeAndItem(class ItemStackBase const&, class ItemStackBase const&);
    MCAPI static class CreativeGroupInfo* mActiveCreativeGroupInfo;
    MCAPI static class CreativeItemGroupCategory* mActiveCreativeItemCategory;
    MCAPI static class CreativeItemRegistry* mActiveCreativeItemRegistry;
    MCAPI static bool const mGenerateDenyParticleEffect;
    MCAPI static struct TextureUVCoordinateSet mInvalidTextureUVCoordinateSet;
    MCAPI static class std::weak_ptr<class AtlasItemManager> mItemTextureItems;
    MCAPI static void setAtlasItemManager(class std::shared_ptr<class AtlasItemManager>);
    MCAPI static void startCreativeItemDefinitions(bool, class CreativeItemRegistry*);
    MCAPI static struct NewBlockID toBlockId(short);

protected:
    MCAPI void _helpChangeInventoryItemInPlace(class Actor&, class ItemStack&, class ItemStack&, enum ItemAcquisitionMethod) const;

private:
    MCAPI static void _addLooseCreativeItemsClient();
    MCAPI static std::unique_ptr<class std::set<short, struct std::less<short>, class std::allocator<short> >> mServerItemsUsedInCreativeItems;

};