// This Header is auto generated by BDSLiteLoader Toolchain
#pragma once
#include <Global.h>
#include "Scripting.hpp"
#define EXTRA_INCLUDE_PART_SCRIPTSERVERNETWORKEVENTHANDLER
#include "Extra/ScriptServerNetworkEventHandlerAPI.hpp"
#undef EXTRA_INCLUDE_PART_SCRIPTSERVERNETWORKEVENTHANDLER
class ScriptServerNetworkEventHandler {
#include "Extra/ScriptServerNetworkEventHandlerAPI.hpp"
public:
    /*0*/ virtual ~ScriptServerNetworkEventHandler();
    /*1*/ virtual struct GameplayHandlerResult<int /*enum CoordinatorResult*/> handleChat(struct ChatEvent&);

private:
    MCAPI bool _handleChat(struct ChatEvent&, class Scripting::WeakLifetimeScope const&, struct Scripting::TypedObjectHandle<class ScriptWorldEvents>) const;
};