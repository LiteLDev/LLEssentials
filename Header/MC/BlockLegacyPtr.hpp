// This Header is auto generated by BDSLiteLoader Toolchain
#pragma once
#include <Global.h>
#define EXTRA_INCLUDE_PART_BLOCKLEGACYPTR
#include "Extra/BlockLegacyPtrAPI.hpp"
#undef EXTRA_INCLUDE_PART_BLOCKLEGACYPTR
class BlockLegacyPtr {
#include "Extra/BlockLegacyPtrAPI.hpp"

public:
    MCAPI bool Deserialize(class BasicLoader&, struct SerializerTraits const&, class BedrockLoadContext const&);
    MCAPI bool Serialize(class BasicSaver&, struct SerializerTraits const&) const;
};