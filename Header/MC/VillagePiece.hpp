// This Header is auto generated by BDSLiteLoader Toolchain
#pragma once
#include <Global.h>
#include "PoolElementStructurePiece.hpp"
#define EXTRA_INCLUDE_PART_VILLAGEPIECE
#include "Extra/VillagePieceAPI.hpp"
#undef EXTRA_INCLUDE_PART_VILLAGEPIECE
class VillagePiece : public PoolElementStructurePiece {
#include "Extra/VillagePieceAPI.hpp"
public:
    /*0*/ virtual ~VillagePiece();
    /*2*/ virtual class PoolElementStructurePiece* asPoolElement();
    /*3*/ virtual int /*enum StructurePieceType*/ getType() const;
    /*4*/ virtual void addChildren(class StructurePiece&, std::vector<std::unique_ptr<class StructurePiece>>&, class Random&);
    /*10*/ virtual bool canBeReplaced(class BlockSource&, int, int, int, class BoundingBox const&);
    /*12*/ virtual int getWorldZ(int, int);
    /*13*/ virtual int generateHeightAtPosition(class BlockPos const&, class Dimension&, class BlockVolume&, class std::unordered_map<class ChunkPos, std::unique_ptr<std::vector<short>>, struct std::hash<class ChunkPos>, struct std::equal_to<class ChunkPos>, class std::allocator<struct std::pair<class ChunkPos const, std::unique_ptr<std::vector<short>>>>>&) const;
    /*14*/ virtual class Block const* getSupportBlock(class BlockSource&, class BlockPos const&, class Block const&) const;
    /*15*/ virtual class Block const& getBeardStabilizeBlock(class Block const&) const;
    /*16*/ virtual int /*enum AdjustmentEffect*/ getTerrainAdjustmentEffect() const;
    /*17*/ virtual bool _needsPostProcessing(class BlockSource&);

public:
    MCAPI static void addPieces(class BlockPos, std::vector<std::unique_ptr<class StructurePiece>>&, class Random&, class JigsawStructureRegistry&, enum VanillaBiomeTypes, class Dimension&);
};