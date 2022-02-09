#pragma once

#include "HookAPI.h"
#include "../Global.h"
#include "Vec2.hpp"
#include "Vec3.hpp"
#include "BlockPos.hpp"
#include "AABB.hpp"
#include "ChunkPos.hpp"
#include "ChunkBlockPos.hpp"

typedef std::string xuid_t;
typedef unsigned long long QWORD;

namespace mce
{
class UUID
{
    uint64_t a, b;

public:
    MCAPI std::string asString() const;
    MCAPI static UUID fromString(std::string const&);
    MCAPI bool isEmpty() const;
    MCAPI static UUID seedFromString(std::string const&);

    inline operator bool() const
    {
        return !isEmpty();
    }
};

class Color;

}; // namespace mce


class BoundingBox
{
public:
    BlockPos bpos1;
    BlockPos bpos2;

    inline BlockPos getCenter() const
    {
        return {(bpos1.x + bpos2.x) / 2, (bpos1.y + bpos2.y) / 2, (bpos1.z + bpos2.z) / 2};
    }

    LIAPI AABB toAABB() const;
};

template <typename A, typename T>
class AutomaticID
{
    T id;

public:
    AutomaticID()
    {
        id = 0;
    }

    AutomaticID(T x)
    {
        id = x;
    }

    inline operator T() const
    {
        return id;
    }
};

struct ActorUniqueID
{
    long long id;

public:
    ActorUniqueID()
    {
        id = -1;
    }

    ActorUniqueID(long long i)
    {
        id = i;
    }

    inline long long get() const
    {
        return id;
    }

    inline operator long long() const
    {
        return id;
    }
};
//static_assert(!std::is_pod_v<ActorUniqueID>);


class ActorRuntimeID
{
public:
    unsigned long long id;

    inline unsigned long long get() const
    {
        return id;
    }

    inline operator unsigned long long() const
    {
        return id;
    }
};
//static_assert(std::is_pod_v<ActorRuntimeID>);

#include "../MC/RelativeFloat.hpp"
//class RelativeFloat {
//public:
//    float value;
//    bool is_relative;
//
//    RelativeFloat(float value)
//        : value(value)
//        , is_relative(true) {
//    }
//
//    inline float getFloat(float center) const {
//        if (is_relative)
//            return center + value;
//        return value;
//    }
//};

//namespace Core {
//
//class PathPart {
//public:
//    std::string data;
//};
//
//class Path : public PathPart {
//public:
//};
//
//template <typename T>
//class PathBuffer {
//    T value;
//    operator T&() noexcept {
//        return value;
//    }
//    operator T const &() const noexcept {
//        return value;
//    }
//};
//
//}; // namespace Core

namespace gametest
{
class BaseGameTestBatchRunner;

class BaseGameTestFunction;

class BaseGameTestHelper;

class BaseGameTestInstance;

class GameTestBatch;

struct GameTestError;

class GameTestRegistry;

class GameTestTicker;

class IGameTestFunctionContext;

class IGameTestHelperProvider;

struct TestParameters;
}; // namespace gametest

namespace DBHelpers
{
enum Category;
}; // namespace DBHelpers

class AgentCommands
{
public:
    class Command;
};

#include "../MC/Automation.hpp"

class ClientBlobCache
{
public:
    struct Server
    {
        class TransferBuilder;

        class ActiveTransfersManager;
    };
};

class ClientBlockPipeline
{
public:
    template <typename T>
    class VolumeOf;

    struct BlockSchematic;
};

struct ISurfaceBuilder
{
    struct BuildParameters;
};

struct FeatureLoading
{
    template <typename T>
    struct ConcreteFeatureHolder;
    struct FeatureRootParseContext;
    template <typename T>
    struct ConcreteFeatureHolder;
};

template <typename T1, typename T2>
class OperationNode;

struct OperationNodeDetails
{
    template <typename T1, typename T2>
    class WorkingData;
};

struct PositionTrackingDB
{
    class TrackingRecord;
};


struct SubChunkBrightnessStorage
{
    struct LightPair;
};

struct BlockGeometry
{
    struct Model;

    class TessellatedModel;
};

struct CanyonFeatureUtils
{
    struct CanyonConfiguration;
};

class IInPackagePacks
{
public:
    struct MetaData;
};

struct GameEventConfig
{
    enum GameEvents;
};

#include "IMinecraftEventing.hpp"

struct OperationNodeValues
{
    enum Terrain;
};

struct SubChunkStorageUnit
{
    enum PruneType;
};

//Templates
template <typename T, typename T2, int unk>
class TypedServerNetId
{
public:
    T2 netId;
    inline operator T2()
    {
        return netId;
    }
};

template <typename T, typename T2, int unk>
class TypedClientNetId
{
public:
    T2 netId;
};

template <typename T, typename T2, int unk>
class TypedRuntimeId
{
public:
    T2 netId;
};

template <typename T, typename T2>
class AutomaticID;

template<typename T, typename T2>
class BidirectionalUnorderedMap {
public:
    std::unordered_map<T, T2> mMap1;
    std::unordered_map<T2, T> mMap2;
};

template <typename T>
class BlockDataFetchResult;

template <typename T>
class CommandSelectorResults;

template <typename... T>
class Factory;

template <typename T>
class InheritanceTree;

//enum class ItemStackRequestActionType : char;
//template <typename T, ItemStackRequestActionType actionType>
//class ItemStackRequestActionCraft;

template <typename T>
class ItemStateVariant;

template <typename T>
class LevelChunkGridAreaElement;

template <typename T>
class GridArea;

template <typename T>
class OwnerPtrT;

template <typename T>
class ServiceReference;

template <typename T>
class SharedPtr;

template <typename T>
class StackRefResultT;

template<typename T>
class WeakPtr {
    T** value;
public:
    inline T* get()
    {
        if (value)
            return *value;
        return nullptr;
    }
    inline T const* get() const
    {
        if (value)
            return *value;
        return nullptr;
    }
    inline T& operator*()
    {
        return *get();
    }
    inline T const& operator*() const
    {
        return *get();
    }
    //inline operator ->() {

    //}
};

template <typename T>
class WeakRefT;

template <typename T>
struct SharePtrRefTraits;

template <typename T>
class SubChunkStorage;

template <typename T, typename T2>
class TagRegistry;

template <typename T>
struct IDType;

template <typename T>
class ToFloatFunction;

template <typename T>
class TypedScreenCapabilities
{
};

template <typename T, typename T2, typename T3, typename T4 = class UNK>
class ViewedEntityContextT;

template <typename T>
class FlagComponent;

template <typename T>
class WeightedChoices;

template <typename T>
class buffer_span;

template <typename T>
class buffer_span_mut;

template <typename T>
class optional_ref;

template <int a>
class DividedPos2d;

//template <typename T>
//struct GameplayHandlerResult;

template <typename T>
struct GameplayHandlerResult;

template <int T>
class ItemStackRequestActionDataless;

template <typename T>
class OperationGraphResult;

template <typename T1>
class SmallSet;

template <typename T1>
struct TaskStartInfoEx;

template <typename T1>
class WildcardCommandSelector;

//enum
enum class ContainerType : char
{
    INVENTORY              = -1,
    NONE                   = -9,
    CONTAINER              = 0,
    WORKBENCH              = 1,
    FURNACE                = 2,
    ENCHANTMENT            = 3,
    BREWING_STAND          = 4,
    ANVIL                  = 5,
    DISPENSER              = 6,
    DROPPER                = 7,
    HOPPER                 = 8,
    CAULDRON               = 9,
    MINECART_CHEST         = 10,
    MINECART_HOPPER        = 11,
    HORSE                  = 12,
    TRADE                  = 15,//NotGenerated
    MINECART_COMMAND_BLOCK = 16,
    JUKEBOX                = 17,
    COMPOUND_CREATOR       = 20,
    ELEMENT_CONSTRUCTOR    = 21,
    MATERIAL_REDUCER       = 22,
    LAB_TABLE              = 23,
    BLAST_FURNACE          = 27,
    SMOKER                 = 28,
    STONECUTTER            = 29,
    HUD                    = 31,
    SMITHING_TABLE         = 33,
};

enum class UpdateBlockLayer : int
{
    UpdateBlockDefault,
    UpdateBlockLiquid
};

enum class UpdateBlockFlags : int
{
    UpdateBlockNone = 0,
    BlockUpdateNeighbors = 1,
    BlockUpdateNetwork = 2,
    BlockUpdateAll = 3,//default value in BDS
    BlockUpdateNoGraphic = 4,
    BlockUpdatePriority = 8,
    BlockUpdateAllPriority = 11
    //old one not correctly ? 
    //BlockUpdateNeighbours = 1,
    //BlockUpdateNetwork = 2,
    //BlockUpdateNoGraphics = 3,
    //BlockUpdatePriority = 4,
};

enum class TextType : char
{
    RAW = 0,
    CHAT = 1,
    TRANSLATION = 2,
    POPUP = 3,
    JUKEBOX_POPUP = 4,
    TIP = 5,
    SYSTEM = 6,
    WHISPER = 7,
    ANNOUNCEMENT = 8,
    JSON_WHISPER = 9,
    JSON = 10
};

enum class TitleType : int
{
    Clear = 0,
    Reset = 1,
    SetTitle = 2,
    SetSubtitle = 3,
    SetActionBar = 4,
    SetDurations = 5,
    TitleTextObject = 6,
    SubtitleTextObject = 7,
    ActionbarTextObject = 8
};
enum class BossEvent : int
{
    Show = 0,
    RegisterPlayer = 1,
    Hide = 2,
    UnregisterPlayer = 3,
    HealthPercentage = 4,
    Title = 5,
    AppearanceProperties = 6,
    Texture = 7
};

enum class BossEventColour : int
{
    Grey = 0,
    Blue = 1,
    Red = 2,
    Green = 3,
    Yellow = 4,
    Purple = 5,
    White = 6
};

enum class ContainerEnumName : int8_t
{
    AnvilInputContainer = 0,
    AnvilMaterialContainer = 1,
    AnvilResultPreviewContainer = 2,
    SmithingTableInputContainer = 3,
    SmithingTableMaterialContainer = 4,
    SmithingTableResultPreviewContainer = 5,
    ArmorContainer = 6,
    LevelEntityContainer = 7,
    BeaconPaymentContainer = 8,
    BrewingStandInputContainer = 9,
    BrewingStandResultContainer = 10,
    BrewingStandFuelContainer = 11,
    CombinedHotbarAndInventoryContainer = 12,
    CraftingInputContainer = 13,
    CraftingOutputPreviewContainer = 14,
    RecipeConstructionContainer = 15,
    RecipeNatureContainer = 16,
    RecipeItemsContainer = 17,
    RecipeSearchContainer = 18,
    RecipeSearchBarContainer = 19,
    RecipeEquipmentContainer = 20,
    EnchantingInputContainer = 21,
    EnchantingMaterialContainer = 22,
    FurnaceFuelContainer = 23,
    FurnaceIngredientContainer = 24,
    FurnaceResultContainer = 25,
    HorseEquipContainer = 26,
    HotbarContainer = 27,
    InventoryContainer = 28,
    ShulkerBoxContainer = 29,
    TradeIngredient1Container = 30,
    TradeIngredient2Container = 31,
    TradeResultPreviewContainer = 32,
    OffhandContainer = 33,
    CompoundCreatorInput = 34,
    CompoundCreatorOutputPreview = 35,
    ElementConstructorOutputPreview = 36,
    MaterialReducerInput = 37,
    MaterialReducerOutput = 38,
    LabTableInput = 39,
    LoomInputContainer = 40,
    LoomDyeContainer = 41,
    LoomMaterialContainer = 42,
    LoomResultPreviewContainer = 43,
    BlastFurnaceIngredientContainer = 44,
    SmokerIngredientContainer = 45,
    Trade2Ingredient1Container = 46,
    Trade2Ingredient2Container = 47,
    Trade2ResultPreviewContainer = 48,
    GrindstoneInputContainer = 49,
    GrindstoneAdditionalContainer = 50,
    GrindstoneResultPreviewContainer = 51,
    StonecutterInputContainer = 52,
    StonecutterResultPreviewContainer = 53,
    CartographyInputContainer = 54,
    CartographyAdditionalContainer = 55,
    CartographyResultPreviewContainer = 56,
    BarrelContainer = 57,
    CursorContainer = 58,
    CreatedOutputContainer = 59
};

enum class ParticleType
{
    dragondestroyblock = 0x40,
    none = 0x00,
    bubble = 0x01,
    bubblemanual = 0x02,
    crit = 0x03,
    blockforcefield = 0x04,
    smoke = 0x05,
    explode = 0x06,
    evaporation = 0x07,
    flame = 0x08,
    candleflame = 0x09,
    lava = 0x0a,
    largesmoke = 0x0b,
    reddust = 0x0c,
    risingborderdust = 0x0d,
    iconcrack = 0x0e,
    snowballpoof = 0x0f,
    largeexplode = 0x10,
    hugeexplosion = 0x11,
    mobflame = 0x12,
    heart = 0x13,
    terrain = 0x14,
    townaura = 0x15,
    portal = 0x16,
    watersplash = 0x18,
    watersplashmanual = 0x19,
    waterwake = 0x1a,
    dripwater = 0x1b,
    driplava = 0x1c,
    driphoney = 0x1d,
    stalactitedripwater = 0x1e,
    stalactitedriplava = 0x1f,
    fallingdust = 0x20,
    mobspell = 0x21,
    mobspellambient = 0x22,
    mobspellinstantaneous = 0x23,
    ink = 0x24,
    slime = 0x25,
    rainsplash = 0x26,
    villagerangry = 0x27,
    villagerhappy = 0x28,
    enchantingtable = 0x29,
    trackingemitter = 0x2a,
    note = 0x2b,
    witchspell = 0x2c,
    carrotboost = 0x2d,
    mobappearance = 0x2e,
    endrod = 0x2f,
    dragonbreath = 0x30,
    spit = 0x31,
    totem = 0x32,
    food = 0x33,
    fireworksstarter = 0x34,
    fireworks = 0x35,
    fireworksoverlay = 0x36,
    balloongas = 0x37,
    coloredflame = 0x38,
    sparkler = 0x39,
    conduit = 0x3a,
    bubblecolumnup = 0x3b,
    bubblecolumndown = 0x3c,
    sneeze = 0x3d,
    shulkerbullet = 0x3e,
    bleach = 0x3f,
    myceliumdust = 0x41,
    fallingborderdust = 0x42,
    campfiresmoke = 0x43,
    campfiresmoketall = 0x44,
    dragonbreathfire = 0x45,
    dragonbreathtrail = 0x46,
    soul = 0x48,
    obsidiantear = 0x49,
    portalreverse = 0x4a,
    snowflake = 0x4b,
    wax = 0x50,
    electricspark = 0x51,
    shriek = 0x52,
    sculksoul = 0x53
};

enum class transactionType
{
    NormalTransaction = 0x00,
    InventoryMismatch = 0x01,
    ItemUseTransaction = 0x02,
    ItemUseOnEntityTransaction = 0x03,
    ItemReleaseTransaction = 0x04
};

enum class ItemStackRequestActionType: char
{
    Take = 0x00,
    Place = 0x01,
    Swap = 0x02,
    Drop = 0x03,
    Destroy = 0x04,
    Consume = 0x05,
    Create = 0x06,
    ScreenLabTableCombine = 0x07,
    ScreenBeaconPayment = 0x08,
    ScreenHUDMineBlock = 0x09,
    CraftRecipe = 0x0a,
    CraftRecipeAuto = 0x0b,
    CraftCreative = 0x0c,
    CraftRecipeOptional = 0x0d,
    CraftRepairAndDisenchant = 0x0e,
    CraftLoom = 0x0f,
    CraftNonImplemented_DEPRECATEDASKTYLAING = 0x10,
    CraftResults_DEPRECATEDASKTYLAING = 0x11
};

enum class ActorDamageCause : int
{
    Override = 0x0,
    Contact = 0x1,
    EntityAttack = 0x2,
    Projectile = 0x3,
    Suffocation = 0x4,
    Fall = 0x5,
    Fire = 0x6,
    FireTick = 0x7,
    Lava = 0x8,
    Drowning = 0x9,
    BlockExplosion = 0x0A,
    EntityExplosion = 0x0B,
    Void = 0x0C,
    Suicide = 0x0D,
    Magic = 0x0E,
    Wither = 0x0F,
    Starve = 0x10,
    Anvil = 0x11,
    Thorns = 0x12,
    FallingBlock = 0x13,
    Piston = 0x14,
    FlyIntoWall = 0x15,
    Magma = 0x16,
    Fireworks = 0x17,
    Lightning = 0x18,
    Charging = 0x19,
    Temperature = 0x1A,
    All = 0x1F,
    None = -0x01,
};

enum class ObjectiveSortOrder : char
{
    Ascending = 0,
    Descending = 1
};

enum class PlayerScoreSetFunction : char
{
    Set = 0,
    Add = 1,
    Remove = 2
};

enum class FaceID : char
{
    Unknown = -1,
    Down = 0,
    Up = 1,
    North = 2,
    South = 3,
    West = 4,
    East = 5,
};

enum class MinecraftPacketIds : int
{
    Login = 0x1,
    PlayStatus = 0x2,
    ServerToClientHandshake = 0x3,
    ClientToServerHandshake = 0x4,
    Disconnect = 0x5,
    ResourcePacksInfo = 0x6,
    ResourcePackStack = 0x7,
    ResourcePackClientResponse = 0x8,
    Text = 0x9,
    SetTime = 0xa,
    StartGame = 0xb,
    AddPlayer = 0xc,
    AddActor = 0xd,
    RemoveActor = 0xe,
    AddItemActor = 0xf,
    TakeItemActor = 0x11,
    MoveActorAbsolute = 0x12,
    MovePlayer = 0x13,
    UpdateBlock = 0x15,
    AddPainting = 0x16,
    TickSync = 0x17,
    BlockEvent = 0x1a,
    ActorEvent = 0x1b,
    MobEffect = 0x1c,
    UpdateAttributes = 0x1d,
    InventoryTransaction = 0x1e,
    MobEquipment = 0x1f,
    MobArmorEquipment = 0x20,
    Interact = 0x21,
    BlockPickRequest = 0x22,
    ActorPickRequest = 0x23,
    PlayerAction = 0x24,
    HurtArmor = 0x26,
    SetActorData = 0x27,
    SetActorLink = 0x29,
    SetHealth = 0x2a,
    SetSpawnPosition = 0x2b,
    Animate = 0x2c,
    Respawn = 0x2d,
    ContainerOpen = 0x2e,
    ContainerClose = 0x2f,
    PlayerHotbar = 0x30,
    InventoryContent = 0x31,
    InventorySlot = 0x32,
    ContainerSetData = 0x33,
    CraftingData = 0x34,
    CraftingEvent = 0x35,
    GuiDataPickItem = 0x36,
    AdventureSettings = 0x37,
    BlockActorData = 0x38,
    PlayerInput = 0x39,
    LevelChunk = 0x3a,
    SetCommandsEnabled = 0x3b,
    SetDifficulty = 0x3c,
    ChangeDimension = 0x3d,
    SetPlayerGameType = 0x3e,
    PlayerList = 0x3f,
    Event = 0x41,
    SpawnExperienceOrb = 0x42,
    ClientboundMapItemData = 0x43,
    MapInfoRequest = 0x44,
    ItemFrameDropItem = 0x47,
    GameRulesChanged = 0x48,
    Camera = 0x49,
    BossEvent = 0x4a,
    ShowCredits = 0x4b,
    AvailableCommands = 0x4c,
    CommandRequest = 0x4d,
    CommandBlockUpdate = 0x4e,
    CommandOutput = 0x4f,
    UpdateTrade = 0x50,
    UpdateEquip = 0x51,
    ResourcePackDataInfo = 0x52,
    ResourcePackChunkData = 0x53,
    ResourcePackChunkRequest = 0x54,
    Transfer = 0x55,
    PlaySound = 0x56,
    StopSound = 0x57,
    SetTitle = 0x58,
    AddBehaviorTree = 0x59,
    StructureBlockUpdate = 0x5a,
    ShowStoreOffer = 0x5b,
    PurchaseReceipt = 0x5c,
    PlayerSkin = 0x5d,
    SubClientLogin = 0x5e,
    AutomationClientConnect = 0x5f,
    SetLastHurtBy = 0x60,
    BookEdit = 0x61,
    NpcRequest = 0x62,
    PhotoTransfer = 0x63,
    ModalFormRequest = 0x64,
    ModalFormResponse = 0x65,
    ServerSettingsRequest = 0x66,
    ServerSettingsResponse = 0x67,
    ShowProfile = 0x68,
    SetDefaultGameType = 0x69,
    RemoveObjective = 0x6a,
    SetDisplayObjective = 0x6b,
    SetScore = 0x6c,
    LabTable = 0x6d,
    UpdateBlockSynced = 0x6e,
    MoveActorDelta = 0x6f,
    SetScoreboardIdentity = 0x70,
    SetLocalPlayerAsInitialized = 0x71,
    UpdateSoftEnum = 0x72,
    NetworkStackLatency = 0x73,
    ScriptCustomEvent = 0x75,
    SpawnParticleEffect = 0x76,
    AvailableActorIdentifiers = 0x77,
    NetworkChunkPublisherUpdate = 0x79,
    BiomeDefinitionList = 0x7a,
    LevelSoundEvent = 0x7b,
    LevelEventGeneric = 0x7c,
    LecternUpdate = 0x7d,
    AddEntity = 0x7f,
    ClientCacheStatus = 0x81,
    OnScreenTextureAnimation = 0x82,
    MapCreateLockedCopy = 0x83,
    StructureTemplateDataRequest = 0x84,
    StructureTemplateDataResponse = 0x85,
    ClientCacheBlobStatus = 0x87,
    ClientCacheMissResponse = 0x88,
    EducationSettings = 0x89,
    Emote = 0x8a,
    MultiplayerSettings = 0x8b,
    SettingsCommand = 0x8c,
    AnvilDamage = 0x8d,
    CompletedUsingItem = 0x8e,
    NetworkSettings = 0x8f,
    PlayerAuthInput = 0x90,
    CreativeContent = 0x91,
    PlayerEnchantOptions = 0x92,
    ItemStackRequest = 0x93,
    ItemStackResponse = 0x94,
    PlayerArmorDamage = 0x95,
    CodeBuilder = 0x96,
    UpdatePlayerGameType = 0x97,
    EmoteList = 0x98,
    PositionTrackingDBServerBroadcast = 0x99,
    PositionTrackingDBClientRequest = 0x9a,
    DebugInfo = 0x9b,
    PacketViolationWarning = 0x9c,
    MotionPredictionHints = 0x9d,
    AnimateEntity = 0x9e,
    CameraShake = 0x9f,
    PlayerFog = 0xa0,
    CorrectPlayerMovePrediction = 0xa1,
    ItemComponent = 0xa2,
    FilterText = 0xa3,
    ClientboundDebugRenderer = 0xa4,
    SyncActorProperty = 0xa5,
    AddVolumeEntity = 0xa6,
    RemoveVolumeEntity = 0xa7,
    SimulationType = 0xa8,
    NPCDialogue = 0xa9,
    EduUriResource = 0xaa,
    CreatePhoto = 0xab,
    UpdateSubChunkBlocks = 0xac,
    PhotoInfoRequest = 0xad,
    SubChunk = 0xae,
    SubChunkRequest = 0xaf
};

enum ItemStackNetResult :unsigned char {
    Success                                          = 0,
    Error                                            = 1,
    InvalidRequestActionType                         = 2,
    ActionRequestNotAllowed                          = 3,
    ScreenHandlerEndRequestFailed                    = 4,
    ItemRequestActionHandlerCommitFailed             = 5,
    InvalidRequestCraftActionType                    = 6,
    InvalidCraftRequest                              = 7,
    InvalidCraftRequestScreen                        = 8,
    InvalidCraftResult                               = 9,
    InvalidCraftResultIndex                          = 10,
    InvalidCraftResultItem                           = 11,
    InvalidItemNetId                                 = 12,
    MissingCreatedOutputContainer                    = 13,
    FailedToSetCreatedItemOutputSlot                 = 14,
    RequestAlreadyInProgress                         = 15,
    FailedToInitSparseContainer                      = 16,
    ResultTransferFailed                             = 17,
    ExpectedItemSlotNotFullyConsumed                 = 18,
    ExpectedAnywhereItemNotFullyConsumed             = 19,
    ItemAlreadyConsumedFromSlot                      = 20,
    ConsumedTooMuchFromSlot                          = 21,
    MismatchSlotExpectedConsumedItem                 = 22,
    MismatchSlotExpectedConsumedItemNetIdVariant     = 23,
    FailedToMatchExpectedSlotConsumedItem            = 24,
    FailedToMatchExpectedAllowedAnywhereConsumedItem = 25,
    ConsumedItemOutOfAllowedSlotRange                = 26,
    ConsumedItemNotAllowed                           = 27,
    PlayerNotInCreativeMode                          = 28,
    InvalidExperimentalRecipeRequest                 = 29,
    FailedToCraftCreative                            = 30,
    FailedToGetLevelRecipe                           = 31,
    FailedToFindRecipeByNetId                        = 32,
    MismatchedCraftingSize                           = 33,
    MissingInputSparseContainer                      = 34,
    MismatchedRecipeForInputGridItems                = 35,
    EmptyCraftResults                                = 36,
    FailedToEnchant                                  = 37,
    MissingInputItem                                 = 38,
    InsufficientPlayerLevelToEnchant                 = 39,
    MissingMaterialItem                              = 40,
    MissingActor                                     = 41,
    UnknownPrimaryEffect                             = 42,
    PrimaryEffectOutOfRange                          = 43,
    PrimaryEffectUnavailable                         = 44,
    SecondaryEffectOutOfRange                        = 45,
    SecondaryEffectUnavailable                       = 46,
    DstContainerEqualToCreatedOutputContainer        = 47,
    DstContainerAndSlotEqualToSrcContainerAndSlot    = 48,
    FailedToValidateSrcSlot                          = 49,
    FailedToValidateDstSlot                          = 50,
    InvalidAdjustedAmount                            = 51,
    InvalidItemSetType                               = 52,
    InvalidTransferAmount                            = 53,
    CannotSwapItem                                   = 54,
    CannotPlaceItem                                  = 55,
    UnhandledItemSetType                             = 56,
    InvalidRemovedAmount                             = 57,
    InvalidRegion                                    = 58,
    CannotDropItem                                   = 59,
    CannotDestroyItem                                = 60,
    InvalidSourceContainer                           = 61,
    ItemNotConsumed                                  = 62,
    InvalidNumCrafts                                 = 63,
    InvalidCraftResultStackSize                      = 64,
    CannotConsumeItem                                = 66,
    ScreenStackError                                 = 67,
};

//class CommandVersion {
//public:
//    int Min = 1, Max = 0x7FFFFFFF;
//};

template <typename T>
struct InvertableFilter
{
    T value;
    bool inverted;
};

class CommandOutputParameter
{
    std::string str;
    int type;

public:
    MCINLINE CommandOutputParameter(std::string str, int type)
        : str(std::move(str))
        , type(type)
    {
    }
};

template <typename T>
class CommandSelectorResults
{
public:
    std::shared_ptr<std::vector<T*>> data;

    auto begin()
    {
        return data->begin();
    }

    auto end()
    {
        return data->end();
    }

    auto count() const
    {
        return data->size();
    }

    auto empty() const
    {
        return data->empty();
    }
};
