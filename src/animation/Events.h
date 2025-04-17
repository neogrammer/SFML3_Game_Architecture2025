#pragma once
#include <variant>
#include "FSMEvent.h"
struct EventMoved : FSMEvent { EventMoved() : FSMEvent() { setName("Moved"); } };
struct EventStoppedMoving : FSMEvent { EventStoppedMoving() : FSMEvent() { setName("StoppedMoving"); } };




using PlayerEventVar = std::variant<EventMoved, EventStoppedMoving>;
