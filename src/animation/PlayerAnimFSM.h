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

	std::optional<PlayerAnimVar> On_Event(IdleState& s, const EventMoved& e) { std::cout << "Running" << std::endl; return RunningState{}; }

	std::optional<PlayerAnimVar> On_Event(RunningState& s, const EventStoppedMoving& e) { std::cout << "Idle" << std::endl;  return IdleState{}; }


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
		else { return "None"; }
	}
};
#endif