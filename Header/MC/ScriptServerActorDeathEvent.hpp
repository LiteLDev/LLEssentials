// This Header is auto generated by BDSLiteLoader Toolchain
#pragma once
#include <Global.h>
#include "ScriptApi.hpp"
#define EXTRA_INCLUDE_PART_SCRIPTSERVERACTORDEATHEVENT
#include "Extra/ScriptServerActorDeathEventAPI.hpp"
#undef EXTRA_INCLUDE_PART_SCRIPTSERVERACTORDEATHEVENT
class ScriptServerActorDeathEvent {
#include "Extra/ScriptServerActorDeathEventAPI.hpp"
public:
    /*0*/ virtual ~ScriptServerActorDeathEvent();
    /*1*/ virtual bool _serialize(class ScriptEngine&, class ScriptApi::ScriptObjectHandle&) const;

public:
    MCAPI void setActorId(struct ActorUniqueID const&);
    MCAPI void setBlockPos(class BlockPos const&);
    MCAPI void setCause(std::string const&);
    MCAPI void setKillerId(struct ActorUniqueID const&);
    MCAPI void setProjectile(enum ActorType const&);

private:
    MCAPI static class HashedString const mHash;
};