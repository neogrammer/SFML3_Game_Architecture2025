#pragma once
#include <variant>
#include "FSMEvent.h"
struct EventMoved : FSMEvent { EventMoved() : FSMEvent() { setName("Moved"); } };
struct EventStoppedMoving : FSMEvent { EventStoppedMoving() : FSMEvent() { setName("StoppedMoving"); } };
struct EventStartedShootSetup : FSMEvent { EventStartedShootSetup() : FSMEvent() { setName("StartedShootSetup"); } };
struct EventStoppedShooting : FSMEvent { EventStoppedShooting() : FSMEvent() { setName("StoppedShooting"); } };
struct EventShooting : FSMEvent { EventShooting() : FSMEvent() { setName("Shooting"); } };



using PlayerEventVar = std::variant<EventMoved, EventStoppedMoving, EventStartedShootSetup, EventStoppedShooting, EventShooting>;
