// ===== BusterBullet.cpp =====
#include "BusterBullet.h"

BusterBullet::BusterBullet(const sf::Vector2f& position, const sf::Vector2f& direction)
    : ProjectileObj{Cfg::textures.get((int)Cfg::Textures::BusterBullet) }
{
    setPos(position);
    setVelocity(direction * 500.f); // Bullet speed
    _lifetime = 2.f;

    
    DrawableObj::initialize("BusterBullet.anim", { 24.f,18.f }, getPos(), Cfg::textures.get((int)Cfg::Textures::BusterBullet), getVelocity());
    setTexture(Cfg::textures.get((int)Cfg::Textures::PlayerAtlas));
}

//#include "BusterBullet.h"
//
//void BusterBullet::update(float dt_)
//{
//	animHandler.update(dt_);
//	frameElapsed += dt_;
//	if (frameElapsed > frameDelay)
//	{
//		m_currentFrame++;
//		frameElapsed = 0.f;
//		if (m_currentFrame > this->m_texFramesUni.at("Projectile").size() - 1)
//		{
//			m_currentFrame = 0;
//		}
//	}
//	DrawableObj::update(dt_);
//}
//
//void BusterBullet::render(sf::RenderWindow& wnd_)
//{
//	auto vw = wnd_.getView().getCenter();
//	
//	if (this->GetPosition().x > vw.x + (wnd_.getSize().x / 2.f) || this->GetPosition().x + this->getTexRectSize().x < vw.x - (wnd_.getSize().x / 2.f))
//	{
//		this->setAlive(false);
//	}
//
//	DrawableObj::render(wnd_);
//}
