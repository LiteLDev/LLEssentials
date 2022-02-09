// This Header is auto generated by BDSLiteLoader Toolchain
#pragma once
#define AUTO_GENERATED
#include "../Global.h"

#define BEFORE_EXTRA
// Include Headers or Declare Types Here

#undef BEFORE_EXTRA

class ActorMapping {

#define AFTER_EXTRA
// Add Member There

#undef AFTER_EXTRA

#ifndef DISABLE_CONSTRUCTOR_PREVENTION_ACTORMAPPING
public:
    class ActorMapping& operator=(class ActorMapping const&) = delete;
    ActorMapping(class ActorMapping const&) = delete;
    ActorMapping() = delete;
#endif

public:
    MCAPI ActorMapping(std::string const&, std::string const&, std::string const&);
    MCAPI ActorMapping(std::string const&, std::string const&);
    MCAPI std::string getMappingName(enum ActorTypeNamespaceRules) const;
    MCAPI ~ActorMapping();

protected:

private:

};