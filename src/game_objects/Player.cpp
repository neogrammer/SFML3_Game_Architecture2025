#include "Player.h"
#include <animation/DuckFold.h>

Player::Player()
	: AnimObject{ Cfg::Textures::MegaManSheet1x48x48x1,{{0,160}, { 130,160 }},{50.f,50.f}, {49.f,79.f},{300.f,300.f} }
	, projectiles{}
{
	setPosition({ 300.f,600.f });
	setTexRect({ {0,160},{130,160} });
	currWorldSize = {49.f,79.f};
	loadInFile("Player.anim");
	animMgr.switchAnim(AnimName::Idle, AnimDir::Right);
	setWorldSize({ 49.f,79.f });

	projectiles.clear();
}

Player::~Player()
{
}

void Player::renderBullets(sf::RenderWindow& wnd_)
{
	for (auto& b : projectiles)
	{
		wnd_.draw(*b);
	}
}

void Player::handleInput()
{

	rightPressed = false;
	leftPressed = false;
	jumpPressed = false;
	shootPressed = false;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right))
	{
		rightPressed = true;
	}
	

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left))
	{
		leftPressed = true;
	}
	
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space))
	{
		jumpPressed = true;
	}
	if (!jumpPressed && landingJumpButtonHeld)
	{
		landingJumpButtonHeld = false;
		canJump = true;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Enter))
	{
		shootPressed = true;
	}

}

void Player::update(float dt_)
{




	for (auto& b : projectiles)
	{
		b->update(dt_);
	}

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

	if (shootCoolingDown)
	{
		shootCooldownElapsed += dt_;
		if (shootCooldownElapsed >= shootCooldownTime)
		{
			shootCooldownElapsed = 0.f;
			shootCoolingDown = false;
		}
	}
	else
	{
		if (shootPressed)
		{
			shoot();
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
	if (!jumpPressed && landingJumpButtonHeld)
	{
		landingJumpButtonHeld = false;
		canJump = true;
	}
	

	// lets update jump before doing a jump() so that the initial jump state gets counted for this frame then next frame it will update as needed, jump() is idempotent if canJump is false, which happens when first jumping until landing back down
	//  flag must be changed by the collision system
	updateJump(dt_);
	if (jumpPressed)
	{
		jump();
	}

	if (!jumpPressed && waitingForJumpButton)
	{
		waitingForJumpButton = false;
		canJump = true;
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
	std::vector<std::vector<std::shared_ptr<Projectile>>::iterator> itt{};
	
	for (int i = 0; i < projectiles.size(); i++)
	{
		auto vw = wnd_.getView().getCenter().x;
		if (projectiles[i]->getPosition().x < vw - wnd_.getSize().x / 2.f || projectiles[i]->getPosition().x > vw + wnd_.getSize().x / 2.f)
		{
		
			itt.push_back(projectiles.begin()+i);

		}
		
	}

	for (auto start = itt.rbegin(); start != itt.rend(); start++)
	{
		projectiles.erase(*start);
	}
	projectiles.shrink_to_fit();
	

	std::vector<std::vector<std::shared_ptr<Projectile>>::iterator>  ers;
	for (int i = 0; i < projectiles.size(); i++)
	{
		if (projectiles[i]->hasCollided())
		{
			auto* collider = projectiles[i]->getCollider();

			if (collider)
			{
				collider->getHit(projectiles[i]->getPower());

			}

			ers.push_back(projectiles.begin() + i);
		}
	}

	for (auto start = ers.rbegin(); start != ers.rend(); start++)
	{
		projectiles.erase(*start);
	}

	projectiles.shrink_to_fit();



	auto vw = wnd_.getView();
	if (rightPressed)
	{
		// if player is going to be still on the left side of screen after moving, then move the player
		if (getPosition().x + velocity.x * dt_ < bgLowBoundX || vw.getCenter().x >= bgHighBoundX)
		{
			move({ velocity.x * dt_, 0.f });
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

void Player::jump()
{
	if (canJump)
	{
		justJumped = true;
		canJump = false;
		velocity.y -= JUMPSTRENGTH;  // up is down the y axis, so subtract the jump power to send play upward
		falling = false;
		rising = true;

		jumpHeightComparator = getPosition().y;
		currJumpHeight = jumpHeightComparator;
	}

}

void Player::updateJump(float dt_)
{
	if (rising)
	{
		currJumpHeight += velocity.y * dt_;
		if (jumpHeightComparator - currJumpHeight > MAXJUMPHEIGHT) // beacuse up goes down the y axis, and you jump upward
		{
			reachedJumpPeak = true;
			
			topOfJumpHoldTimeElapsed = 0.f;
			rising = false;
			falling = false;
			setVelocity({ getVelocity().x, 0.f });
		}
	}
	else if (reachedJumpPeak)
	{
		topOfJumpHoldTimeElapsed += dt_;
		setVelocity({ getVelocity().x, 0.f });

		if (topOfJumpHoldTimeElapsed >= topOfJumpHoldTime)
		{
			topOfJumpHoldTimeElapsed = 0.f;
			reachedJumpPeak = false;
			falling = true;
		}
	}
	else if (falling)
	{
		// if the collision detection changed the canJump flag, we are no longer falling
		if (canJump)
		{
			falling = false;
		}
	}
}

void Player::getHit(int power)
{
}

void Player::shoot()
{
	if (!shootCoolingDown)
	{
		projectiles.push_back(std::make_shared<BusterShot>(this, Cfg::Textures::BusterShot, sf::IntRect{ sf::Vector2i{0,0},sf::Vector2i{24,14} }, sf::Vector2f{ 0.f,0.f }, sf::Vector2f{ 24.f,14.f }, getPosition()));
	
		if (animMgr.getCurrDir() == AnimDir::Right)
		{ 
			projectiles.back()->setVelocity({ 500.f, 0.f });
		}
		else
		{
			projectiles.back()->setVelocity({ -500.f,0.f });
		}

		shootCoolingDown = true;
		shootCooldownElapsed = 0.f;
	}
}

