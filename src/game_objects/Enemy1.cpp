#include "Enemy1.h"

//void Enemy1::translateData(void*** outToBase_, size_t numElems_, size_t elemSize_)
//{
//	cannonCoolDown = *reinterpret_cast<float*>(**outToBase_);
//}

Enemy1::Enemy1(float coolDown_, sf::Vector2f position_)
	: Enemy::Enemy{ Cfg::Textures::GooglyEye, {{0,0},{96,64}}, {45.f,44.f}, {42.f,20.f}, {position_} }
	, cannonCoolDown {coolDown_}
{
	loadInFile("GoogleEye.anim");
}

void Enemy1::update(float dt_)
{
	
}

void Enemy1::finalize(float dt_, sf::RenderWindow& wnd_)
{
	move(velocity * dt_);
}
