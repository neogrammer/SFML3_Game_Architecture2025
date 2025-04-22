#ifndef ENEMY_H__
#define ENEMY_H__
#include <game_objects/GameObject.h>
class Enemy : public GameObject
{
public:
	using GameObject::GameObject;
	virtual ~Enemy() override {}
};

#endif