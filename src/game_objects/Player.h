
#ifndef PLAYER_H__
#define PLAYER_H__

#include "AnimObject.h"
#include <animation/PlayerAnimFSM.h>
class Player : public AnimObject
{
	bool rightPressed{ false };
	bool leftPressed{ false };
	const float MOVESPEED{ 300.f };
public:
	using AnimObject::AnimObject;
	Player();
	virtual ~Player() override final;
	
	void handleInput() override final;
	void update(float dt_) override final;
	void finalize(float dt_) override final;

public:
	FSM_Player fsm;
};

#endif
