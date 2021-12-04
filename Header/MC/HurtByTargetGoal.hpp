// This Header is auto generated by BDSLiteLoader Toolchain
#pragma once
#include <Global.h>
#include "TargetGoal.hpp"
#define EXTRA_INCLUDE_PART_HURTBYTARGETGOAL
#include "Extra/HurtByTargetGoalAPI.hpp"
#undef EXTRA_INCLUDE_PART_HURTBYTARGETGOAL
class HurtByTargetGoal : public TargetGoal {
#include "Extra/HurtByTargetGoalAPI.hpp"
public:
    /*0*/ virtual ~HurtByTargetGoal();
    /*1*/ virtual bool canUse();
    /*3*/ virtual bool isTargetGoal() const;
    /*4*/ virtual void start();
    /*5*/ virtual void stop();
    /*7*/ virtual void appendDebugInfo(std::string&) const;
    /*8*/ virtual bool isTargetGoal() const;
    /*9*/ virtual void stop();
    /*11*/ virtual void alertOther(class Mob*, class Mob*);
};