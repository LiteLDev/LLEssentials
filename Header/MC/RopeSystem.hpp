// This Header is auto generated by BDSLiteLoader Toolchain
#pragma once
#include <Global.h>
#define EXTRA_INCLUDE_PART_ROPESYSTEM
#include "Extra/RopeSystemAPI.hpp"
#undef EXTRA_INCLUDE_PART_ROPESYSTEM
class RopeSystem {
#include "Extra/RopeSystemAPI.hpp"

public:
    MCAPI void _initializePins(class Vec3 const&, class Vec3 const&);
    MCAPI void cutAtPercent(float);
    MCAPI void initialize(struct RopeParams const&);
    MCAPI bool isCut() const;
    MCAPI bool isDestroyed() const;
    MCAPI void queueTick(class BlockSource&, class std::shared_ptr<class RopeSystem>&);

    MCAPI static float const sBucketLength;
    MCAPI static bool sEnabled;
    MCAPI static float const sEpsilon;

private:
    MCAPI void _finalizeBucket(struct AABBBucket&);
    MCAPI void _initializePins();
    MCAPI void _integrate();
    MCAPI void _prepareAABBBuckets();
    MCAPI float _propagateDistanceConstraint(class Vec3 const&, class Vec3&, float);
    MCAPI void _pruneDenyList();
    MCAPI void _pushRange(unsigned __int64, unsigned __int64);
    MCAPI void _resizeRope();
    MCAPI float _solveCollisions(bool);
    MCAPI float _solveDistanceConstraint(class Vec3&, class Vec3&, float);
    MCAPI float _solveDistanceConstraintBlock(class Vec3&, class Vec3&, class Vec3&, class Vec3&, float);
    MCAPI float _solveDistanceConstraints3();
    MCAPI void _tick();
    MCAPI void _tickWaves();
    MCAPI void _updateRenderPoints();
};