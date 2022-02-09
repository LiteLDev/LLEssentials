// This Header is auto generated by BDSLiteLoader Toolchain
#pragma once
#define AUTO_GENERATED
#include "../Global.h"
#include "ContainerManagerModel.hpp"

#define BEFORE_EXTRA
// Include Headers or Declare Types Here

#undef BEFORE_EXTRA

class MaterialReducerContainerManagerModel : public ContainerManagerModel {

#define AFTER_EXTRA
// Add Member There

#undef AFTER_EXTRA

#ifndef DISABLE_CONSTRUCTOR_PREVENTION_MATERIALREDUCERCONTAINERMANAGERMODEL
public:
    class MaterialReducerContainerManagerModel& operator=(class MaterialReducerContainerManagerModel const&) = delete;
    MaterialReducerContainerManagerModel(class MaterialReducerContainerManagerModel const&) = delete;
    MaterialReducerContainerManagerModel() = delete;
#endif

public:
    /*0*/ virtual ~MaterialReducerContainerManagerModel();
    /*1*/ virtual enum ContainerID getContainerId() const;
    /*2*/ virtual void setContainerId(enum ContainerID);
    /*3*/ virtual enum ContainerType getContainerType() const;
    /*4*/ virtual void setContainerType(enum ContainerType);
    /*6*/ virtual std::vector<class ItemStack> getItemCopies() const;
    /*7*/ virtual void setSlot(int, class ItemStack const&, bool);
    /*8*/ virtual class ItemStack const& getSlot(int) const;
    /*9*/ virtual void setData(int, int);
    /*10*/ virtual void broadcastChanges();
    /*15*/ virtual bool isValid(float);
    /*16*/ virtual class ContainerScreenContext _postInit();
    MCAPI MaterialReducerContainerManagerModel(enum ContainerID, class Player&, class BlockPos const&);

protected:

private:

};