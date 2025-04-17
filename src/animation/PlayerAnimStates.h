#pragma once
#include "IgnoreUnknownEvent.h"
#include <variant>
#include "Events.h"





struct IdleState {};
struct RunningState {};


using PlayerAnimVar = std::variant<IdleState, RunningState>;
//using AnimVariant = PlayerAnimVar;
