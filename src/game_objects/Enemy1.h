#ifndef ENEMY1_H__
#define ENEMY1_H__
#include <game_objects/Enemy.h>
class Enemy1 : public Enemy
{
public:
	using Enemy::Enemy;
	~Enemy1() override {}
};

#endif