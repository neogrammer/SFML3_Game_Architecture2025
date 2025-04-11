

// ===== ProjectileObj.h =====
#pragma once
#include "../DrawableObj.h"

class ProjectileObj : public DrawableObj {
public:
    ProjectileObj(const sf::Texture& tex_);
    virtual ~ProjectileObj() = default;

    void update(float dt) override;

protected:

    float _lifetime;

    // Inherited via DrawableObj
    void commit(float dt) override;
};

//#ifndef PROJECTILE_H__
//#define PROJECTILE_H__
//#include "ProjectileTypes.h"
//#include <SFML/Audio/Sound.hpp>
//
//#include <GameObjects/DrawableObj.h>
//class Projectile : public DrawableObj
//{
//
//protected:
//	static std::vector<sf::Sound> sounds;
//	proj::DirType m_dirType;
//	proj::DmgType m_dmgType;
//	int m_power;
//	bool m_alive{ true };
//public:
//	Projectile(sf::Vector2f pos_ = { 0.f,0.f });
//	Projectile(proj::DirType type_, proj::DmgType dmg_, int power_, sf::Vector2f pos_ = { 0.f,0.f });
//	virtual ~Projectile() = 0;
//	Projectile(const Projectile&) = default;
//	Projectile& operator=(const Projectile&) = default;
//	Projectile(Projectile&&) = default;
//	Projectile& operator=(Projectile&&) = default;
//
//	virtual void update(float dt_) override = 0;
//	virtual void render(sf::RenderWindow& dt_) = 0;
//
//	bool isAlive() { return m_alive; }
//	void setAlive(bool cond_) { m_alive = cond_; }
//
//	void deflect();
//};
//
//#endif