#include "Enemy1.h"
#include <game_objects/BusterShot.h>
#include <game_objects/Player.h>

//void Enemy1::translateData(void*** outToBase_, size_t numElems_, size_t elemSize_)
//{
//	cannonCoolDown = *reinterpret_cast<float*>(**outToBase_);
//}

Enemy1::Enemy1(float coolDown_, sf::Vector2f position_)
	: Enemy::Enemy{ Cfg::Textures::GooglyEye, {{0,0},{192,128}}, {90.f,88.f}, {84.f,40.f}, {position_} }
	, cannonCoolDown {coolDown_}
	, projectiles{}
{
	loadInFile("GooglyEye.anim");
	animMgr.switchAnim(AnimName::Idle, AnimDir::Left);
	
}

void Enemy1::update(float dt_)
{
	int idx = animMgr.getCurrIndex();


	animMgr.animate(dt_);

	int idxAfter = animMgr.getCurrIndex();

	if (idx == 8 && idxAfter == 0)
	{
		if (animMgr.getCurrDir() == AnimDir::Left)
			move({ (float) - animMgr.getTexRect().size.x / 2.8f - 5.f, 0.f});
		else if (animMgr.getCurrDir() == AnimDir::Right)
			move({ (float)animMgr.getTexRect().size.x / 2.8f + 5.f, 0.f });
	}

	for (auto& b : projectiles)
	{
		b->update(dt_);
	}
}

void Enemy1::finalize(float dt_, sf::RenderWindow& wnd_)
{
	move(velocity * dt_);

	setTexRect(animMgr.getTexRect());
}

void Enemy1::stopMove()
{
	animMgr.pauseAnim();
}

void Enemy1::turnAround()
{
	if (animMgr.getCurrDir() == AnimDir::Left)
		animMgr.setCurrDir(AnimDir::Right);
	else
		animMgr.setCurrDir(AnimDir::Left);

}

void Enemy1::shoot(Player& target_)
{
	projectiles.push_back(std::make_unique<BusterShot>(this, Cfg::Textures::BusterShot, sf::IntRect{ sf::Vector2i{0,0},sf::Vector2i{24,14} }, sf::Vector2f{ 0.f,0.f }, sf::Vector2f{ 24.f,14.f }, sf::Vector2f{ getPosition().x + animMgr.getBulletPoint(AnimName::Idle, animMgr.getCurrDir(), (int)animMgr.getCurrIndex()).x, getPosition().y + animMgr.getBulletPoint(AnimName::Idle, animMgr.getCurrDir(), (int)animMgr.getCurrIndex()).y }));
	auto v = target_.getPosition() - worldPos;
	auto vectNorm = v.normalized();
	projectiles.back()->setVelocity(vectNorm * 200.f);
}


