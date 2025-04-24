#pragma once
#include "IgnoreUnknownEvent.h"
#include <variant>
#include "Events.h"





struct IdleState {};
struct RunningState {};
struct ShootSetupState {};
struct ShootingState {};


using PlayerAnimVar = std::variant<IdleState, RunningState, ShootSetupState, ShootingState>;
//using AnimVariant = PlayerAnimVar;
