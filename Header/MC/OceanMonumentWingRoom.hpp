// This Header is auto generated by BDSLiteLoader Toolchain
#pragma once
#define AUTO_GENERATED
#include "../Global.h"
#include "OceanMonumentPiece.hpp"

#define BEFORE_EXTRA
// Include Headers or Declare Types Here

#undef BEFORE_EXTRA

class OceanMonumentWingRoom : public OceanMonumentPiece {

#define AFTER_EXTRA
// Add Member There

#undef AFTER_EXTRA

#ifndef DISABLE_CONSTRUCTOR_PREVENTION_OCEANMONUMENTWINGROOM
public:
    class OceanMonumentWingRoom& operator=(class OceanMonumentWingRoom const&) = delete;
    OceanMonumentWingRoom(class OceanMonumentWingRoom const&) = delete;
    OceanMonumentWingRoom() = delete;
#endif

public:
    /*0*/ virtual ~OceanMonumentWingRoom();
    /*2*/ virtual class PoolElementStructurePiece* asPoolElement();
    /*3*/ virtual enum StructurePieceType getType() const;
    /*4*/ virtual void addChildren(class StructurePiece&, std::vector<std::unique_ptr<class StructurePiece>>&, class Random&);
    /*5*/ virtual bool postProcess(class BlockSource&, class Random&, class BoundingBox const&);
    /*6*/ virtual void postProcessMobsAt(class BlockSource&, class Random&, class BoundingBox const&);
    /*10*/ virtual void __unk_vfn_10();

protected:

private:

};