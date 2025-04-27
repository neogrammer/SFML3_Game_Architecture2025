#pragma once
#include <variant>
#include "FSMEvent.h"
struct EventMoved : FSMEvent { EventMoved() : FSMEvent() { setName("Moved"); } };
struct EventStoppedMoving : FSMEvent { EventStoppedMoving() : FSMEvent() { setName("StoppedMoving"); } };
struct EventStoppedShooting : FSMEvent {EventStoppedShooting() : FSMEvent() { setName("StoppedShooting"); } };
struct EventShootSetupTimedOut : FSMEvent { EventShootSetupTimedOut() : FSMEvent() { setName("ShootSetupTimedOut"); } };
struct EventShoot : FSMEvent { EventShoot() : FSMEvent() { setName("Shoot"); } };
struct EventJumped : FSMEvent { EventJumped() : FSMEvent() { setName("Jumped"); } };
struct EventIdleToRunTimedOut : FSMEvent { EventIdleToRunTimedOut() : FSMEvent() { setName("IdleToRunTimedOut"); } };
struct EventFell : FSMEvent { EventFell() : FSMEvent() { setName("Fell"); } };
struct EventJumpReleased : FSMEvent { EventJumpReleased() : FSMEvent() { setName("JumpReleased"); } };
struct EventLiftOffTimedOut : FSMEvent { EventLiftOffTimedOut() : FSMEvent() { setName("LiftOffTimedOut"); } };
struct EventEnteredJumpPeak : FSMEvent { EventEnteredJumpPeak() : FSMEvent() { setName("EnteredJumpPeak"); } };
struct EventReachedJumpMax : FSMEvent { EventReachedJumpMax() : FSMEvent() { setName("ReachedJumpMax"); } };
struct EventExitingJumpPeak : FSMEvent { EventExitingJumpPeak() : FSMEvent() { setName("ExitingJumpPeak"); } };
struct EventLanded : FSMEvent { EventLanded() : FSMEvent() { setName("Landed"); } };
struct EventFullyLanded : FSMEvent { EventFullyLanded() : FSMEvent() { setName("FullyLanded"); } };



using PlayerEventVar = std::variant<EventMoved, EventStoppedMoving, EventLanded, EventFullyLanded, EventReachedJumpMax, EventExitingJumpPeak,  EventLiftOffTimedOut, EventEnteredJumpPeak,   EventJumpReleased, EventJumped,  EventStoppedShooting, EventShoot, EventFell, EventIdleToRunTimedOut, EventShootSetupTimedOut >;
