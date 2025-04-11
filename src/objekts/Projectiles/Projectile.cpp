
// ===== ProjectileObj.cpp =====
#include <GameObjects/Projectiles/Projectile.h>

ProjectileObj::ProjectileObj(const sf::Texture& tex_) : DrawableObj(tex_) , _lifetime(5.f)
{
    
}


void ProjectileObj::update(float dt) {
    setPos(getPos() +  ( getVelocity() * dt));

    _lifetime -= dt;
    if (_lifetime <= 0.f) {
        // Mark for deletion
    }

    animHandler.update(dt);
}

void ProjectileObj::commit(float dt)
{
}


//#include "Projectile.h"
//std::vector<sf::Sound> Projectile::sounds = {};
//
//Projectile::Projectile(sf::Vector2f pos_)	
//	: Projectile( proj::DirType::Horizontal , proj::DmgType::Burst, 1, pos_ )
//{}
//
//Projectile::~Projectile()
//{
//	sounds.emplace_back(Cfg::sounds.get((int)Cfg::Sounds::HelmetHit));
//}
////
////void Projectile::render(sf::RenderWindow& wnd_)
////{
////	sf::Sprite aSprite{ Cfg::textures.get((int)this->getTextureID()) };
////	aSprite.setTextureRect({ sf::Vector2i{(int)this->getTexRectPos().x, (int)this->getTexRectPos().y}, sf::Vector2i{ (int)(this->getTexRectSize().x),(int)(this->getTexRectSize().y) } });
////	aSprite.setPosition({ this->GetPosition().x - this->getFrameOffset().x, this->GetPosition().y - this->getFrameOffset().y , });
////	wnd_.draw(aSprite);
////
////	DrawableObj::render(wnd_);
////}
//
//void Projectile::deflect()
//{
//	sounds[0].play();
//	this->getVelocityRef().x *= -1.f;
//	this->getVelocityRef().y = -40.f;
//
//}
//
//Projectile::Projectile(proj::DirType dir_, proj::DmgType dmg_, int power_, sf::Vector2f pos_)
//	: DrawableObj{}
//    , m_dirType{dir_}
//	, m_dmgType{dmg_}
//	, m_power{power_}
//{
//	DrawableObj::initialize("BusterBullet.anim", { 27.f, 17.f }, Cfg::Textures::BusterBullet, pos_, { 0.f,0.f });
//
//}
