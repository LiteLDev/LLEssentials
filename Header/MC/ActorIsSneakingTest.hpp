// This Header is auto generated by BDSLiteLoader Toolchain
#pragma once
#define AUTO_GENERATED
#include "../Global.h"
#include "FilterTest.hpp"
#include "Json.hpp"

#define BEFORE_EXTRA
// Include Headers or Declare Types Here

#undef BEFORE_EXTRA

class ActorIsSneakingTest : public FilterTest {

#define AFTER_EXTRA
// Add Member There

#undef AFTER_EXTRA

#ifndef DISABLE_CONSTRUCTOR_PREVENTION_ACTORISSNEAKINGTEST
public:
    class ActorIsSneakingTest& operator=(class ActorIsSneakingTest const&) = delete;
    ActorIsSneakingTest(class ActorIsSneakingTest const&) = delete;
    ActorIsSneakingTest() = delete;
#endif

public:
    /*0*/ virtual ~ActorIsSneakingTest();
    /*2*/ virtual bool evaluate(struct FilterContext const&) const;
    /*3*/ virtual void finalizeParsedValue(class IWorldRegistriesProvider&);
    /*4*/ virtual class gsl::basic_string_span<char const, -1> getName() const;
    /*
    inline  ~ActorIsSneakingTest(){
         (ActorIsSneakingTest::*rv)();
        *((void**)&rv) = dlsym("??1ActorIsSneakingTest@@UEAA@XZ");
        return (this->*rv)();
    }
    */

protected:

private:

};