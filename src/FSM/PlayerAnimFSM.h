#ifndef PLAYERANIMFSM_H__
#define PLAYERANIMFSM_H__
#include <FSM/DuckFold.h>
#include <optional>
#include <FSM/PlayerAnimStates.h>
#include <type_traits>
#include <variant>
#include <iostream>

class FSM_Player : public FSM<FSM_Player, PlayerAnimVar>
{
public:

	std::optional<PlayerAnimVar> On_Event(IdleState& s, const EventStartedMoving& e) { std::cout << "StartedMoving" << std::endl; return StartedMovingState{}; }
	std::optional<PlayerAnimVar> On_Event(IdleState& s, const EventStartedShooting& e) { std::cout << "StartedShooting" << std::endl; return StartedShootingState{}; }
	std::optional<PlayerAnimVar> On_Event(IdleState& s, const EventStartedJumping& e) { std::cout << "StartedJump" << std::endl; return StartedJumpState{}; }
	std::optional<PlayerAnimVar> On_Event(IdleState& s, const EventFell& e) { std::cout << "Falling" << std::endl; return FallingState{}; }
	std::optional<PlayerAnimVar> On_Event(IdleState& s, const EventHit& e) { std::cout << "Hit" << std::endl; return HitState{}; }

	std::optional<PlayerAnimVar> On_Event(HitState& s, const EventRecovered& e) { std::cout << "Idle" << std::endl; return IdleState{}; }
	std::optional<PlayerAnimVar> On_Event(HitState& s, const EventLifeDepleted& e) { std::cout << "Dead" << std::endl; return DeadState{}; }

	std::optional<PlayerAnimVar> On_Event(ShootingState& s, const EventStoppedShooting& e) { std::cout << "Idle" << std::endl; return IdleState{}; }
	std::optional<PlayerAnimVar> On_Event(ShootingState& s, const EventStartedMoving& e) { std::cout << "MovingAndShooting" << std::endl; return MovingAndShootingState{}; }
	std::optional<PlayerAnimVar> On_Event(ShootingState& s, const EventStartedJumping& e) { std::cout << "RisingAndShooting" << std::endl; return StartedJumpAndShootingState{}; }
	std::optional<PlayerAnimVar> On_Event(ShootingState& s, const EventHit& e) { std::cout << "Hit" << std::endl; return HitState{}; }
	std::optional<PlayerAnimVar> On_Event(ShootingState& s, const EventFell& e) { std::cout << "Falling" << std::endl; return FallingState{}; }


	std::optional<PlayerAnimVar> On_Event(MovingState& s, const EventStoppedMoving& e) { std::cout << "Idle" << std::endl; return IdleState{}; }
	std::optional<PlayerAnimVar> On_Event(MovingState& s, const EventStartedShooting& e) { std::cout << "MovingAndShooting" << std::endl; return MovingAndShootingState{}; }
	std::optional<PlayerAnimVar> On_Event(MovingState& s, const EventStartedJumping& e) { std::cout << "StartedJump" << std::endl; return StartedJumpState{}; }
	std::optional<PlayerAnimVar> On_Event(MovingState& s, const EventFell& e) { std::cout << "Falling" << std::endl; return FallingState{}; }
	

	std::optional<PlayerAnimVar> On_Event(StartedJumpState& s, const EventStartedShooting& e) { std::cout << "StartedJumpAndShooting" << std::endl; return StartedJumpAndShootingState{}; }
	std::optional<PlayerAnimVar> On_Event(StartedJumpState& s, const EventHit& e) { std::cout << "Hit" << std::endl; return HitState{}; }
	std::optional<PlayerAnimVar> On_Event(StartedJumpState& s, const EventJumpStartFinished& e) { std::cout << "Rising" << std::endl; return RisingState{}; }

	

	std::optional<PlayerAnimVar> On_Event(RisingState& s, const EventStartedShooting& e) { std::cout << "RisingAndStartedShooting" << std::endl; return RisingAndShootingState{}; }
	std::optional<PlayerAnimVar> On_Event(RisingState& s, const EventNearingTopOfJump& e) { std::cout << "AtJumpTop" << std::endl; return AtJumpTopState{}; }
	std::optional<PlayerAnimVar> On_Event(RisingState& s, const EventHit& e) { std::cout << "Hit" << std::endl; return HitState{}; }

	std::optional<PlayerAnimVar> On_Event(RisingAndShootingState& s, const EventStoppedShooting& e) { std::cout << "Rising" << std::endl; return RisingState{}; }
	std::optional<PlayerAnimVar> On_Event(RisingAndShootingState& s, const EventNearingTopOfJump& e) { std::cout << "AtJumpTopAndShooting" << std::endl; return AtJumpTopAndShootingState{}; }
	std::optional<PlayerAnimVar> On_Event(RisingAndShootingState& s, const EventHit& e) { std::cout << "Hit" << std::endl; return HitState{}; }

	std::optional<PlayerAnimVar> On_Event(AtJumpTopState& s, const EventFell& e) { std::cout << "Falling" << std::endl; return FallingState{}; }
	std::optional<PlayerAnimVar> On_Event(AtJumpTopState& s, const EventReachedJumpHeight& e) { std::cout << "Falling" << std::endl; return FallingState{}; }
	std::optional<PlayerAnimVar> On_Event(AtJumpTopState& s, const EventHit& e) { std::cout << "Hit" << std::endl; return HitState{}; }
	std::optional<PlayerAnimVar> On_Event(AtJumpTopState& s, const EventStartedShooting& e) { std::cout << "AtJumpTopAndShooting" << std::endl; return AtJumpTopAndShootingState{}; }


	
	std::optional<PlayerAnimVar> On_Event(FallingState& s, const EventStartedShooting& e) { std::cout << "FallingAndStartedShooting" << std::endl; return FallingAndShootingState{}; }
	std::optional<PlayerAnimVar> On_Event(FallingState & s, const EventLanding & e) { std::cout << "Landing" << std::endl; return LandingState{}; }
	std::optional<PlayerAnimVar> On_Event(FallingState& s, const EventHit& e) { std::cout << "Hit" << std::endl; return HitState{}; }
	std::optional<PlayerAnimVar> On_Event(FallingState& s, const EventLifeDepleted& e) { std::cout << "Dead" << std::endl; return DeadState{}; }

	
	std::optional<PlayerAnimVar> On_Event(LandingState& s, const EventStartedShooting& e) { std::cout << "LandingAndStartedShooting" << std::endl; return LandingAndShootingState{}; } 
	std::optional<PlayerAnimVar> On_Event(LandingState& s, const EventLanding2& e) { std::cout << "Idle" << std::endl;  return IdleState{}; } 
	std::optional<PlayerAnimVar> On_Event(LandingState& s, const EventHit& e) { std::cout << "Hit" << std::endl; return HitState{}; }
	std::optional<PlayerAnimVar> On_Event(LandingState& s, const EventFell &e) { std::cout << "Falling" << std::endl; return FallingState{}; }

	std::optional<PlayerAnimVar> On_Event(MovingAndShootingState& s, const EventStartedJumping& e) { std::cout << "RisingAndShooting" << std::endl;  return RisingAndShootingState{};  }
	std::optional<PlayerAnimVar> On_Event(MovingAndShootingState& s, const EventFell& e) { std::cout << "FallingAndShooting" << std::endl;  return FallingAndShootingState{}; }
	std::optional<PlayerAnimVar> On_Event(MovingAndShootingState& s, const EventHit& e) { std::cout << "Hit" << std::endl;  return HitState{}; }
	std::optional<PlayerAnimVar> On_Event(MovingAndShootingState& s, const EventStoppedShooting& e) { std::cout << "Moving" << std::endl;  return MovingState{}; }
	std::optional<PlayerAnimVar> On_Event(MovingAndShootingState& s, const EventStoppedMoving& e) { std::cout << "Shooting" << std::endl;  return ShootingState{}; }

	std::optional<PlayerAnimVar> On_Event(StartedJumpAndShootingState& s, const EventStoppedShooting& e) { std::cout << "StartedJump" << std::endl;  return RisingState{}; }
	std::optional<PlayerAnimVar> On_Event(StartedJumpAndShootingState& s, const EventJumpStartFinished& e) { std::cout << "RisingAndShooting" << std::endl;  return RisingAndShootingState{}; }
	std::optional<PlayerAnimVar> On_Event(StartedJumpAndShootingState& s, const EventHit& e) { std::cout << "Hit" << std::endl;  return HitState{}; }


	std::optional<PlayerAnimVar> On_Event(AtJumpTopAndShootingState& s, const EventStoppedShooting& e) { std::cout << " AtJumpTop" << std::endl; return AtJumpTopState{}; }
	std::optional<PlayerAnimVar> On_Event(AtJumpTopAndShootingState& s, const EventReachedJumpHeight& e) { std::cout << "FallingAndShooting" << std::endl; return FallingAndShootingState{}; }
	std::optional<PlayerAnimVar> On_Event(AtJumpTopAndShootingState& s, const EventHit& e) { std::cout << "Hit" << std::endl; return HitState{}; }


	std::optional<PlayerAnimVar> On_Event(FallingAndShootingState& s, const EventStoppedShooting& e) { std::cout << "Falling" << std::endl; return FallingState{}; }
	std::optional<PlayerAnimVar> On_Event(FallingAndShootingState& s, const EventLanding& e) { std::cout << "LandingAndShooting" << std::endl; return LandingAndShootingState{}; }
	std::optional<PlayerAnimVar> On_Event(FallingAndShootingState& s, const EventHit& e) { std::cout << "Hit" << std::endl; return HitState{}; }
	std::optional<PlayerAnimVar> On_Event(FallingAndShootingState& s, const EventLifeDepleted& e) { std::cout << "Dead" << std::endl; return DeadState{}; }

	std::optional<PlayerAnimVar> On_Event(LandingAndShootingState& s, const EventStoppedShooting& e) { std::cout << "Landing" << std::endl; return LandingState{}; }
	std::optional<PlayerAnimVar> On_Event(LandingAndShootingState& s, const EventLanding2& e) { std::cout << "Shooting" << std::endl; return ShootingState{}; }
	std::optional<PlayerAnimVar> On_Event(LandingAndShootingState& s, const EventHit& e) { std::cout << "Hit" << std::endl; return HitState{}; }
	std::optional<PlayerAnimVar> On_Event(LandingAndShootingState& s, const EventFell& e) { std::cout << "FallingAndShooting" << std::endl; return FallingAndShootingState{}; }


	std::optional<PlayerAnimVar> On_Event(StartedShootingState& s, const EventShootSetupDone& e) { std::cout << "Shooting" << std::endl;  return ShootingState{}; }
	std::optional<PlayerAnimVar> On_Event(StartedShootingState& s, const EventHit& e) { std::cout << "Hit" << std::endl;  return HitState{}; }
	std::optional<PlayerAnimVar> On_Event(StartedShootingState& s, const EventFell& e) { std::cout << "FallingAndShooting" << std::endl;  return FallingAndShootingState{}; }
	std::optional<PlayerAnimVar> On_Event(StartedShootingState& s, const EventStoppedShooting& e) { std::cout << "Idle" << std::endl;  return IdleState{}; }
	std::optional<PlayerAnimVar> On_Event(StartedShootingState& s, const EventStartedMoving e) { std::cout << "StartedMovingAndShooting" << std::endl;  return StartedMovingAndShootingState{}; }
	std::optional<PlayerAnimVar> On_Event(StartedShootingState& s, const EventStartedJumping e) { std::cout << "StartedJumpAndShooting" << std::endl;  return StartedJumpAndShootingState{}; }

	
	std::optional<PlayerAnimVar> On_Event(StartedMovingState& s, const EventMoveStartFinished& e) { std::cout << "Moving" << std::endl; return MovingState{}; }
	std::optional<PlayerAnimVar> On_Event(StartedMovingState& s, const EventStartedJumping& e) { std::cout << "StartedJump" << std::endl; return StartedJumpState{}; }
	std::optional<PlayerAnimVar> On_Event(StartedMovingState& s, const EventStartedShooting& e) { std::cout << "StartedMovingAndShooting" << std::endl; return StartedMovingAndShootingState{}; }
	std::optional<PlayerAnimVar> On_Event(StartedMovingState& s, const EventFell& e) { std::cout << "Falling" << std::endl; return FallingState{}; }
	std::optional<PlayerAnimVar> On_Event(StartedMovingState& s, const EventHit& e) { std::cout << "Hit" << std::endl; return HitState{}; }
	std::optional<PlayerAnimVar> On_Event(StartedMovingState& s, const EventStoppedMoving& e) { std::cout << "Idle" << std::endl; return IdleState{}; }


	std::optional<PlayerAnimVar> On_Event(StartedMovingAndShootingState& s, const EventHit& e) { std::cout << "Hit" << std::endl; return HitState{}; }
	std::optional<PlayerAnimVar> On_Event(StartedMovingAndShootingState& s, const EventFell& e) { std::cout << "FallingAndShooting" << std::endl; return FallingAndShootingState{}; }
	std::optional<PlayerAnimVar> On_Event(StartedMovingAndShootingState& s, const EventStoppedMoving& e) { std::cout << "Shooting" << std::endl; return ShootingState{}; }
	std::optional<PlayerAnimVar> On_Event(StartedMovingAndShootingState& s, const EventMoveStartFinished& e) { std::cout << "MovingAndShooting" << std::endl; return MovingAndShootingState{}; }

	std::optional<PlayerAnimVar> On_Event(StartedMovingAndShootingState& s, const EventStoppedShooting& e) { std::cout << "Moving" << std::endl; return MovingState{}; }
	std::optional<PlayerAnimVar> On_Event(StartedMovingAndShootingState& s, const EventStartedJumping& e) { std::cout << "StartedJumpAndShooting" << std::endl; return StartedJumpAndShootingState{}; }




	/*std::optional<PlayerAnimVar> On_Event(InAirState& s, const EventLanded& e)
	{
		if (e.isMoving)
			return RunningState{};
		else
			return IdleState{};
	}*/
	template <typename State, typename Event>
	std::optional<PlayerAnimVar> On_Event(State&, const Event&) { 	return std::nullopt; 	}
	std::string getStateName()
	{
		if (std::holds_alternative<IdleState>(state_)) { return "Idle"; }
		else if (std::holds_alternative<HitState>(state_)) { return "Hit"; }
		else if (std::holds_alternative<DeadState>(state_)) { return "Dead"; }
		else if (std::holds_alternative<ShootingState>(state_)) { return "Shooting"; }
		else if (std::holds_alternative<MovingState>(state_)) { return "Moving"; }
		else if (std::holds_alternative<StartedJumpState>(state_)) { return "StartedJump"; }
		else if (std::holds_alternative<RisingState>(state_)) { return "Rising"; }
		else if (std::holds_alternative<RisingAndShootingState>(state_)) {return "RisingAndShooting";}
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
		else if (std::holds_alternative <StartedShootingState > (state_)) { return "StartedShooting"; }
		else if (std::holds_alternative <StartedMovingState>(state_)) { return "StartedMoving"; }
		else if (std::holds_alternative <StartedMovingAndShootingState >(state_)) { return "StartedMovingAndShooting"; }
		else if (std::holds_alternative <WarningState >(state_)) { return "Warning"; }
		else if (std::holds_alternative <GuardingState >(state_)) { return "Guarding"; }
		else { return "None"; }
	}
};
#endif