// This Header is auto generated by BDSLiteLoader Toolchain
#pragma once
#define AUTO_GENERATED
#include "../Global.h"
#include "StructureStart.hpp"

#define BEFORE_EXTRA
// Include Headers or Declare Types Here

#undef BEFORE_EXTRA

class BuriedTreasureStart : public StructureStart {

#define AFTER_EXTRA
// Add Member There

#undef AFTER_EXTRA

#ifndef DISABLE_CONSTRUCTOR_PREVENTION_BURIEDTREASURESTART
public:
    class BuriedTreasureStart& operator=(class BuriedTreasureStart const&) = delete;
    BuriedTreasureStart(class BuriedTreasureStart const&) = delete;
    BuriedTreasureStart() = delete;
#endif

public:
    /*0*/ virtual ~BuriedTreasureStart();
    /*2*/ virtual void __unk_vfn_2();
    /*3*/ virtual enum StructureFeatureType getType() const;

protected:

private:

};