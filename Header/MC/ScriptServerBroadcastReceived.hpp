// This Header is auto generated by BDSLiteLoader Toolchain
#pragma once
#include <Global.h>
#include "ScriptApi.hpp"
#define EXTRA_INCLUDE_PART_SCRIPTSERVERBROADCASTRECEIVED
#include "Extra/ScriptServerBroadcastReceivedAPI.hpp"
#undef EXTRA_INCLUDE_PART_SCRIPTSERVERBROADCASTRECEIVED
class ScriptServerBroadcastReceived {
#include "Extra/ScriptServerBroadcastReceivedAPI.hpp"
public:
    /*0*/ virtual ~ScriptServerBroadcastReceived();
    /*1*/ virtual bool receivedEvent(class ScriptApi::ScriptVersionInfo const&, class ScriptEngine&, class ScriptServerContext&, std::string const&, class ScriptApi::ScriptObjectHandle const&);
    /*2*/ virtual bool getEventData(class ScriptApi::ScriptVersionInfo const&, class ScriptEngine&, class ScriptServerContext&, std::string const&, class ScriptApi::ScriptObjectHandle&);
};