// This Header is auto generated by BDSLiteLoader Toolchain
#pragma once
#include <Global.h>
#include "Scripting.hpp"
#define EXTRA_INCLUDE_PART_SCRIPTWEATHERCHANGEDEVENT
#include "Extra/ScriptWeatherChangedEventAPI.hpp"
#undef EXTRA_INCLUDE_PART_SCRIPTWEATHERCHANGEDEVENT
struct ScriptWeatherChangedEvent {
#include "Extra/ScriptWeatherChangedEventAPI.hpp"

public:
    MCAPI static class Scripting::ClassBindingBuilder<struct ScriptWeatherChangedEvent> bind(struct Scripting::Version);
};