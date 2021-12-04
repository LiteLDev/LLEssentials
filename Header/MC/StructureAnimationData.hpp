// This Header is auto generated by BDSLiteLoader Toolchain
#pragma once
#include <Global.h>
#define EXTRA_INCLUDE_PART_STRUCTUREANIMATIONDATA
#include "Extra/StructureAnimationDataAPI.hpp"
#undef EXTRA_INCLUDE_PART_STRUCTUREANIMATIONDATA
class StructureAnimationData {
#include "Extra/StructureAnimationDataAPI.hpp"

public:
    MCAPI class BlockPos const& getPosition() const;
    MCAPI std::string const& getStructureName() const;
    MCAPI class StructureSettings const& getStructureSettings() const;
    MCAPI class CompoundTag& serialize(class CompoundTag&);
    MCAPI void setCmdArea(std::unique_ptr<class CommandArea>);

    MCAPI static class StructureAnimationData load(std::string const&, class CompoundTag const&);
};