// This Header is auto generated by BDSLiteLoader Toolchain
#pragma once
#define AUTO_GENERATED
#include "../Global.h"
#include "FilterTest.hpp"
#include "Json.hpp"

#define BEFORE_EXTRA
// Include Headers or Declare Types Here

#undef BEFORE_EXTRA

class ActorUnderwaterTest : public FilterTest {

#define AFTER_EXTRA
// Add Member There

#undef AFTER_EXTRA

#ifndef DISABLE_CONSTRUCTOR_PREVENTION_ACTORUNDERWATERTEST
public:
    class ActorUnderwaterTest& operator=(class ActorUnderwaterTest const&) = delete;
    ActorUnderwaterTest(class ActorUnderwaterTest const&) = delete;
    ActorUnderwaterTest() = delete;
#endif

public:
    /*0*/ virtual ~ActorUnderwaterTest();
    /*2*/ virtual bool evaluate(struct FilterContext const&) const;
    /*3*/ virtual void finalizeParsedValue(class IWorldRegistriesProvider&);
    /*4*/ virtual class gsl::basic_string_span<char const, -1> getName() const;
    /*
    inline  ~ActorUnderwaterTest(){
         (ActorUnderwaterTest::*rv)();
        *((void**)&rv) = dlsym("??1ActorUnderwaterTest@@UEAA@XZ");
        return (this->*rv)();
    }
    */

protected:

private:

};