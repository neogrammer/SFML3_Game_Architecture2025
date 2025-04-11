#ifndef GREENGUYANIMFSM_H__
#define GREENGUYANIMFSM_H__
#include <FSM/DuckFold.h>
#include <optional>
#include <FSM/PlayerAnimStates.h>
#include <type_traits>
#include <variant>
#include <iostream>

class FSM_GreenGuy : public FSM<FSM_GreenGuy, AnimVariant>
{
public:
	
	std::optional<AnimVariant> On_Event(GuardingState& s, const EventHit& e) { std::cout << "Hit" << std::endl; return HitState{}; }
	std::optional<AnimVariant> On_Event(GuardingState& s, const EventLifeDepleted& e) { std::cout << "Dead" << std::endl; return DeadState{}; }
	std::optional<AnimVariant> On_Event(GuardingState& s, const EventDetectedTarget& e) { std::cout << "Warning" << std::endl; return WarningState{}; }
	std::optional<AnimVariant> On_Event(GuardingState& s, const EventStartedShooting& e) { std::cout << "StartedShooting" << std::endl; return StartedShootingState{}; }

	std::optional<AnimVariant> On_Event(IdleState& s, const EventHit& e) { std::cout << "Hit" << std::endl; return HitState{}; }
	std::optional<AnimVariant> On_Event(IdleState& s, const EventLifeDepleted& e) { std::cout << "Dead" << std::endl; return DeadState{}; }
	std::optional<AnimVariant> On_Event(IdleState& s, const EventDetectedTarget& e) { std::cout << "Warning" << std::endl; return WarningState{}; }
	std::optional<AnimVariant> On_Event(IdleState& s, const EventStartedShooting& e) { std::cout << "StartedShooting" << std::endl; return StartedShootingState{}; }



	std::optional<AnimVariant> On_Event(HitState& s, const EventRecovered& e) { std::cout << "Falling" << std::endl; return GuardingState{}; }
	std::optional<AnimVariant> On_Event(HitState& s, const EventLifeDepleted& e) { std::cout << "Dead" << std::endl; return DeadState{}; }

	std::optional<AnimVariant> On_Event(ShootingState& s, const EventHit& e) { std::cout << "Hit" << std::endl; return HitState{}; }
	std::optional<AnimVariant> On_Event(ShootingState& s, const EventLifeDepleted& e) { std::cout << "Dead" << std::endl; return DeadState{}; }
	std::optional<AnimVariant> On_Event(ShootingState& s, const EventStoppedShooting& e) { std::cout << "Guarding" << std::endl; return GuardingState{}; }

	std::optional<AnimVariant> On_Event(StartedShootingState& s, const EventHit& e) { std::cout << "Hit" << std::endl; return HitState{}; }
	std::optional<AnimVariant> On_Event(StartedShootingState& s, const EventLifeDepleted& e) { std::cout << "Dead" << std::endl; return DeadState{}; }
	std::optional<AnimVariant> On_Event(StartedShootingState& s, const EventStartedShooting& e) { std::cout << "Shooting" << std::endl; return ShootingState{}; }


	std::optional<AnimVariant> On_Event(RisingState& s, const EventNearingTopOfJump& e) { std::cout << "AtJumpTop" << std::endl; return AtJumpTopState{}; }
	std::optional<AnimVariant> On_Event(RisingState& s, const EventHit& e) { std::cout << "Hit" << std::endl; return HitState{}; }
	std::optional<AnimVariant> On_Event(RisingState& s, const EventLifeDepleted& e) { std::cout << "Dead" << std::endl; return DeadState{}; }


	std::optional<AnimVariant> On_Event(AtJumpTopState& s, const EventReachedJumpHeight& e) { std::cout << "Falling" << std::endl; return FallingState{}; }
	std::optional<AnimVariant> On_Event(AtJumpTopState& s, const EventHit& e) { std::cout << "Hit" << std::endl; return HitState{}; }
	std::optional<AnimVariant> On_Event(AtJumpTopState& s, const EventLifeDepleted& e) { std::cout << "Dead" << std::endl; return DeadState{}; }

	std::optional<AnimVariant> On_Event(FallingState &s, const EventLanding& e) { std::cout << "Guarding" << std::endl; return GuardingState{}; }
	std::optional<AnimVariant> On_Event(FallingState& s, const EventHit& e) { std::cout << "Hit" << std::endl; return HitState{}; }
	std::optional<AnimVariant> On_Event(FallingState& s, const EventLifeDepleted& e) { std::cout << "Dead" << std::endl; return DeadState{}; }


	std::optional<AnimVariant> On_Event(WarningState& s, const EventStartedShooting& e) { std::cout << "Shooting" << std::endl; return ShootingState{}; }
	std::optional<AnimVariant> On_Event(WarningState& s, const EventHit& e) { std::cout << "Hit" << std::endl; return HitState{}; }
	std::optional<AnimVariant> On_Event(WarningState& s, const EventLifeDepleted& e) { std::cout << "Dead" << std::endl; return DeadState{}; }


	/*std::optional<AnimVariant> On_Event(InAirState& s, const EventLanded& e)
	{
		if (e.isMoving)
			return RunningState{};
		else
			return IdleState{};
	}*/
	template <typename State, typename Event>
	std::optional<AnimVariant> On_Event(State&, const Event&) { return std::nullopt; }
	std::string getStateName()
	{
		if (std::holds_alternative<IdleState>(state_)) { return "Idle"; }
		else if (std::holds_alternative<HitState>(state_)) { return "Hit"; }
		else if (std::holds_alternative<DeadState>(state_)) { return "Dead"; }
		else if (std::holds_alternative<ShootingState>(state_)) { return "Shooting"; }
		else if (std::holds_alternative<MovingState>(state_)) { return "Moving"; }
		else if (std::holds_alternative<StartedJumpState>(state_)) { return "StartedJump"; }
		else if (std::holds_alternative<RisingState>(state_)) { return "Rising"; }
		else if (std::holds_alternative<RisingAndShootingState>(state_)) { return "RisingAndShooting"; }
		else if (std::holds_alternative<AtJumpTopState>(state_)) { return "AtJumpTop"; }
		else if (std::holds_alternative<FallingState>(state_)) { return "Falling"; }
		else if (std::holds_alternative<LandingState>(state_)) { return "Landing"; }
		else if (std::holds_alternative<MovingAndShootingState>(state_)) { return "MovingAndShooting"; }
		else if (std::holds_alternative<StartedJumpAndShootingState>(state_)) { return "StartedJumpAndShooting"; }
		else if (std::holds_alternative<RisingAndShootingState>(state_)) { return "RisingAndShooting"; }
		else if (std::holds_alternative<AtJumpTopAndShootingState>(state_)) { return "AtJumpTopAndShooting"; }
		else if (std::holds_alternative<AtJumpTopState>(state_)) { return "AtJumpTop"; }
		else if (std::holds_alternative<FallingAndShootingState>(state_)) { return "FallingAndShooting"; }
		else if (std::holds_alternative<LandingAndShootingState>(state_)) { return "LandingAndShooting"; }
		else if (std::holds_alternative <StartedShootingState >(state_)) { return "StartedShooting"; }
		else if (std::holds_alternative <StartedMovingState>(state_)) { return "StartedMoving"; }
		else if (std::holds_alternative <StartedMovingAndShootingState >(state_)) { return "StartedMovingAndShooting"; }
		else if (std::holds_alternative <WarningState >(state_)) { return "Warning"; }
		else if (std::holds_alternative <GuardingState >(state_)) { return "Guarding"; }
		else { return "None"; }
	}
};
#endif