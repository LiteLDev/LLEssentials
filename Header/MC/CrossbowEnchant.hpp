// This Header is auto generated by BDSLiteLoader Toolchain
#pragma once
#include <Global.h>
#define EXTRA_INCLUDE_PART_CROSSBOWENCHANT
#include "Extra/CrossbowEnchantAPI.hpp"
#undef EXTRA_INCLUDE_PART_CROSSBOWENCHANT
class CrossbowEnchant {
#include "Extra/CrossbowEnchantAPI.hpp"
public:
    /*0*/ virtual ~CrossbowEnchant();
    /*1*/ virtual bool isCompatibleWith(int /*enum Enchant::Type*/) const;
    /*2*/ virtual int getMinCost(int) const;
    /*3*/ virtual int getMaxCost(int) const;
    /*4*/ virtual void unk_vfn_4();
    /*5*/ virtual int getMaxLevel() const;
    /*6*/ virtual void unk_vfn_6();
    /*7*/ virtual void unk_vfn_7();
    /*8*/ virtual void unk_vfn_8();
    /*9*/ virtual void unk_vfn_9();
    /*10*/ virtual void unk_vfn_10();
    /*11*/ virtual void unk_vfn_11();
    /*12*/ virtual void unk_vfn_12();
    /*13*/ virtual void unk_vfn_13();
    /*14*/ virtual bool _isValidEnchantmentTypeForCategory(int /*enum Enchant::Type*/) const;

private:
    MCAPI static std::vector<enum Enchant::Type> const VALID_ENCHANTMENTS;
};