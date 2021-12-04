// This Header is auto generated by BDSLiteLoader Toolchain
#pragma once
#include <Global.h>
#define EXTRA_INCLUDE_PART_NPCSCENEDIALOGUEDATA
#include "Extra/NpcSceneDialogueDataAPI.hpp"
#undef EXTRA_INCLUDE_PART_NPCSCENEDIALOGUEDATA
class NpcSceneDialogueData {
#include "Extra/NpcSceneDialogueDataAPI.hpp"
public:
    /*0*/ virtual ~NpcSceneDialogueData();
    /*1*/ virtual std::string const& getDialogueText() const;
    /*2*/ virtual void unk_vfn_2();
    /*3*/ virtual std::string const& getNameText() const;
    /*4*/ virtual std::string const& getNameRawText() const;
    /*5*/ virtual std::string const& getSceneName() const;
    /*6*/ virtual struct NpcActionsContainer& getActionsContainer();
    /*7*/ virtual struct NpcActionsContainer const& getActionsContainer() const;
    /*8*/ virtual struct ActorUniqueID const& getActorUniqueID();
};