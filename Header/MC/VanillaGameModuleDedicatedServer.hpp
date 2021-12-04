// This Header is auto generated by BDSLiteLoader Toolchain
#pragma once
#include <Global.h>
#define EXTRA_INCLUDE_PART_VANILLAGAMEMODULEDEDICATEDSERVER
#include "Extra/VanillaGameModuleDedicatedServerAPI.hpp"
#undef EXTRA_INCLUDE_PART_VANILLAGAMEMODULEDEDICATEDSERVER
class VanillaGameModuleDedicatedServer {
#include "Extra/VanillaGameModuleDedicatedServerAPI.hpp"
public:
    /*0*/ virtual ~VanillaGameModuleDedicatedServer();
    /*1*/ virtual std::unique_ptr<class GameModuleServer> createGameModuleServer();
    /*2*/ virtual class std::shared_ptr<class IInPackagePacks> createInPackagePacks();
    /*3*/ virtual void registerMolangQueries();
    /*4*/ virtual void registerServerInstanceHandler(class ServerInstanceEventCoordinator&);
};