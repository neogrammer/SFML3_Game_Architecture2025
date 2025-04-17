#include "Player.h"
#include <animation/DuckFold.h>

Player::Player()
	: AnimObject{ Cfg::Textures::MegaManSheet1x48x48x1,{{1,1},{48,48}},{0.f,0.f}, {0.f,0.f},{300.f,300.f}}
{
	setPosition({ 0.f,0.f });
	setTexRect({ {1,1},{48,48} });
	setScale({ 5.f,5.f });
	currWorldSize = {48.f*5.f,48.f*5.f};
	loadInFile("Player.anim");
}

Player::~Player()
{
}

void Player::handleInput()
{

	rightPressed = false;
	leftPressed = false;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right))
	{
		rightPressed = true;
	}
	

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left))
	{
		leftPressed = true;
	}
	
}

void Player::update(float dt_)
{
	bool playerFacingRight{};


	auto nameBefore = fsm.getStateName();
	auto dirBefore = animMgr.getCurrDir();
	if (dirBefore == AnimDir::Right)
		playerFacingRight = true;
	else if (dirBefore == AnimDir::Left)
		playerFacingRight = false;
	AnimDir dirAfter{ dirBefore };
	if ((rightPressed && leftPressed) || (!rightPressed && !leftPressed))
	{
		dispatch(fsm, EventStoppedMoving{});
		velocity.x = 0.f;
	}
	else
	{
		if (rightPressed)
		{
			dispatch(fsm, EventMoved{});
			velocity.x = MOVESPEED;
			dirAfter = AnimDir::Right;
		
		}
		else if (leftPressed)
		{
			// left was pressed
			dispatch(fsm, EventMoved{});
			velocity.x = -MOVESPEED;
			dirAfter = AnimDir::Left;
		}
		else
		{

		}
	}

	bool playerFacingRightAfter{};
	
	if (dirAfter == AnimDir::Right)
		playerFacingRightAfter = true;
	else if (dirAfter == AnimDir::Left)
		playerFacingRightAfter = false;

	auto nameAfter = fsm.getStateName();


	if (playerFacingRight != playerFacingRightAfter)
	{
		if (playerFacingRightAfter == true)
		{
			animMgr.setCurrDir(AnimDir::Right);
		}
		else
		{
			animMgr.setCurrDir(AnimDir::Left);
		}
	}

	auto finalDir = animMgr.getCurrDir();

	if(nameBefore != nameAfter || finalDir != dirBefore)
	{
		animMgr.switchAnim(AnimNameLUT[nameAfter], finalDir);
		setTexID(animMgr.getTexID());
	}
	else
	{

	}

	//if (name != fsm.getStateName() || dir != animMgr.getCurrDir())
	//{
		//animation switched, update the texture
		
		//animMgr.switchAnim(AnimNameLUT[name], animMgr.getCurrDir());
	//}
	
	
//	auto r = animMgr.currFrame();
	animMgr.animate(dt_);
//	if (r != animMgr.currFrame())
//	{
		// frame changed
		setTexRect(animMgr.currFrame());
	//}

}

void Player::finalize(float dt_)
{

	setTexRect(animMgr.currFrame());
	move(velocity * dt_);

	// final tick after collision detection

	//if (animMgr.getTexID() != getTexID())
	//{
	//	setTexID(animMgr.getTexID());
	//}

	//setTexRect(animMgr.currFrame());
}

