// This Header is auto generated by BDSLiteLoader Toolchain
#pragma once
#define AUTO_GENERATED
#include "../Global.h"
#include "MoveInput.hpp"

#define BEFORE_EXTRA
// Include Headers or Declare Types Here

#undef BEFORE_EXTRA

class ServerMoveInputHandler : public MoveInput {

#define AFTER_EXTRA
// Add Member There

#undef AFTER_EXTRA

#ifndef DISABLE_CONSTRUCTOR_PREVENTION_SERVERMOVEINPUTHANDLER
public:
    class ServerMoveInputHandler& operator=(class ServerMoveInputHandler const&) = delete;
    ServerMoveInputHandler(class ServerMoveInputHandler const&) = delete;
#endif

public:
    /*0*/ virtual ~ServerMoveInputHandler();
    /*2*/ virtual void __unk_vfn_2();
    /*3*/ virtual void __unk_vfn_3();
    /*5*/ virtual void __unk_vfn_5();
    /*6*/ virtual void __unk_vfn_6();
    /*8*/ virtual void setAutoJumpingInWater(bool);
    /*9*/ virtual void __unk_vfn_9();
    /*10*/ virtual void setSneakDown(bool);
    /*12*/ virtual class Vec3 const& getGazeDirection() const;
    /*
    inline void registerInputHandlers(class InputHandler& a0){
        void (ServerMoveInputHandler::*rv)(class InputHandler&);
        *((void**)&rv) = dlsym("?registerInputHandlers@ServerMoveInputHandler@@UEAAXAEAVInputHandler@@@Z");
        return (this->*rv)(std::forward<class InputHandler&>(a0));
    }
    */
    MCAPI ServerMoveInputHandler();
    MCAPI void digestPlayerInputPacket(class PlayerAuthInputPacket const&);

protected:

private:

};