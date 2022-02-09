// This Header is auto generated by BDSLiteLoader Toolchain
#pragma once
#define AUTO_GENERATED
#include "../Global.h"
#include "Json.hpp"
#include "BlockCommandOrigin.hpp"

#define BEFORE_EXTRA
// Include Headers or Declare Types Here

#undef BEFORE_EXTRA

class MinecartBlockCommandOrigin : public BlockCommandOrigin {

#define AFTER_EXTRA
// Add Member There

#undef AFTER_EXTRA

#ifndef DISABLE_CONSTRUCTOR_PREVENTION_MINECARTBLOCKCOMMANDORIGIN
public:
    class MinecartBlockCommandOrigin& operator=(class MinecartBlockCommandOrigin const&) = delete;
    MinecartBlockCommandOrigin(class MinecartBlockCommandOrigin const&) = delete;
    MinecartBlockCommandOrigin() = delete;
#endif

public:
    /*0*/ virtual ~MinecartBlockCommandOrigin();
    /*3*/ virtual class BlockPos getBlockPosition() const;
    /*4*/ virtual class Vec3 getWorldPosition() const;
    /*8*/ virtual class Actor* getEntity() const;
    /*9*/ virtual enum CommandPermissionLevel getPermissionsLevel() const;
    /*10*/ virtual std::unique_ptr<class CommandOrigin> clone() const;
    /*11*/ virtual class std::optional<class BlockPos> getCursorHitBlockPos() const;
    /*12*/ virtual class std::optional<class Vec3> getCursorHitPos() const;
    /*15*/ virtual bool canUseAbility(enum AbilitiesIndex) const;
    /*17*/ virtual bool canUseCommandsWithoutCheatsEnabled() const;
    /*18*/ virtual bool isSelectorExpansionAllowed() const;
    /*20*/ virtual unsigned char getSourceSubId() const;
    /*23*/ virtual enum CommandOriginType getOriginType() const;
    /*26*/ virtual void handleCommandOutputCallback(class Json::Value&&) const;
    /*27*/ virtual void updateValues();
    /*29*/ virtual class CompoundTag serialize() const;
    /*30*/ virtual bool isValid() const;
    /*32*/ virtual class BaseCommandBlock* _getBaseCommandBlock(class BlockSource&) const;
    /*33*/ virtual class CommandBlockActor* _getBlockEntity(class BlockSource&) const;
    MCAPI MinecartBlockCommandOrigin(class BlockSource&, struct ActorUniqueID const&);
    MCAPI static std::unique_ptr<class MinecartBlockCommandOrigin> load(class CompoundTag const&, class Level&);

protected:

private:

};