#pragma once
#include "IgnoreUnknownEvent.h"
#include <variant>
#include "Events.h"





struct IdleState {};
struct RunningState {};
struct IdleToRunState {};
struct ShootSetupState {};
struct ShootingState {};
struct LiftOffState {};
struct RisingState {};
struct JumpPeakRisingState {};
struct JumpPeakFallingState {};
struct FallingState {};
struct LandingState {};
struct LiftOffAndShootingState {};
struct RisingAndShootingState {};
struct JumpPeakRisingAndShootingState {};
struct JumpPeakFallingAndShootingState {};
struct FallingAndShootingState {};
struct LandingAndShootingState {};
struct IdleToRunAndShootingState {};
struct RunningAndShootingState {};



using PlayerAnimVar = std::variant<IdleState, RunningState, ShootSetupState, ShootingState, IdleToRunState, LiftOffState
, RisingState, JumpPeakRisingState, JumpPeakFallingState, FallingState, LandingState, LiftOffAndShootingState
, RisingAndShootingState, JumpPeakRisingAndShootingState, JumpPeakFallingAndShootingState, FallingAndShootingState
, LandingAndShootingState, IdleToRunAndShootingState , RunningAndShootingState>;
//using AnimVariant = PlayerAnimVar;
