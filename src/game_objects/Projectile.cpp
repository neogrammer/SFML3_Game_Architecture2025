#include "Projectile.h"

Projectile::Projectile(GameObject* owner_, Cfg::Textures texID_, sf::IntRect rect_, sf::Vector2f texOff_, sf::Vector2f size_, sf::Vector2f pos_ )
	: AnimObject::AnimObject{texID_, rect_, texOff_, size_, pos_}
	, owner{dynamic_cast<AnimObject*>(owner_)}
{
}

Projectile::~Projectile()
{
}
