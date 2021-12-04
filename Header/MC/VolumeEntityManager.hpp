// This Header is auto generated by BDSLiteLoader Toolchain
#pragma once
#include <Global.h>
#define EXTRA_INCLUDE_PART_VOLUMEENTITYMANAGER
#include "Extra/VolumeEntityManagerAPI.hpp"
#undef EXTRA_INCLUDE_PART_VOLUMEENTITYMANAGER
class VolumeEntityManager {
#include "Extra/VolumeEntityManagerAPI.hpp"
public:
    /*0*/ virtual ~VolumeEntityManager();

public:
    MCAPI static void bindVolumeDefinitions();
    MCAPI static bool isTriggerVolumesEnabled;
    MCAPI static void registerComponentNetRelevancy(class ComponentNetRelevancyRegistry&);

protected:
    MCAPI class OwnerPtrT<struct EntityRefTraits> _createVolumeEntity(class DefinitionInstanceGroup const&);
    MCAPI bool _definitionAlreadyExists(struct VolumeDefinition const&) const;
};