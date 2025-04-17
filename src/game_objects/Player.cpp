#include "Player.h"

Player::Player()
	: AnimObject{}
{
	setPosition({ 0.f,0.f });
	setTexRect({ {1,1},{48,48} });
	setScale({ 5.f,5.f });

}

Player::~Player()
{
}

void Player::handleInput()
{

}

void Player::update(float dt_)
{


	animMgr.animate(dt_);


}

void Player::finalize(float dt_)
{
	// final tick after collision detection

	if (animMgr.getTexID() != getTexID())
	{
		setTexID(animMgr.getTexID());
	}

	setTexRect(animMgr.currFrame());
}
