// This Header is auto generated by BDSLiteLoader Toolchain
#pragma once
#define AUTO_GENERATED
#include "../Global.h"
#include "Actor.hpp"
#include "Slime.hpp"

#define BEFORE_EXTRA
// Include Headers or Declare Types Here

#undef BEFORE_EXTRA

class LavaSlime : public Slime {

#define AFTER_EXTRA
// Add Member There

#undef AFTER_EXTRA

#ifndef DISABLE_CONSTRUCTOR_PREVENTION_LAVASLIME
public:
    class LavaSlime& operator=(class LavaSlime const&) = delete;
    LavaSlime(class LavaSlime const&) = delete;
    LavaSlime() = delete;
#endif

public:
    /*8*/ virtual void reloadHardcoded(enum Actor::InitializationMethod, class VariantParameterList const&);
    /*14*/ virtual ~LavaSlime();
    /*20*/ virtual void __unk_vfn_20();
    /*22*/ virtual void __unk_vfn_22();
    /*36*/ virtual class Vec3 getInterpolatedRidingOffset(float) const;
    /*41*/ virtual void __unk_vfn_41();
    /*46*/ virtual void lerpMotion(class Vec3 const&);
    /*52*/ virtual float getRidingHeight();
    /*61*/ virtual void __unk_vfn_61();
    /*68*/ virtual void __unk_vfn_68();
    /*73*/ virtual void __unk_vfn_73();
    /*78*/ virtual float getCameraOffset() const;
    /*82*/ virtual void __unk_vfn_82();
    /*86*/ virtual float getBrightness(float) const;
    /*87*/ virtual void __unk_vfn_87();
    /*94*/ virtual void __unk_vfn_94();
    /*97*/ virtual void __unk_vfn_97();
    /*100*/ virtual void __unk_vfn_100();
    /*102*/ virtual void __unk_vfn_102();
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
    /*257*/ virtual void __unk_vfn_257();
    /*265*/ virtual void __unk_vfn_265();
    /*274*/ virtual void __unk_vfn_274();
    /*276*/ virtual void spawnAnim();
    /*290*/ virtual void aiStep();
    /*295*/ virtual bool checkSpawnRules(bool);
    /*298*/ virtual int getItemUseDuration() const;
    /*299*/ virtual float getItemUseStartupProgress() const;
    /*300*/ virtual float getItemUseIntervalProgress() const;
    /*303*/ virtual void __unk_vfn_303();
    /*305*/ virtual void __unk_vfn_305();
    /*307*/ virtual void __unk_vfn_307();
    /*312*/ virtual int getArmorValue();
    /*316*/ virtual void sendArmorDamage(class std::bitset<4> const&);
    /*331*/ virtual void onBorn(class Actor&, class Actor&);
    /*335*/ virtual int getAttackTime();
    /*338*/ virtual void __unk_vfn_338();
    /*344*/ virtual void jumpFromGround();
    /*348*/ virtual void _serverAiMobStep();
    /*354*/ virtual void __unk_vfn_354();
    /*356*/ virtual void __unk_vfn_356();
    /*357*/ virtual void __unk_vfn_357();
    /*361*/ virtual void __unk_vfn_361();
    /*364*/ virtual void decreaseSquish();
    /*365*/ virtual class OwnerPtrT<struct EntityRefTraits> createChild(int);
    /*
    inline bool isInLava() const{
        bool (LavaSlime::*rv)() const;
        *((void**)&rv) = dlsym("?isInLava@LavaSlime@@UEBA_NXZ");
        return (this->*rv)();
    }
    inline bool isOnFire() const{
        bool (LavaSlime::*rv)() const;
        *((void**)&rv) = dlsym("?isOnFire@LavaSlime@@MEBA_NXZ");
        return (this->*rv)();
    }
    inline bool isDarkEnoughToSpawn() const{
        bool (LavaSlime::*rv)() const;
        *((void**)&rv) = dlsym("?isDarkEnoughToSpawn@LavaSlime@@UEBA_NXZ");
        return (this->*rv)();
    }
    inline bool doPlayLandSound(){
        bool (LavaSlime::*rv)();
        *((void**)&rv) = dlsym("?doPlayLandSound@LavaSlime@@MEAA_NXZ");
        return (this->*rv)();
    }
    inline bool canDealDamage(){
        bool (LavaSlime::*rv)();
        *((void**)&rv) = dlsym("?canDealDamage@LavaSlime@@MEAA_NXZ");
        return (this->*rv)();
    }
    */
    MCAPI LavaSlime(class ActorDefinitionGroup*, struct ActorDefinitionIdentifier const&, class EntityContext&);

protected:

private:

};