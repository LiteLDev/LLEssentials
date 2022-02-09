// This Header is auto generated by BDSLiteLoader Toolchain
#pragma once
#define AUTO_GENERATED
#include "../Global.h"
#include "Actor.hpp"
#include "Animal.hpp"

#define BEFORE_EXTRA
// Include Headers or Declare Types Here

#undef BEFORE_EXTRA

class Llama : public Animal {

#define AFTER_EXTRA
// Add Member There

#undef AFTER_EXTRA

#ifndef DISABLE_CONSTRUCTOR_PREVENTION_LLAMA
public:
    class Llama& operator=(class Llama const&) = delete;
    Llama(class Llama const&) = delete;
    Llama() = delete;
#endif

public:
    /*14*/ virtual ~Llama();
    /*20*/ virtual void __unk_vfn_20();
    /*22*/ virtual void __unk_vfn_22();
    /*36*/ virtual class Vec3 getInterpolatedRidingOffset(float) const;
    /*41*/ virtual void __unk_vfn_41();
    /*46*/ virtual void lerpMotion(class Vec3 const&);
    /*52*/ virtual float getRidingHeight();
    /*61*/ virtual void __unk_vfn_61();
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
    /*186*/ virtual void causeFallDamage(float, float, class ActorDamageSource);
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
    /*255*/ virtual void updateEntitySpecificMolangVariables(class RenderParams&);
    /*257*/ virtual void __unk_vfn_257();
    /*263*/ virtual void _playStepSound(class BlockPos const&, class Block const&);
    /*265*/ virtual void __unk_vfn_265();
    /*274*/ virtual void __unk_vfn_274();
    /*276*/ virtual void spawnAnim();
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
    /*348*/ virtual void _serverAiMobStep();
    /*354*/ virtual void __unk_vfn_354();
    /*
    inline bool useNewAi() const{
        bool (Llama::*rv)() const;
        *((void**)&rv) = dlsym("?useNewAi@Llama@@MEBA_NXZ");
        return (this->*rv)();
    }
    */
    MCAPI Llama(class ActorDefinitionGroup*, struct ActorDefinitionIdentifier const&, class EntityContext&);

protected:

private:

};