// This Header is auto generated by BDSLiteLoader Toolchain
#pragma once
#define AUTO_GENERATED
#include "../Global.h"
#include "ContainerValidationBase.hpp"

#define BEFORE_EXTRA
// Include Headers or Declare Types Here

#undef BEFORE_EXTRA

class HorseEquipContainerValidation : public ContainerValidationBase {

#define AFTER_EXTRA
// Add Member There

#undef AFTER_EXTRA

#ifndef DISABLE_CONSTRUCTOR_PREVENTION_HORSEEQUIPCONTAINERVALIDATION
public:
    class HorseEquipContainerValidation& operator=(class HorseEquipContainerValidation const&) = delete;
    HorseEquipContainerValidation(class HorseEquipContainerValidation const&) = delete;
    HorseEquipContainerValidation() = delete;
#endif

public:
    /*0*/ virtual ~HorseEquipContainerValidation();
    /*2*/ virtual bool isItemAllowedInSlot(class ContainerScreenContext const&, int, class ItemStackBase const&, int) const;
    /*3*/ virtual void __unk_vfn_3();
    /*4*/ virtual bool isItemAllowedToAdd(class ItemStack const&) const;
    /*5*/ virtual void __unk_vfn_5();
    /*8*/ virtual void __unk_vfn_8();
    /*9*/ virtual int getContainerSize(class ContainerScreenContext const&, class Container const&) const;
    /*
    inline int getAvailableSetCount(int a0, class ItemStackBase const& a1) const{
        int (HorseEquipContainerValidation::*rv)(int, class ItemStackBase const&) const;
        *((void**)&rv) = dlsym("?getAvailableSetCount@HorseEquipContainerValidation@@UEBAHHAEBVItemStackBase@@@Z");
        return (this->*rv)(std::forward<int>(a0), std::forward<class ItemStackBase const&>(a1));
    }
    */
    MCAPI HorseEquipContainerValidation(class ContainerScreenContext const&);

protected:

private:

};