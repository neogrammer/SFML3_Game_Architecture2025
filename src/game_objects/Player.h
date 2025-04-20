
#ifndef PLAYER_H__
#define PLAYER_H__

#include "AnimObject.h"
#include <animation/PlayerAnimFSM.h>
class Player : public AnimObject
{
	friend class Physics;
	friend class PlayState;
	float bgLowBoundX{ 800.f };
	float bgHighBoundX{ 7200.f };

	float bgLowBoundY{ 450.f };
	float bgHighBoundY{ 450.f };

	bool rightPressed{ false };
	bool leftPressed{ false };
	bool jumpPressed{ false };
	const float MOVESPEED{ 300.f };

	bool canJump{ false };
	bool justJumped{ false };
	bool falling{ true };
	bool rising{ false };

	bool reachedJumpPeak{ false };
	float topOfJumpHoldTime{ 0.1f };
	float topOfJumpHoldTimeElapsed{ 0.f };
	const float JUMPSTRENGTH{ 800.f };
	float currJumpHeight{ 0.f };
	const float MAXJUMPHEIGHT{800.f};
	float jumpHeightComparator{ 0.f };




public:
	using AnimObject::AnimObject;
	Player();
	virtual ~Player() override final;
	
	void handleInput() override final;
	void update(float dt_) override final;
	void finalize(float dt_, sf::RenderWindow& wnd_) override final;

	void setBGSize(float lx_, float hx_, float ly_, float hy_);

	void jump();
	void updateJump(float dt_);

public:
	FSM_Player fsm;
};

#endif
