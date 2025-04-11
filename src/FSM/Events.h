#pragma once
#include <variant>
#include <FSM/FSMEvent.h>
struct EventStartedShooting : FSMEvent { EventStartedShooting() : FSMEvent() { setName("StartedShooting"); } };
struct EventStartedMoving : FSMEvent { EventStartedMoving() : FSMEvent() { setName("StartedMoving"); } };
struct EventStoppedMoving : FSMEvent { EventStoppedMoving() : FSMEvent() { setName("StoppedMoving"); } };
struct EventFell : FSMEvent { EventFell() : FSMEvent() { setName("Fell"); } };
struct EventHit : FSMEvent { EventHit() : FSMEvent() { setName("Hit"); } };
struct EventJumpStartFinished : FSMEvent { EventJumpStartFinished() : FSMEvent() { setName("JumpStartFinished"); } };
struct EventLanding2 : FSMEvent { EventLanding2() : FSMEvent() { setName("Landing2"); } };

struct EventMoveStartFinished : FSMEvent { EventMoveStartFinished() : FSMEvent() { setName("MoveStartFinished"); } };

struct EventRecovered : FSMEvent { EventRecovered() : FSMEvent() { setName("Recovered"); } };
struct EventLifeDepleted : FSMEvent { EventLifeDepleted() : FSMEvent() { setName("LifeDepleted"); } };
struct EventNearingTopOfJump : FSMEvent { EventNearingTopOfJump() : FSMEvent() { setName("NearingTopOfJump"); } };
struct EventStoppedShooting : FSMEvent { EventStoppedShooting() : FSMEvent() { setName("StoppedShooting"); } };
struct EventStartedJumping : FSMEvent { EventStartedJumping() : FSMEvent() { setName("StartedJump"); } };
struct EventLanding : FSMEvent { bool moving{ false };  EventLanding(bool moving_) : FSMEvent(), moving{ moving_ } { setName("Landing"); } };
struct EventShootSetupDone : FSMEvent { EventShootSetupDone() : FSMEvent{} { setName("ShootSetupDone"); } };
struct EventReachedJumpHeight : FSMEvent { EventReachedJumpHeight() : FSMEvent() { setName("ReachedJumpHeight"); } };
struct EventDetectedTarget : FSMEvent { EventDetectedTarget() : FSMEvent() { setName("DetectedTarget"); } };


using PlayerEventVar = std::variant<EventStartedShooting, EventMoveStartFinished, EventDetectedTarget, EventStartedMoving , EventStoppedMoving, EventFell, EventHit, EventJumpStartFinished, EventLanding2, EventRecovered, EventLifeDepleted, EventNearingTopOfJump, EventStoppedShooting, EventStartedJumping, EventLanding, EventShootSetupDone, EventReachedJumpHeight >;