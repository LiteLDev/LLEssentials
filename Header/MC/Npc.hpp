// This Header is auto generated by BDSLiteLoader Toolchain
#pragma once
#define AUTO_GENERATED
#include "../Global.h"
#include "Actor.hpp"
#include "Mob.hpp"

#define BEFORE_EXTRA
// Include Headers or Declare Types Here

#undef BEFORE_EXTRA

class Npc : public Mob {

#define AFTER_EXTRA
// Add Member There

#undef AFTER_EXTRA

#ifndef DISABLE_CONSTRUCTOR_PREVENTION_NPC
public:
    class Npc& operator=(class Npc const&) = delete;
    Npc(class Npc const&) = delete;
    Npc() = delete;
#endif

public:
    /*8*/ virtual void reloadHardcoded(enum Actor::InitializationMethod, class VariantParameterList const&);
    /*10*/ virtual void initializeComponents(enum Actor::InitializationMethod, class VariantParameterList const&);
    /*14*/ virtual ~Npc();
    /*20*/ virtual void __unk_vfn_20();
    /*22*/ virtual void __unk_vfn_22();
    /*36*/ virtual class Vec3 getInterpolatedRidingOffset(float) const;
    /*41*/ virtual void __unk_vfn_41();
    /*46*/ virtual void lerpMotion(class Vec3 const&);
    /*52*/ virtual float getRidingHeight();
    /*60*/ virtual void __unk_vfn_60();
    /*61*/ virtual void __unk_vfn_61();
    /*65*/ virtual std::string getFormattedNameTag() const;
    /*68*/ virtual void __unk_vfn_68();
    /*78*/ virtual float getCameraOffset() const;
    /*82*/ virtual void __unk_vfn_82();
    /*87*/ virtual void __unk_vfn_87();
    /*88*/ virtual void playerTouch(class Player&);
    /*94*/ virtual void __unk_vfn_94();
    /*97*/ virtual void __unk_vfn_97();
    /*100*/ virtual void __unk_vfn_100();
    /*104*/ virtual void __unk_vfn_104();
    /*106*/ virtual void __unk_vfn_106();
    /*107*/ virtual void __unk_vfn_107();
    /*108*/ virtual void __unk_vfn_108();
    /*112*/ virtual class Actor* findAttackTarget();
    /*113*/ virtual void __unk_vfn_113();
    /*116*/ virtual void adjustDamageAmount(int&) const;
    /*120*/ virtual void onTame();
    /*121*/ virtual void onFailedTame();
    /*130*/ virtual void vehicleLanded(class Vec3 const&, class Vec3 const&);
    /*140*/ virtual void onBounceStarted(class BlockPos const&, class Block const&);
    /*143*/ virtual float getPickRadius();
    /*152*/ virtual void awardKillScore(class Actor&, int);
    /*171*/ virtual class HashedString const& queryEntityRenderer() const;
    /*172*/ virtual struct ActorUniqueID getSourceUniqueID() const;
    /*179*/ virtual int getPortalWaitTime() const;
    /*181*/ virtual void __unk_vfn_181();
    /*182*/ virtual void __unk_vfn_182();
    /*184*/ virtual struct ActorUniqueID getControllingPlayer() const;
    /*193*/ virtual void __unk_vfn_193();
    /*194*/ virtual void __unk_vfn_194();
    /*196*/ virtual void __unk_vfn_196();
    /*199*/ virtual void __unk_vfn_199();
    /*203*/ virtual void buildDebugInfo(std::string&) const;
    /*211*/ virtual void __unk_vfn_211();
    /*221*/ virtual void __unk_vfn_221();
    /*222*/ virtual void __unk_vfn_222();
    /*227*/ virtual void __unk_vfn_227();
    /*228*/ virtual void __unk_vfn_228();
    /*229*/ virtual void __unk_vfn_229();
    /*233*/ virtual void __unk_vfn_233();
    /*234*/ virtual void setAuxValue(int);
    /*240*/ virtual void stopSpinAttack();
    /*242*/ virtual void __unk_vfn_242();
    /*245*/ virtual void __unk_vfn_245();
    /*247*/ virtual void die(class ActorDamageSource const&);
    /*257*/ virtual void __unk_vfn_257();
    /*258*/ virtual bool _hurt(class ActorDamageSource const&, int, bool, bool);
    /*265*/ virtual void __unk_vfn_265();
    /*273*/ virtual void _onSizeUpdated();
    /*274*/ virtual void __unk_vfn_274();
    /*275*/ virtual void knockback(class Actor*, int, float, float, float, float, float);
    /*276*/ virtual void spawnAnim();
    /*298*/ virtual int getItemUseDuration() const;
    /*299*/ virtual float getItemUseStartupProgress() const;
    /*300*/ virtual float getItemUseIntervalProgress() const;
    /*303*/ virtual void __unk_vfn_303();
    /*305*/ virtual void __unk_vfn_305();
    /*307*/ virtual void __unk_vfn_307();
    /*316*/ virtual void sendArmorDamage(class std::bitset<4> const&);
    /*331*/ virtual void onBorn(class Actor&, class Actor&);
    /*335*/ virtual int getAttackTime();
    /*336*/ virtual float _getWalkTargetValue(class BlockPos const&);
    /*337*/ virtual void __unk_vfn_337();
    /*338*/ virtual void __unk_vfn_338();
    /*347*/ virtual void newServerAiStep();
    /*348*/ virtual void _serverAiMobStep();
    /*354*/ virtual void __unk_vfn_354();
    /*
    inline bool canBeAffected(class MobEffectInstance const& a0) const{
        bool (Npc::*rv)(class MobEffectInstance const&) const;
        *((void**)&rv) = dlsym("?canBeAffected@Npc@@UEBA_NAEBVMobEffectInstance@@@Z");
        return (this->*rv)(std::forward<class MobEffectInstance const&>(a0));
    }
    inline bool isFishable() const{
        bool (Npc::*rv)() const;
        *((void**)&rv) = dlsym("?isFishable@Npc@@UEBA_NXZ");
        return (this->*rv)();
    }
    inline bool canBePulledIntoVehicle() const{
        bool (Npc::*rv)() const;
        *((void**)&rv) = dlsym("?canBePulledIntoVehicle@Npc@@UEBA_NXZ");
        return (this->*rv)();
    }
    inline bool isTargetable() const{
        bool (Npc::*rv)() const;
        *((void**)&rv) = dlsym("?isTargetable@Npc@@UEBA_NXZ");
        return (this->*rv)();
    }
    inline void _serverAiMobStep(){
        void (Npc::*rv)();
        *((void**)&rv) = dlsym("?_serverAiMobStep@Npc@@MEAAXXZ");
        return (this->*rv)();
    }
    inline bool canExistWhenDisallowMob() const{
        bool (Npc::*rv)() const;
        *((void**)&rv) = dlsym("?canExistWhenDisallowMob@Npc@@UEBA_NXZ");
        return (this->*rv)();
    }
    inline bool interactPreventDefault(){
        bool (Npc::*rv)();
        *((void**)&rv) = dlsym("?interactPreventDefault@Npc@@UEAA_NXZ");
        return (this->*rv)();
    }
    inline bool breaksFallingBlocks() const{
        bool (Npc::*rv)() const;
        *((void**)&rv) = dlsym("?breaksFallingBlocks@Npc@@UEBA_NXZ");
        return (this->*rv)();
    }
    inline bool canShowNameTag() const{
        bool (Npc::*rv)() const;
        *((void**)&rv) = dlsym("?canShowNameTag@Npc@@UEBA_NXZ");
        return (this->*rv)();
    }
    inline bool useNewAi() const{
        bool (Npc::*rv)() const;
        *((void**)&rv) = dlsym("?useNewAi@Npc@@UEBA_NXZ");
        return (this->*rv)();
    }
    inline void newServerAiStep(){
        void (Npc::*rv)();
        *((void**)&rv) = dlsym("?newServerAiStep@Npc@@UEAAXXZ");
        return (this->*rv)();
    }
    */
    MCAPI Npc(class ActorDefinitionGroup*, struct ActorDefinitionIdentifier const&, class EntityContext&);
    MCAPI static std::string const SKIN_ID_TAG;
    MCAPI static std::vector<struct std::pair<std::string, std::string >> const Skins;

protected:

private:

};