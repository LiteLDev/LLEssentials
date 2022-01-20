// This Header is auto generated by BDSLiteLoader Toolchain
#pragma once
#define AUTO_GENERATED
#include "../Global.h"

#define BEFORE_EXTRA
// Include Headers or Declare Types Here

#undef BEFORE_EXTRA

class WeakEntityRef {

#define AFTER_EXTRA
// Add Member There

#undef AFTER_EXTRA

#ifndef DISABLE_CONSTRUCTOR_PREVENTION_WEAKENTITYREF
public:
    class WeakEntityRef& operator=(class WeakEntityRef const&) = delete;
    WeakEntityRef(class WeakEntityRef const&) = delete;
    WeakEntityRef() = delete;
#endif

public:
    MCAPI WeakEntityRef(class WeakRefT<struct EntityRefTraits> const&);
    MCAPI WeakEntityRef(class WeakRefT<struct EntityRefTraits>&);
    MCAPI class WeakEntityRef& operator=(class WeakEntityRef&&);
    MCAPI bool operator==(class WeakEntityRef) const;
    MCAPI bool operator==(class WeakRefT<struct EntityRefTraits>) const;
    MCAPI ~WeakEntityRef();

protected:

private:

};