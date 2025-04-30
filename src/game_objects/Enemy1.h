#ifndef ENEMY1_H__
#define ENEMY1_H__
#include <game_objects/Enemy.h>
class Projectile;
class BusterShot;
class Player;
class Enemy1 : public Enemy
{
	bool rightCannonShotLast{ false };
	float cannonCoolDown{ 2.2f };

	bool rollingRight{ false };
	std::vector<std::unique_ptr<Projectile>> projectiles;

public:
	Enemy1() = delete;
	Enemy1(float coolDown_, sf::Vector2f position_);
	~Enemy1() override {}
	void update(float dt_) override;
	void finalize(float dt_, sf::RenderWindow& wnd_) override;

	//void translateData(void*** outToBase_, size_t numElems_, size_t elemSize_);

	void stopMove();
	void turnAround();
	void shoot(Player& target_);
};

#endif