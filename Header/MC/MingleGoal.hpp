// This Header is auto generated by BDSLiteLoader Toolchain
#pragma once
#include <Global.h>
#include "MoveToPOIGoal.hpp"
#define EXTRA_INCLUDE_PART_MINGLEGOAL
#include "Extra/MingleGoalAPI.hpp"
#undef EXTRA_INCLUDE_PART_MINGLEGOAL
class MingleGoal : public MoveToPOIGoal {
#include "Extra/MingleGoalAPI.hpp"
public:
    /*0*/ virtual ~MingleGoal();
    /*1*/ virtual bool canUse();
    /*2*/ virtual bool canContinueToUse();
    /*3*/ virtual void unk_vfn_3();
    /*4*/ virtual void start();
    /*5*/ virtual void stop();
    /*6*/ virtual void tick();
    /*7*/ virtual void appendDebugInfo(std::string&) const;
    /*8*/ virtual void unk_vfn_8();
    /*9*/ virtual void unk_vfn_9();
    /*16*/ virtual unsigned __int64 _getRepathTime() const;

private:
    MCAPI void _findNewPartner(struct ActorUniqueID);
    MCAPI class MingleComponent& _getMingleComponent() const;
    MCAPI bool _isWithinInteractRange(class Actor&) const;

    MCAPI static int const FIND_PARTNER_INTERVAL_TICKS;
    MCAPI static int const SPEAK_INTERVAL_TICKS_MAX;
    MCAPI static int const SPEAK_INTERVAL_TICKS_MIN;
    MCAPI static class MingleComponent* _tryGetMingleComponent(class Actor&);
};