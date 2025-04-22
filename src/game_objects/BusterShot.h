#ifndef BUSTERSHOT_H__
#define BUSTERSHOT_H__
#include "Projectile.h"

class BusterShot : public Projectile
{
public:
	using Projectile::Projectile;
	BusterShot(GameObject* owner_, Cfg::Textures texID_, sf::IntRect rect_, sf::Vector2f texOff_, sf::Vector2f size_, sf::Vector2f pos_);
	BusterShot() {}

	~BusterShot() override final;
	void update(float dt_) override final;
	void render(sf::RenderWindow& wnd_) override final;
	void finalize(float dt_, sf::RenderWindow& wnd_) override final;



};

#endif