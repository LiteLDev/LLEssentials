// This Header is auto generated by BDSLiteLoader Toolchain
#pragma once
#include <Global.h>
#define EXTRA_INCLUDE_PART_STRUCTUREANIMATIONACTION
#include "Extra/StructureAnimationActionAPI.hpp"
#undef EXTRA_INCLUDE_PART_STRUCTUREANIMATIONACTION
class StructureAnimationAction {
#include "Extra/StructureAnimationActionAPI.hpp"
public:
    /*0*/ virtual ~StructureAnimationAction();
    /*1*/ virtual void execute(class ServerLevel&, class Dimension&);
    /*2*/ virtual void serialize(class CompoundTag&);
    /*3*/ virtual bool operator==(class IRequestAction&);

public:
    MCAPI static std::unique_ptr<class StructureAnimationAction> load(class CompoundTag const&, std::string const&);
};