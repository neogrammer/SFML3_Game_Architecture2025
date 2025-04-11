#pragma once
#include <FSM/IgnoreUnknownEvent.h>
#include <variant>
#include <FSM/Events.h>





struct IdleState {};
struct HitState {};
struct DeadState {};
struct MovingState {};
struct AtJumpTopState {};
struct AtJumpTopStateAndShooting {};
struct StartedJumpState {};
struct StartedJumpAndShootingState {};
struct RisingState {};
struct RisingAndShootingState {};
struct AtJumpTopAndShootingState {};
struct FallingState {};
struct FallingAndShootingState {};;
struct LandingState {};
struct LandingAndShootingState {};
struct ShootingState {};
struct StartedShootingState {};
struct StartedMovingState{};
struct StartedMovingAndShootingState {};
struct MovingAndShootingState {};
struct JumpingAndShootingState {};
struct WarningState {};
struct GuardingState {};



using PlayerAnimVar = std::variant<IdleState, StartedMovingState, JumpingAndShootingState, WarningState, GuardingState, StartedMovingAndShootingState,  ShootingState,  HitState, DeadState, MovingState, StartedJumpState, RisingState, FallingState, LandingState, MovingAndShootingState, StartedJumpAndShootingState, RisingAndShootingState, AtJumpTopAndShootingState, AtJumpTopState, FallingAndShootingState, LandingAndShootingState, StartedShootingState>;
using AnimVariant = PlayerAnimVar;
