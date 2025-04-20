#include "Player.h"
#include <animation/DuckFold.h>

Player::Player()
	: AnimObject{ Cfg::Textures::MegaManSheet1x48x48x1,{{0,160},{130,160}},{0.f,0.f}, {130.f,160.f},{300.f,300.f}}
{
	setPosition({ 300.f,600.f });
	setTexRect({ {0,160},{130,160} });
	currWorldSize = {130.f,160.f};
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

void Player::finalize(float dt_, sf::RenderWindow& wnd_)
{
	auto vw = wnd_.getView();
	if (rightPressed)
	{
		// if player is going to be still on the left side of screen after moving, then move the player
		if (getPosition().x + velocity.x * dt_ < bgLowBoundX || vw.getCenter().x >= bgHighBoundX)
		{
			move(velocity * dt_);
		}
		else // move the player to the center, move the view instead by (playerPosition if moved - view.getCenter) * dt_
		{
			vw.move({ (getPosition().x + velocity.x * dt_) - vw.getCenter().x, 0.f });
			wnd_.setView(vw);
			setPosition({ wnd_.mapPixelToCoords({(int)bgLowBoundX,(int)bgLowBoundY}).x, getPosition().y});
		}
	}
	else if (leftPressed)
	{
		// if player is going to be still on the left side of screen after moving, then move the player
		if (getPosition().x + velocity.x * dt_ > bgHighBoundX || vw.getCenter().x <= bgLowBoundX)
		{
			move({ velocity.x * dt_, 0.f });
		}
		else // move the player to the center, move the view instead by (playerPosition if moved - view.getCenter) * dt_
		{
			vw.move({ (getPosition().x + velocity.x * dt_) - (vw.getCenter().x) , 0.f });
			wnd_.setView(vw);
			setPosition({ wnd_.mapPixelToCoords({(int)bgLowBoundX,(int)bgLowBoundY}).x, getPosition().y });
		}
	}

	// apply y velocity
	setPosition({ getPosition().x, getPosition().y + (getVelocity().y * dt_) });
}

void Player::setBGSize(float lx_, float hx_, float ly_, float hy_)
{
	bgLowBoundX = lx_;
	bgLowBoundY = ly_;
	bgHighBoundX = hx_;
	bgHighBoundY = hy_;


}

