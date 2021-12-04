// This Header is auto generated by BDSLiteLoader Toolchain
#pragma once
#include <Global.h>
#include "ContainerModel.hpp"
#define EXTRA_INCLUDE_PART_HUDCONTAINERMODEL
#include "Extra/HudContainerModelAPI.hpp"
#undef EXTRA_INCLUDE_PART_HUDCONTAINERMODEL
class HudContainerModel : public ContainerModel {
#include "Extra/HudContainerModelAPI.hpp"
public:
    /*0*/ virtual void containerContentChanged(int);
    /*1*/ virtual ~HudContainerModel();
    /*2*/ virtual void postInit();
    /*6*/ virtual void unk_vfn_6();
    /*7*/ virtual class ContainerWeakRef getContainerWeakRef() const;
    /*9*/ virtual std::vector<class ItemStack> const& getItems() const;
    /*11*/ virtual class ItemStackBase const& getItemStackBase(int) const;
    /*12*/ virtual void unk_vfn_12();
    /*14*/ virtual bool isValid();
    /*15*/ virtual void unk_vfn_15();
    /*16*/ virtual void unk_vfn_16();
    /*17*/ virtual void unk_vfn_17();
    /*18*/ virtual std::string const& getItemGroupName(int) const;
    /*19*/ virtual void unk_vfn_19();
    /*20*/ virtual class Container* _getContainer() const;
    /*21*/ virtual int _getContainerOffset() const;

private:
    MCAPI void _refreshContainer();
};