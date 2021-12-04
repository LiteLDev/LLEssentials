// This Header is auto generated by BDSLiteLoader Toolchain
#pragma once
#include <Global.h>
#define EXTRA_INCLUDE_PART_DELAYACTIONLIST
#include "Extra/DelayActionListAPI.hpp"
#undef EXTRA_INCLUDE_PART_DELAYACTIONLIST
class DelayActionList {
#include "Extra/DelayActionListAPI.hpp"
public:
    /*0*/ virtual ~DelayActionList();

public:
    MCAPI enum QueueRequestResult queueRequestOrExecuteAction(class DelayRequest, class ServerLevel&, class Dimension&, unsigned __int64, bool);
    MCAPI void tick(class ServerLevel&, class Dimension&, unsigned __int64);
};