// This Header is auto generated by BDSLiteLoader Toolchain
#pragma once
#include <Global.h>
#include "OceanMonumentPiece.hpp"
#define EXTRA_INCLUDE_PART_OCEANMONUMENTSIMPLETOPROOM
#include "Extra/OceanMonumentSimpleTopRoomAPI.hpp"
#undef EXTRA_INCLUDE_PART_OCEANMONUMENTSIMPLETOPROOM
class OceanMonumentSimpleTopRoom : public OceanMonumentPiece {
#include "Extra/OceanMonumentSimpleTopRoomAPI.hpp"
public:
    /*0*/ virtual ~OceanMonumentSimpleTopRoom();
    /*2*/ virtual bool isValid() const;
    /*3*/ virtual int /*enum StructurePieceType*/ getType() const;
    /*4*/ virtual void addChildren(class StructurePiece&, std::vector<std::unique_ptr<class StructurePiece>>&, class Random&);
    /*5*/ virtual bool postProcess(class BlockSource&, class Random&, class BoundingBox const&);
    /*6*/ virtual void postProcessMobsAt(class BlockSource&, class Random&, class BoundingBox const&);
    /*10*/ virtual bool canBeReplaced(class BlockSource&, int, int, int, class BoundingBox const&);
};