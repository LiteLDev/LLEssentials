// This Header is auto generated by BDSLiteLoader Toolchain
#pragma once
#include <Global.h>
#define EXTRA_INCLUDE_PART_DESPAWNSYSTEM
#include "Extra/DespawnSystemAPI.hpp"
#undef EXTRA_INCLUDE_PART_DESPAWNSYSTEM
class DespawnSystem {
#include "Extra/DespawnSystemAPI.hpp"
public:
    /*0*/ virtual ~DespawnSystem();
    /*1*/ virtual void unk_vfn_1();
    /*2*/ virtual void tick(class EntityRegistry&);
};