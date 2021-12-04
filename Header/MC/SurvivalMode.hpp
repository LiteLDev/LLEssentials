// This Header is auto generated by BDSLiteLoader Toolchain
#pragma once
#include <Global.h>
#include "GameMode.hpp"
#define EXTRA_INCLUDE_PART_SURVIVALMODE
#include "Extra/SurvivalModeAPI.hpp"
#undef EXTRA_INCLUDE_PART_SURVIVALMODE
class SurvivalMode : public GameMode {
#include "Extra/SurvivalModeAPI.hpp"
public:
    /*0*/ virtual ~SurvivalMode();
    /*1*/ virtual bool startDestroyBlock(class BlockPos const&, unsigned char, bool&);
    /*2*/ virtual bool destroyBlock(class BlockPos const&, unsigned char);
    /*5*/ virtual void startBuildBlock(class BlockPos const&, unsigned char);
    /*6*/ virtual bool buildBlock(class BlockPos const&, unsigned char, bool);
    /*9*/ virtual void tick();
    /*11*/ virtual bool useItem(class ItemStack&);
    /*12*/ virtual bool useItemOn(class ItemStack&, class BlockPos const&, unsigned char, class Vec3 const&, class Block const*);
    /*13*/ virtual bool interact(class Actor&, class Vec3 const&);
    /*14*/ virtual bool attack(class Actor&);
    /*16*/ virtual void setTrialMode(bool);
    /*17*/ virtual bool isInTrialMode();
    /*18*/ virtual void registerUpsellScreenCallback(class std::function<void(bool)>);

private:
    MCAPI void _messagePlayers(std::string);
    MCAPI void _showTrialReminder(bool);

    MCAPI static bool mTrialHasEnded;
};