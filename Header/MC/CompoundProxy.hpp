// This Header is auto generated by BDSLiteLoader Toolchain
#pragma once
#define AUTO_GENERATED
#include "../Global.h"

#define BEFORE_EXTRA

#undef BEFORE_EXTRA

struct CompoundProxy {

#define AFTER_EXTRA

#undef AFTER_EXTRA

#ifndef DISABLE_CONSTRUCTOR_PREVENTION_COMPOUNDPROXY
public:
    struct CompoundProxy& operator=(struct CompoundProxy const&) = delete;
    CompoundProxy(struct CompoundProxy const&) = delete;
    CompoundProxy() = delete;
#endif

public:
    MCAPI void fromInt(int);
    MCAPI void fromString(std::string);

protected:

private:

};