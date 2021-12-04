// This Header is auto generated by BDSLiteLoader Toolchain
#pragma once
#include <Global.h>
#define EXTRA_INCLUDE_PART_SERVERLEVELEVENTCOORDINATOR
#include "Extra/ServerLevelEventCoordinatorAPI.hpp"
#undef EXTRA_INCLUDE_PART_SERVERLEVELEVENTCOORDINATOR
class ServerLevelEventCoordinator {
#include "Extra/ServerLevelEventCoordinatorAPI.hpp"
public:
    /*0*/ virtual ~ServerLevelEventCoordinator();

public:
    MCAPI void sendLevelAddedPlayer(class Level&, class Player&);
    MCAPI void sendLevelRemovedPlayer(class Level&, class Player&);
    MCAPI void sendLevelSaveData(class Level&, class CompoundTag&);
};