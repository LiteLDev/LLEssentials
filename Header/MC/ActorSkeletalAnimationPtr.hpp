// This Header is auto generated by BDSLiteLoader Toolchain
#pragma once
#include <Global.h>
#define EXTRA_INCLUDE_PART_ACTORSKELETALANIMATIONPTR
#include "Extra/ActorSkeletalAnimationPtrAPI.hpp"
#undef EXTRA_INCLUDE_PART_ACTORSKELETALANIMATIONPTR
class ActorSkeletalAnimationPtr {
#include "Extra/ActorSkeletalAnimationPtrAPI.hpp"

public:
    MCAPI class HashedString const& getName() const;
    MCAPI bool isNull() const;
    MCAPI class ActorSkeletalAnimation* operator->();
    MCAPI class ActorSkeletalAnimation const* operator->();
    MCAPI class ActorSkeletalAnimationPtr& operator=(class ActorSkeletalAnimationPtr const&);

    MCAPI static class ActorSkeletalAnimationPtr const NONE;
};