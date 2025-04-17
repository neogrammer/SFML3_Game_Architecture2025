#include "Player.h"

<<<<<<< HEAD
Player::Player()
	: AnimObject{}
{
	setPosition({ 0.f,0.f });
	setTexRect({ {1,1},{48,48} });
	setScale({ 5.f,5.f });

=======
Player::Player() : AnimObject{Cfg::Textures::MegaManSheet1x48x48x1,{{0,0},{48,48}},{0.f,0.f},{48.f,48.f},{0.f,0.f}}
{
	loadInFile("Player.anim");
>>>>>>> 715163d0180834600f23e60846ea0b9689190064
}

Player::~Player()
{
<<<<<<< HEAD
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
=======

}
>>>>>>> 715163d0180834600f23e60846ea0b9689190064
