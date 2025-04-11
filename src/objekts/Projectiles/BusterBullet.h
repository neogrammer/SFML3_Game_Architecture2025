
// ===== BusterBullet.h =====
#pragma once
#include <GameObjects/Projectiles/Projectile.h>

class BusterBullet : public ProjectileObj {
public:
    BusterBullet(const sf::Vector2f& position, const sf::Vector2f& direction);
    virtual ~BusterBullet() = default;
};


//#ifndef BUSTERBULLET_H__
//#define BUSTERBULLET_H__
//#include "Projectile.h"
//
//
//class BusterBullet : public Projectile
//{
//	float frameElapsed{ 0.f };
//	float frameDelay{ 0.13f };
//public:
//	BusterBullet(sf::Vector2f pos_ = { 0.f,0.f }) : Projectile{ proj::DirType::Horizontal, proj::DmgType::Burst, 1 }
//	{
//		m_uniDirectional = true;
//		SetPosition({pos_});
//	}
//	~BusterBullet() override final = default;
//	BusterBullet(const BusterBullet&) = default;
//	BusterBullet& operator=(const BusterBullet&) = default;
//	BusterBullet(BusterBullet&&) = default;
//	BusterBullet& operator=(BusterBullet&&) = default;
//
//	inline int GetPower() { return m_power; }
//	inline void SetPower(int power_) { m_power = power_; }
//	inline proj::DirType GetDirType() { return m_dirType; }
//	inline proj::DmgType GetDmgType() { return m_dmgType; }
//
//	void update(float dt_) override final;
//	void render(sf::RenderWindow& wnd_) override final;
//};
//
//#endif