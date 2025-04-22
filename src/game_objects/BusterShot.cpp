#include "BusterShot.h"
#include "Player.h"
BusterShot::BusterShot(GameObject* owner_, Cfg::Textures texID_, sf::IntRect rect_, sf::Vector2f texOff_, sf::Vector2f size_, sf::Vector2f pos_)
	: Projectile::Projectile{ owner_, texID_, rect_, texOff_, size_, pos_ }
{
	// set texture and position based on owners frame index and animation, and direction
	texID = Cfg::Textures::BusterShot;

	auto* p = dynamic_cast<Player*>(owner_);
 	if (p != nullptr)
	{

		if (p->animMgr.getCurrDir() == AnimDir::Right)
		{
			velocity.x = 500.f;
		}
		else
		{
			velocity.x = -500.f;
		}

	}

	setWorldSize({ 24,14, });
	setTexRect({ { 0, 0 }, { 24, 14 } });
	setPosition(owner_->getPosition());


}

BusterShot::~BusterShot()
{
}

void BusterShot::update(float dt_)
{

	move(velocity * dt_);
}

void BusterShot::render(sf::RenderWindow& wnd_)
{
	wnd_.draw(*this);

}

void BusterShot::finalize(float dt_, sf::RenderWindow& wnd_)
{
}
