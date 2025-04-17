
#ifndef PLAYER_H__
#define PLAYER_H__

#include "AnimObject.h"

class Player : public AnimObject
{
public:
	using AnimObject::AnimObject;
	Player();
	virtual ~Player() override final;
	
	void handleInput() override final;
	void update(float dt_) override final;
	void finalize(float dt_) override final;
};

#endif
