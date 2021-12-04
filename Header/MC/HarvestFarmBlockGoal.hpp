// This Header is auto generated by BDSLiteLoader Toolchain
#pragma once
#include <Global.h>
#include "BaseMoveToBlockGoal.hpp"
#define EXTRA_INCLUDE_PART_HARVESTFARMBLOCKGOAL
#include "Extra/HarvestFarmBlockGoalAPI.hpp"
#undef EXTRA_INCLUDE_PART_HARVESTFARMBLOCKGOAL
class HarvestFarmBlockGoal : public BaseMoveToBlockGoal {
#include "Extra/HarvestFarmBlockGoalAPI.hpp"
public:
    /*0*/ virtual ~HarvestFarmBlockGoal();
    /*1*/ virtual bool canUse();
    /*2*/ virtual bool canContinueToUse();
    /*3*/ virtual void unk_vfn_3();
    /*4*/ virtual void start();
    /*5*/ virtual void stop();
    /*6*/ virtual void tick();
    /*7*/ virtual void appendDebugInfo(std::string&) const;
    /*8*/ virtual void unk_vfn_8();
    /*9*/ virtual void unk_vfn_9();
    /*11*/ virtual bool isValidTarget(class BlockSource&, class BlockPos const&);
    /*16*/ virtual unsigned __int64 _getRepathTime() const;

protected:
    MCAPI bool trySowCrop(class BlockSource&, class BlockPos const&);
};