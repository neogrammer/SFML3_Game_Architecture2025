
// ===== StandardEnemy.cpp =====
#include "StandardEnemy.h"

StandardEnemy::StandardEnemy(const sf::Texture& tex_) : DrawableObj(tex_),  _patrolTimer(0.f)
{
    setPos({ 600.f,600.f - 85.f - 64.f + 5.f });

    setVelocity({0.f,0.f}); // Bullet speed
    DrawableObj::initialize("GreenGuy.anim", { 49.f,85.f }, getPos(), Cfg::textures.get((int)Cfg::Textures::GreenGuy), { 0.f,0.f });
    setTexture(Cfg::textures.get((int)Cfg::Textures::PlayerAtlas));

    sf::SoundBuffer* snd1 = &Cfg::sounds.get((int)Cfg::Sounds::EnemyDie1);
    sf::SoundBuffer* snd2 = &Cfg::sounds.get((int)Cfg::Sounds::EnemyHurt1);
    sf::SoundBuffer* snd3 = &Cfg::sounds.get((int)Cfg::Sounds::HelmetHit);

    sounds.clear();
    sounds[Cfg::Sounds::EnemyDie1] = std::make_shared<sf::Sound>(*snd1);
    sounds[Cfg::Sounds::EnemyHurt1] = std::make_shared<sf::Sound>(*snd2);
    sounds[Cfg::Sounds::HelmetHit] = std::make_shared<sf::Sound>(*snd3);

    sounds.at(Cfg::Sounds::EnemyHurt1)->setVolume(100);

    
}

void StandardEnemy::update(float dt) {
    _patrolTimer += dt;

    if (_patrolTimer >= 2.f) {
        setVelocity({ -1.f * getVelocity().x, getVelocity().y });
        _patrolTimer = 0.f;
    }

    setPos(getPos() + (getVelocity() * dt));
    animHandler.update(dt);
   
}

std::string StandardEnemy::getStateName()
{
    return _fsm.getStateName();
}

void StandardEnemy::commit(float dt)
{
}

// ===== ProjectileObj.h =====

//#include "StandardEnemy.h"
//
//StandardEnemy::StandardEnemy() 
//	: DrawableObj{}
//    , animHandler{nullptr }
//	, sounds{}
//{
//	DrawableObj::initialize("GreenGuy.anim", { 49.f,85.f }, Cfg::Textures::GreenGuy, { 600.f,600.f - 85.f - 64.f + 5.f }, { 0.f,0.f });
//	setFrameOffset("Guarding", { 44.f,53.f });
//	m_frameDelays["Guarding"] = 0.13f;
//	m_loopDelays["Guarding"] = 1.f;
//	m_loopWaits = true;
//
//	setFrameOffset("Rising", { 44.f,53.f });
//
//	m_frameDelays["Rising"] = 0.09f;
//	m_loopDelays["Rising"] = 0.f;
//
//	setFrameOffset("AtJumpTop", { 44.f,53.f });
//
//	m_frameDelays["AtJumpTop"] = 0.08f;
//	m_loopDelays["AtJumpTop"] = 0.f;
//
//	setFrameOffset("Hit", { 44.f,53.f });
//
//	m_frameDelays["Hit"] = 0.03f;
//	m_loopDelays["Hit"] = 10.f;
//
//	setFrameOffset("Dead", { 44.f,53.f });
//
//	m_frameDelays["Dead"] = 0.08f;
//	m_loopDelays["Dead"] = 0.f;
//
//	setFrameOffset("Shooting", { 44.f,53.f });
//
//	m_frameDelays["Shooting"] = 2.f;
//	m_loopDelays["Shooting"] = 10.f;
//
//	setFrameOffset("StartedShooting", { 44.f,53.f });
//
//	m_frameDelays["StartedShooting"] = 2.f;
//	m_loopDelays["StartedShooting"] = 10.f;
//
//
//	setFrameOffset("Falling", { 44.f,53.f });
//
//	m_frameDelays["Falling"] = 0.08f;
//	m_loopDelays["Falling"] = 0.f;
//
//	setFrameOffset("Warning", { 44.f,53.f });
//
//	m_frameDelays["Warning"] = 0.08f;
//	m_loopDelays["Warning"] = 0.f;
//
//
//	this->m_facingRight = false;
//
//	sf::SoundBuffer* snd1 = &Cfg::sounds.get((int)Cfg::Sounds::EnemyDie1);
//	sf::SoundBuffer* snd2 = &Cfg::sounds.get((int)Cfg::Sounds::EnemyHurt1);
//	sf::SoundBuffer* snd3 = &Cfg::sounds.get((int)Cfg::Sounds::HelmetHit);
//
//	sounds.clear();
//	sounds[Cfg::Sounds::EnemyDie1] = std::make_shared<sf::Sound>(*snd1);
//	sounds[Cfg::Sounds::EnemyHurt1] = std::make_shared<sf::Sound>(*snd2);
//	sounds[Cfg::Sounds::HelmetHit] = std::make_shared<sf::Sound>(*snd3);
//
//	sounds.at(Cfg::Sounds::EnemyHurt1)->setVolume(100);
//
//	animHandler = std::make_shared<AnimHandler<FSM_GreenGuy, AnimVariant>>(&fsmEnemy, dynamic_cast<DrawableObj*>(this));
//}
//
//
//StandardEnemy::~StandardEnemy()
//{
//}
//
//void StandardEnemy::handleInput()
//{
//}
//
//FSM_GreenGuy& StandardEnemy::getFsm()
//{
//	return fsmEnemy;
//}
//
//void StandardEnemy::update(float dt_)
//{
//
//	animHandler.update(dt_);
//
//	if (justDied)
//	{
//		// set to be destroyed and dont update
//		dispatch(fsmEnemy, EventLifeDepleted{}); 
//		ChangeAnim("Dead");
//	}
//
//		if ((m_animName == "Guarding" || m_animName == "Idle") && firstRun)
//		{
//			idleElapsed = 0.f;
//			firstRun = false;
//			/*if (!secondComeThrough)
//			{
//				idleElapsed = 0.f;
//				firstRun = false;
//			}
//			else
//			{*/
//			// do nothing
//			/*int i = 0;
//			firstRun = false;*/
//			//	}
//		
//		}
//		
//		
//		if ((m_animName == "Guarding" || m_animName == "Idle") && !firstRun)
//		{
//			//if (secondComeThrough)
//		//	{
//		//		int i = 0;
//		//	}
//		//	else
//		//	{
//
//				idleElapsed += dt_;
//				if (idleElapsed >= idleDuration)
//				{
//				
//					firstRun = true;
//					dispatch(fsmEnemy, EventStartedShooting{});
//				}
//		//	}
//		}
//
//		if (m_animName == "StartedShooting")
//		{
//			int i = 0;
//		}
//
//
//
////		animHandler->update(dt_);
//
//		DrawableObj::update(dt_);
//
//		currMask = DetermineMaskColor(dt_);
//	
//}
//
//
//
//
//void StandardEnemy::render(sf::RenderWindow& wnd_)
//{
//	if (justDied) return;
//
//	if (m_animName != fsmEnemy.getStateName())
//		ChangeAnim(fsmEnemy.getStateName());
//
//	sf::Sprite spr(Cfg::textures.get((int)m_texture));
//	auto pos = GetPosition();
//	auto& offset = m_frameOffset[m_animName];
//	spr.setPosition({ pos.x - offset.x, pos.y - offset.y });
//	if (m_uniDirectional)
//	{
//		spr.setTextureRect(m_texFramesUni[m_animName].at(m_currentFrame));
//	}
//	else
//	{
//		if (m_facingRight)
//		{
//			spr.setTextureRect(m_texFramesRight[m_animName].at(m_currentFrame));
//		}
//		else
//		{
//			spr.setTextureRect(m_texFramesLeft[m_animName].at(m_currentFrame));
//		}
//	}
//	spr.setColor(currMask);
//
//	wnd_.draw(spr);
//	//animHandler.render(wnd_);
//	//DrawableObj::render(wnd_);
//}
//
//sf::Vector2i StandardEnemy::getTexRectSize()
//{
//	return (sf::Vector2i)DrawableObj::getTexRectSize();
//}
//
//Cfg::Textures StandardEnemy::getTextureID()
//{
//	return DrawableObj::getTextureID();
//}
//
//sf::Vector2i StandardEnemy::getTexPos()
//{
//	return (sf::Vector2i)DrawableObj::getTexRectPos();
//}
//
//sf::Color StandardEnemy::DetermineMaskColor(float dt_)
//{
//	if (takingDmg)
//	{
//		hitWaitElapsed += dt_;
//		if (hitWaitElapsed >= hitWaitDelay)
//		{
//			hitWaitElapsed = 0.f;
//			takingDmg = false;
//			dispatch(fsmEnemy, EventRecovered{});
//		}
//		return masked;
//	}
//	else
//	{
//		return normal;
//	}
//}
//
//bool StandardEnemy::GetHit(int power)
//{
//	
//	if (!takingDmg)
//	{
//		if (m_animName == "Guarding" || m_animName == "Idle")
//		{
//			
//			return false;
//		}
//		else {
//			sounds.at(Cfg::Sounds::EnemyHurt1)->play();
//			dispatch(fsmEnemy, EventHit{});
//			if (health <= 0)
//			{
//				dispatch(fsmEnemy, EventLifeDepleted{});
//			}
//			takingDmg = true;
//			hitWaitElapsed = 0.f;
//			health -= power;
//			if (health <= 0)
//			{
//				health = 0;
//				justDied = true;
//				this->sounds.at(Cfg::Sounds::EnemyDie1)->play();
//			}
//		}
//	}
//	return true;
//}
//
//sf::Color& StandardEnemy::getColorMask()
//{
//	return currMask;
//}