// This Header is auto generated by BDSLiteLoader Toolchain
#pragma once
#include <Global.h>
#define EXTRA_INCLUDE_PART_BLOCKVOLUMETARGET
#include "Extra/BlockVolumeTargetAPI.hpp"
#undef EXTRA_INCLUDE_PART_BLOCKVOLUMETARGET
class BlockVolumeTarget {
#include "Extra/BlockVolumeTargetAPI.hpp"
public:
    /*0*/ virtual ~BlockVolumeTarget();
    /*1*/ virtual void unk_vfn_1();
    /*2*/ virtual short getMinHeight() const;
    /*3*/ virtual void unk_vfn_3();
    /*4*/ virtual void unk_vfn_4();
    /*5*/ virtual class Block const& getExtraBlock(class BlockPos const&) const;
    /*6*/ virtual bool hasBiomeTag(unsigned __int64, class BlockPos const&) const;
    /*7*/ virtual bool setBlock(class BlockPos const&, class Block const&, int);
    /*8*/ virtual bool setBlockSimple(class BlockPos const&, class Block const&);
    /*9*/ virtual void unk_vfn_9();
    /*10*/ virtual void unk_vfn_10();
    /*11*/ virtual void unk_vfn_11();
    /*12*/ virtual void unk_vfn_12();
    /*13*/ virtual short getMaxHeight() const;
    /*14*/ virtual short getMinHeight() const;
    /*15*/ virtual void unk_vfn_15();
    /*16*/ virtual short getHeightmap(int, int);
    /*17*/ virtual bool isLegacyLevel();
    /*18*/ virtual class Biome const* getBiome(class BlockPos const&) const;
    /*19*/ virtual bool isInBounds(class Pos const&) const;
    /*20*/ virtual short getLocalWaterLevel(class BlockPos const&) const;
    /*21*/ virtual class LevelData const& getLevelData() const;
    /*22*/ virtual struct WorldGenContext const& getContext();
};