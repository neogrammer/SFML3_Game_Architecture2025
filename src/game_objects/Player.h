
#ifndef PLAYER_H__
#define PLAYER_H__

#include "AnimObject.h"
#include <animation/PlayerAnimFSM.h>
class Player : public AnimObject
{
	float bgLowBoundX{ 800.f };
	float bgHighBoundX{ 7200.f };

	float bgLowBoundY{ 450.f };
	float bgHighBoundY{ 450.f };

	bool rightPressed{ false };
	bool leftPressed{ false };
	const float MOVESPEED{ 300.f };
public:
	using AnimObject::AnimObject;
	Player();
	virtual ~Player() override final;
	
	void handleInput() override final;
	void update(float dt_) override final;
	void finalize(float dt_, sf::RenderWindow& wnd_) override final;

	void setBGSize(float lx_, float hx_, float ly_, float hy_);

public:
	FSM_Player fsm;
};

#endif
