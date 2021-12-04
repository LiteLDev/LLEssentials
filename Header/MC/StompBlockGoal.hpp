// This Header is auto generated by BDSLiteLoader Toolchain
#pragma once
#include <Global.h>
#include "BaseMoveToGoal.hpp"
#define EXTRA_INCLUDE_PART_STOMPBLOCKGOAL
#include "Extra/StompBlockGoalAPI.hpp"
#undef EXTRA_INCLUDE_PART_STOMPBLOCKGOAL
class StompBlockGoal : public BaseMoveToGoal {
#include "Extra/StompBlockGoalAPI.hpp"
public:
    /*0*/ virtual ~StompBlockGoal();
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
    /*13*/ virtual bool _canReach(class BlockPos const&);
    /*14*/ virtual void _moveToBlock();
    /*16*/ virtual unsigned __int64 _getRepathTime() const;
    /*17*/ virtual bool findTargetBlock();
    /*18*/ virtual void _createBreakProgressParticles(class Level&, class BlockSource&, class BlockPos);
    /*19*/ virtual void _createDestroyParticles(class Level&, class BlockSource&, class BlockPos);
    /*20*/ virtual void _playBreakProgressSound(class Level&, class BlockSource&, class BlockPos);
    /*21*/ virtual void _playDestroySound(class Level&, class BlockSource&, class BlockPos);
};