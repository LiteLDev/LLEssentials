// This Header is auto generated by BDSLiteLoader Toolchain
#pragma once
#define AUTO_GENERATED
#include "../Global.h"
#include "Json.hpp"
#include "BlockItem.hpp"

#define BEFORE_EXTRA
// Include Headers or Declare Types Here

#undef BEFORE_EXTRA

class BellBlockItem : public BlockItem {

#define AFTER_EXTRA
// Add Member There

#undef AFTER_EXTRA

#ifndef DISABLE_CONSTRUCTOR_PREVENTION_BELLBLOCKITEM
public:
    class BellBlockItem& operator=(class BellBlockItem const&) = delete;
    BellBlockItem(class BellBlockItem const&) = delete;
    BellBlockItem() = delete;
#endif

public:
    /*0*/ virtual ~BellBlockItem();
    /*2*/ virtual void tearDown();
    /*3*/ virtual int getMaxUseDuration(class ItemStack const*) const;
    /*4*/ virtual void __unk_vfn_4();
    /*5*/ virtual void __unk_vfn_5();
    /*6*/ virtual void executeEvent(class ItemStackBase&, std::string const&, class RenderParams&) const;
    /*7*/ virtual void __unk_vfn_7();
    /*8*/ virtual void __unk_vfn_8();
    /*9*/ virtual void __unk_vfn_9();
    /*10*/ virtual void __unk_vfn_10();
    /*12*/ virtual void __unk_vfn_12();
    /*14*/ virtual void __unk_vfn_14();
    /*15*/ virtual void __unk_vfn_15();
    /*16*/ virtual enum ItemColor getItemColor() const;
    /*17*/ virtual void __unk_vfn_17();
    /*18*/ virtual void __unk_vfn_18();
    /*19*/ virtual void __unk_vfn_19();
    /*20*/ virtual void __unk_vfn_20();
    /*21*/ virtual class ItemComponent* getComponent(class HashedString const&) const;
    /*24*/ virtual class FuelItemComponent* getFuel() const;
    /*38*/ virtual enum BlockShape getBlockShape() const;
    /*40*/ virtual void __unk_vfn_40();
    /*41*/ virtual int getLevelDataForAuxValue(int) const;
    /*43*/ virtual short getMaxDamage() const;
    /*44*/ virtual int getAttackDamage() const;
    /*46*/ virtual bool isGlint(class ItemStackBase const&) const;
    /*47*/ virtual void __unk_vfn_47();
    /*48*/ virtual int getPatternIndex() const;
    /*49*/ virtual void __unk_vfn_49();
    /*50*/ virtual void __unk_vfn_50();
    /*51*/ virtual void __unk_vfn_51();
    /*53*/ virtual void __unk_vfn_53();
    /*54*/ virtual void __unk_vfn_54();
    /*55*/ virtual void __unk_vfn_55();
    /*57*/ virtual void __unk_vfn_57();
    /*58*/ virtual int getEnchantSlot() const;
    /*59*/ virtual int getEnchantValue() const;
    /*60*/ virtual int getArmorValue() const;
    /*61*/ virtual void __unk_vfn_61();
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
    /*77*/ virtual void __unk_vfn_77();
    /*78*/ virtual void __unk_vfn_78();
    /*80*/ virtual void __unk_vfn_80();
    /*85*/ virtual float getDestroySpeed(class ItemStackBase const&, class Block const&) const;
    /*87*/ virtual void hitActor(class ItemStack&, class Actor&, class Mob&) const;
    /*88*/ virtual void hitBlock(class ItemStack&, class Block const&, class BlockPos const&, class Mob&) const;
    /*89*/ virtual bool mineBlock(class ItemInstance&, class Block const&, int, int, int, class Actor*) const;
    /*90*/ virtual bool mineBlock(class ItemStack&, class Block const&, int, int, int, class Actor*) const;
    /*91*/ virtual void __unk_vfn_91();
    /*97*/ virtual unsigned char getMaxStackSize(class ItemDescriptor const&) const;
    /*98*/ virtual void __unk_vfn_98();
    /*99*/ virtual void refreshedInContainer(class ItemStackBase const&, class Level&) const;
    /*103*/ virtual void fixupCommon(class ItemStackBase&, class Level&) const;
    /*106*/ virtual enum InHandUpdateType getInHandUpdateType(class Player const&, class ItemInstance const&, class ItemInstance const&, bool, bool) const;
    /*107*/ virtual enum InHandUpdateType getInHandUpdateType(class Player const&, class ItemStack const&, class ItemStack const&, bool, bool) const;
    /*108*/ virtual void __unk_vfn_108();
    /*111*/ virtual std::string getInteractText(class Player const&) const;
    /*112*/ virtual int getAnimationFrameFor(class Mob*, bool, class ItemStack const*, bool) const;
    /*120*/ virtual void __unk_vfn_120();
    /*121*/ virtual void playSoundIncrementally(class ItemStack const&, class Mob&) const;
    /*122*/ virtual void __unk_vfn_122();
    /*125*/ virtual std::string getAuxValuesDescription() const;
    /*128*/ virtual bool _useOn(class ItemStack&, class Actor&, class BlockPos, unsigned char, class Vec3 const&) const;
    MCAPI BellBlockItem(std::string const&, int);

protected:

private:

};