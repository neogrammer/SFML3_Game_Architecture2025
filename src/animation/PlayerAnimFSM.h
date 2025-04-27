#ifndef PLAYERANIMFSM_H__
#define PLAYERANIMFSM_H__
#include "DuckFold.h"
#include <optional>
#include "PlayerAnimStates.h"
#include <type_traits>
#include <variant>
#include <iostream>

class FSM_Player : public FSM<FSM_Player, PlayerAnimVar>
{
public:

	std::optional<PlayerAnimVar> On_Event(IdleState& s, const EventMoved& e) { std::cout << "IdleToRun" << std::endl; return IdleToRunState{}; }
	std::optional<PlayerAnimVar> On_Event(IdleState& s, const EventShoot& e) { std::cout << "ShootSetup" << std::endl; return ShootSetupState{}; }
	std::optional<PlayerAnimVar> On_Event(IdleState& s, const EventJumped& e) { std::cout << "LiftOff" << std::endl; return LiftOffState{}; }
	std::optional<PlayerAnimVar> On_Event(IdleState& s, const EventFell& e) { std::cout << "Falling" << std::endl;  return FallingState{}; }


	std::optional<PlayerAnimVar> On_Event(RunningState& s, const EventStoppedMoving& e) { std::cout << "Idle" << std::endl;  return IdleState{}; }
	std::optional<PlayerAnimVar> On_Event(RunningState& s, const EventShoot& e) { std::cout << "RunningAndShooting" << std::endl;  return RunningAndShootingState{}; }
	std::optional<PlayerAnimVar> On_Event(RunningState& s, const EventJumped& e) { std::cout << "LiftOff" << std::endl;  return LiftOffState{}; }
	std::optional<PlayerAnimVar> On_Event(RunningState& s, const EventFell& e) { std::cout << "Falling" << std::endl;  return FallingState{}; }

	std::optional<PlayerAnimVar> On_Event(RunningAndShootingState& s, const EventFell& e) { std::cout << "FallingAndShooting" << std::endl;  return FallingAndShootingState{}; }
	std::optional<PlayerAnimVar> On_Event(RunningAndShootingState& s, const EventStoppedMoving& e) { std::cout << "Shooting" << std::endl;  return ShootingState{}; }
	std::optional<PlayerAnimVar> On_Event(RunningAndShootingState& s, const EventStoppedShooting& e) { std::cout << "Running" << std::endl;  return RunningState{}; }
	std::optional<PlayerAnimVar> On_Event(RunningAndShootingState& s, const EventJumped& e) { std::cout << "LiftOffAndShooting" << std::endl;  return LiftOffAndShootingState{}; }

	


	std::optional<PlayerAnimVar> On_Event(IdleToRunState& s, const EventStoppedMoving& e) { std::cout << "Idle" << std::endl;  return IdleState{}; }
	std::optional<PlayerAnimVar> On_Event(IdleToRunState& s, const EventMoved& e) { std::cout << "Running" << std::endl;  return RunningState{}; }
	std::optional<PlayerAnimVar> On_Event(IdleToRunState& s, const EventShoot& e) { std::cout << "IdleToRunAndShooting" << std::endl;  return IdleToRunAndShootingState{}; }
	std::optional<PlayerAnimVar> On_Event(IdleToRunState& s, const EventJumped& e) { std::cout << "LiftOff" << std::endl;  return LiftOffState{}; }
	std::optional<PlayerAnimVar> On_Event(IdleToRunState& s, const EventFell& e) { std::cout << "Falling" << std::endl;  return FallingState{}; }


	std::optional<PlayerAnimVar> On_Event(ShootSetupState& s, const EventShootSetupTimedOut& e) { std::cout << "Shooting" << std::endl; return ShootingState{}; } 
	std::optional<PlayerAnimVar> On_Event(ShootSetupState& s, const EventStoppedShooting& e) { std::cout << "Idle" << std::endl;  return IdleState{}; }
	std::optional<PlayerAnimVar> On_Event(ShootSetupState& s, const EventMoved& e) { std::cout << "RunningAndShooting" << std::endl;  return RunningAndShootingState{}; }
	std::optional<PlayerAnimVar> On_Event(ShootSetupState& s, const EventFell& e) { std::cout << "FallingAndShooting" << std::endl;  return FallingAndShootingState{}; }

	std::optional<PlayerAnimVar> On_Event(IdleToRunAndShootingState& s, const EventIdleToRunTimedOut& e) { std::cout << "RunningAndShooting" << std::endl; return RunningAndShootingState{}; }
	std::optional<PlayerAnimVar> On_Event(IdleToRunAndShootingState& s, const EventStoppedShooting& e) { std::cout << "IdleToRun" << std::endl; return IdleToRunState{}; }
	std::optional<PlayerAnimVar> On_Event(IdleToRunAndShootingState& s, const EventJumped& e) { std::cout << "LiftOffAndShooting" << std::endl;  return LiftOffAndShootingState{}; }
	std::optional<PlayerAnimVar> On_Event(IdleToRunAndShootingState& s, const EventStoppedMoving& e) { std::cout << "Shooting" << std::endl;  return ShootingState{}; }
	std::optional<PlayerAnimVar> On_Event(IdleToRunAndShootingState& s, const EventFell& e) { std::cout << "FallingAndShooting" << std::endl;  return FallingAndShootingState{}; }



	std::optional<PlayerAnimVar> On_Event(ShootingState& s, const EventStoppedShooting& e) { std::cout << "Idle" << std::endl; return IdleState{}; }
	std::optional<PlayerAnimVar> On_Event(ShootingState& s, const EventFell& e) { std::cout << "Falling" << std::endl; return FallingState{}; }
	std::optional<PlayerAnimVar> On_Event(ShootingState& s, const EventMoved& e) { std::cout << "RunningAndShooting" << std::endl; return RunningAndShootingState{}; }
	std::optional<PlayerAnimVar> On_Event(ShootingState& s, const EventJumped& e) { std::cout << "LiftOffAndShooting" << std::endl;  return LiftOffAndShootingState{}; }



	std::optional<PlayerAnimVar> On_Event(LiftOffState& s, const EventJumpReleased& e) { std::cout << "Falling" << std::endl; return FallingState{}; }
	std::optional<PlayerAnimVar> On_Event(LiftOffState& s, const EventShoot& e) { std::cout << "LiftOffAndShooting" << std::endl; return LiftOffAndShootingState{}; }
	std::optional<PlayerAnimVar> On_Event(LiftOffState& s, const EventLiftOffTimedOut& e) { std::cout << "Rising" << std::endl; return RisingState{}; }
	
	std::optional<PlayerAnimVar> On_Event(LiftOffAndShootingState& s, const EventJumpReleased& e) { std::cout << "FallingAndShooting" << std::endl; return FallingAndShootingState{}; }
	std::optional<PlayerAnimVar> On_Event(LiftOffAndShootingState& s, const EventStoppedShooting& e) { std::cout << "LiftOff" << std::endl; return LiftOffState{}; }
	std::optional<PlayerAnimVar> On_Event(LiftOffAndShootingState& s, const EventLiftOffTimedOut& e) { std::cout << "RisingAndShooting" << std::endl; return RisingAndShootingState{}; }



	std::optional<PlayerAnimVar> On_Event(RisingState& s, const EventFell& e) { std::cout << "Falling" << std::endl; return FallingState{}; }
	std::optional<PlayerAnimVar> On_Event(RisingState& s, const EventShoot& e) { std::cout << "RisingAndShooting" << std::endl; return RisingAndShootingState{}; }
	std::optional<PlayerAnimVar> On_Event(RisingState& s, const EventEnteredJumpPeak& e) { std::cout << "JumpPeakRising" << std::endl; return JumpPeakRisingState{}; }


	std::optional<PlayerAnimVar> On_Event(RisingAndShootingState& s, const EventFell& e) { std::cout << "FallingAndShooting" << std::endl; return FallingAndShootingState{}; }
	std::optional<PlayerAnimVar> On_Event(RisingAndShootingState& s, const EventStoppedShooting& e) { std::cout << "Rising" << std::endl; return RisingState{}; }
	std::optional<PlayerAnimVar> On_Event(RisingAndShootingState& s, const EventEnteredJumpPeak& e) { std::cout << "JumpPeakRisingAndShooting" << std::endl; return JumpPeakRisingAndShootingState{}; }



	std::optional<PlayerAnimVar> On_Event(JumpPeakRisingState& s, const EventReachedJumpMax& e) { std::cout << "JumpPeakFalling" << std::endl; return JumpPeakFallingState{}; }
	std::optional<PlayerAnimVar> On_Event(JumpPeakRisingState& s, const EventFell& e) { std::cout << "Falling" << std::endl; return FallingState{}; }
	std::optional<PlayerAnimVar> On_Event(JumpPeakRisingState& s, const EventShoot& e) { std::cout << "JumpPeakRisingAndShooting" << std::endl; return JumpPeakRisingAndShootingState{}; }



	std::optional<PlayerAnimVar> On_Event(JumpPeakRisingAndShootingState& s, const EventReachedJumpMax& e) { std::cout << "JumpPeakFallingAndShooting" << std::endl; return JumpPeakFallingAndShootingState{}; }
	std::optional<PlayerAnimVar> On_Event(JumpPeakRisingAndShootingState& s, const EventFell& e) { std::cout << "FallingAndShooting" << std::endl; return FallingAndShootingState{}; }
	std::optional<PlayerAnimVar> On_Event(JumpPeakRisingAndShootingState& s, const EventStoppedShooting& e) { std::cout << "JumpPeakRising" << std::endl; return JumpPeakRisingState{}; }


	std::optional<PlayerAnimVar> On_Event(JumpPeakFallingState& s, const EventFell& e) { std::cout << "Falling" << std::endl; return FallingState{}; }
	std::optional<PlayerAnimVar> On_Event(JumpPeakFallingState& s, const EventExitingJumpPeak& e) { std::cout << "Falling" << std::endl; return FallingState{}; }
	std::optional<PlayerAnimVar> On_Event(JumpPeakFallingState& s, const EventShoot& e) { std::cout << "JumpPeakFallingAndShootingState" << std::endl; return JumpPeakFallingAndShootingState{}; }


	std::optional<PlayerAnimVar> On_Event(JumpPeakFallingAndShootingState& s, const EventFell& e) { std::cout << "FallingAndShooting" << std::endl; return FallingAndShootingState{}; }
	std::optional<PlayerAnimVar> On_Event(JumpPeakFallingAndShootingState& s, const EventExitingJumpPeak& e) { std::cout << "FallingAndShooting" << std::endl; return FallingAndShootingState{}; }
	std::optional<PlayerAnimVar> On_Event(JumpPeakFallingAndShootingState& s, const EventStoppedShooting& e) { std::cout << "JumpPeakFallingState" << std::endl; return JumpPeakFallingState{}; }



	std::optional<PlayerAnimVar> On_Event(FallingState& s, const EventLanded& e) { std::cout << "Landing" << std::endl; return LandingState{}; }
	std::optional<PlayerAnimVar> On_Event(FallingState& s, const EventShoot& e) { std::cout << "FallingAndShooting" << std::endl; return FallingAndShootingState{}; }
	
	
	std::optional<PlayerAnimVar> On_Event(FallingAndShootingState& s, const EventLanded& e) { std::cout << "LandingAndShooting" << std::endl; return LandingAndShootingState{}; }
	std::optional<PlayerAnimVar> On_Event(FallingAndShootingState& s, const EventStoppedShooting& e) { std::cout << "Falling" << std::endl; return FallingState{}; }


	std::optional<PlayerAnimVar> On_Event(LandingState& s, const EventFullyLanded& e) { std::cout << "Idle" << std::endl; return IdleState{}; }
	std::optional<PlayerAnimVar> On_Event(LandingState& s, const EventShoot& e) { std::cout << "LandingAndShooting" << std::endl; return LandingAndShootingState{}; }
	std::optional<PlayerAnimVar> On_Event(LandingState& s, const EventFell& e) { std::cout << "Falling" << std::endl; return FallingState{}; }
	std::optional<PlayerAnimVar> On_Event(LandingState& s, const EventMoved& e) { std::cout << "Running" << std::endl; return RunningState{}; }



	std::optional<PlayerAnimVar> On_Event(LandingAndShootingState& s, const EventFullyLanded& e) { std::cout << "Shooting" << std::endl; return ShootingState{}; }
	std::optional<PlayerAnimVar> On_Event(LandingAndShootingState& s, const EventStoppedShooting& e) { std::cout << "Landing" << std::endl; return LandingState{}; }
	std::optional<PlayerAnimVar> On_Event(LandingAndShootingState& s, const EventFell& e) { std::cout << "FallingAndShooting" << std::endl; return FallingAndShootingState{}; }
	std::optional<PlayerAnimVar> On_Event(LandingAndShootingState& s, const EventMoved& e) { std::cout << "RunningAndShooting" << std::endl; return RunningAndShootingState{}; }



	
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
		else if (std::holds_alternative<RunningState>(state_)) { return "Running"; }
		else if (std::holds_alternative<ShootSetupState>(state_)) { return "ShootSetup"; }
		else if (std::holds_alternative<ShootingState>(state_)) { return "Shooting"; }
		else if (std::holds_alternative<IdleToRunState>(state_)) { return "IdleToRun"; }
		else if (std::holds_alternative<RunningAndShootingState>(state_)) { return "RunningAndShooting"; }
		else if (std::holds_alternative<IdleToRunAndShootingState>(state_)) { return "IdleToRunAndShooting"; }
		else if (std::holds_alternative<RisingAndShootingState>(state_)) { return "RisingAndShooting"; }
		else if (std::holds_alternative<RisingState>(state_)) { return "Rising"; }
		else if (std::holds_alternative<JumpPeakRisingAndShootingState>(state_)) { return "JumpPeakRisingAndShooting"; }
		else if (std::holds_alternative<JumpPeakRisingState>(state_)) { return "JumpPeakRising"; }
		else if (std::holds_alternative<JumpPeakFallingAndShootingState>(state_)) { return "JumpPeakFallingAndShooting"; }
		else if (std::holds_alternative<JumpPeakFallingState>(state_)) { return "JumpPeakFalling"; }
		else if (std::holds_alternative<FallingAndShootingState>(state_)) { return "FallingAndShooting"; }
		else if (std::holds_alternative<LandingAndShootingState>(state_)) { return "LandingAndShooting"; }
		else if (std::holds_alternative<FallingState>(state_)) { return "Falling"; }
		else if (std::holds_alternative<LandingState>(state_)) { return "Landing"; }
		else if (std::holds_alternative<LiftOffState>(state_)) { return "LiftOff"; }
		else if (std::holds_alternative<LiftOffAndShootingState>(state_)) { return "LiftOffAndShooting"; }
		else { return "None"; }
	}
};
#endif