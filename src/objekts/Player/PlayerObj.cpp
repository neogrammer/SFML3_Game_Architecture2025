//#include "PlayerObj.h"
//#include <Tilemap/Tilemap.h>
//#include <GameObjects/Projectiles/BusterBullet.h>
//
//PlayerObj::PlayerObj() : DrawableObj{}
//, fsmPlayer{}
//, animHandler{ nullptr }
//, m_bullets{}
//, sounds{}
//{
//	DrawableObj::initialize("Player.anim", { 49.f,85.f }, Cfg::Textures::PlayerAtlas, { 400.f - 65.f,300.f - 80.f }, { 0.f,0.f });
//	setFrameOffset("Idle", { 44.f,43.f });
//	m_frameDelays["Idle"] = 0.13f;
//	m_loopDelays["Idle"] = 1.f;
//	m_loopWaits = true;
//
//	m_frameDelays["Moving"] = 0.09f;
//	m_loopDelays["Moving"] = 0.f;
//
//	m_frameDelays["StartedMoving"] = 0.08f;
//	m_loopDelays["StartedMoving"] = 0.f;
//
//	m_frameDelays["StartedShooting"] = 0.03f;
//	m_loopDelays["StartedShooting"] = 10.f;
//
//	m_frameDelays["Shooting"] = 2.f;
//	m_loopDelays["Shooting"] = 10.f;
//
//
//	m_frameDelays["MovingAndShooting"] = 0.08f;
//	m_loopDelays["MovingAndShooting"] = 0.f;
//
//	m_frameDelays["StartedMovingAndShooting"] = 0.08f;
//	m_loopDelays["StartedMovingAndShooting"] = 0.f;
//	m_frameDelays["StartedJump"] = 0.6f;
//	m_loopDelays["StartedJump"] = 10.f;
//	m_frameDelays["Rising"] = 0.6f;
//	m_loopDelays["Rising"] = 10.f;
//	m_frameDelays["AtJumpTop"] = 0.6f;
//	m_loopDelays["AtJumpTop"] = 10.f;
//	m_frameDelays["Falling"] = 0.6f;
//	m_loopDelays["Falling"] = 10.f;
//	m_frameDelays["Landing"] = 0.6f;
//	m_loopDelays["Landing"] = 10.f;
//	m_frameDelays["StartedJumpAndShooting"] = 0.6f;
//	m_loopDelays["StartedJumpAndShooting"] = 10.f;
//	m_frameDelays["RisingAndShooting"] = 0.6f;
//	m_loopDelays["RisingAndShooting"] = 10.f;
//	m_frameDelays["AtJumpTopAndShooting"] = 0.6f;
//	m_loopDelays["AtJumpTopAndShooting"] = 10.f;
//	m_frameDelays["FallingAndShooting"] = 0.6f;
//	m_loopDelays["FallingAndShooting"] = 10.f;
//	m_frameDelays["LandingAndShooting"] = 0.6f;
//	m_loopDelays["LandingAndShooting"] = 10.f;
//
//	m_bullets.clear();
//
//	sounds.clear();
//
//	sf::SoundBuffer* snd1 = &Cfg::sounds.get((int)Cfg::Sounds::BustershotCharged);
//	sf::SoundBuffer* snd2 = &Cfg::sounds.get((int)Cfg::Sounds::BustershotNormal);
//	sf::SoundBuffer* snd3 = &Cfg::sounds.get((int)Cfg::Sounds::XDie);
//	sf::SoundBuffer* snd4 = &Cfg::sounds.get((int)Cfg::Sounds::XHurt);
//	sf::SoundBuffer* snd5 = &Cfg::sounds.get((int)Cfg::Sounds::XCharging);
//	sf::SoundBuffer* snd6 = &Cfg::sounds.get((int)Cfg::Sounds::XJump);
//	sf::SoundBuffer* snd7 = &Cfg::sounds.get((int)Cfg::Sounds::XLand);
//
//
//	sounds[Cfg::Sounds::BustershotCharged] = std::make_shared<sf::Sound>(*snd1);
//	sounds[Cfg::Sounds::BustershotNormal] = std::make_shared<sf::Sound>(*snd2);
//	sounds[Cfg::Sounds::XDie] = std::make_shared<sf::Sound>(*snd3);
//	sounds[Cfg::Sounds::XHurt] = std::make_shared<sf::Sound>(*snd4);
//	sounds[Cfg::Sounds::XCharging] = std::make_shared<sf::Sound>(*snd5);
//	sounds[Cfg::Sounds::XJump] = std::make_shared<sf::Sound>(*snd6);
//	sounds[Cfg::Sounds::XLand] = std::make_shared<sf::Sound>(*snd7);
//
//	sounds.at(Cfg::Sounds::BustershotNormal)->setVolume(100);
//	sounds.at(Cfg::Sounds::XJump)->setVolume(100);
//	sounds.at(Cfg::Sounds::XLand)->setVolume(100);
//
//	dispatch(fsmPlayer, EventFell{});
//	ChangeAnim("Falling");
//
//	animHandler = std::make_shared<AnimHandler<FSM_Player, AnimVariant>>(&fsmPlayer, dynamic_cast<DrawableObj*>(this));
//};
//	
//
//std::shared_ptr<Projectile> PlayerObj::CreateBullet()
//{
//	std::shared_ptr<Projectile> project;
//	if(m_animName == "Shooting" || m_animName == "StartedShooting")
//		project = std::make_shared<BusterBullet>(sf::Vector2f( (m_facingRight ? sf::Vector2f{46.f,17.f} : sf::Vector2f{-20.f , 16.f }) + GetPosition()) );
//	else if (m_animName == "MovingAndShooting")
//		project = std::make_shared<BusterBullet>(sf::Vector2f((m_facingRight ? sf::Vector2f{ 66.f,12.f } : sf::Vector2f{ -40.f , 12.f }) + GetPosition()));
//	else if (m_animName == "StartedJumpAndShooting" || m_animName == "RisingAndShooting" || m_animName == "AtJumpTopAndShooting" || m_animName == "FallingAndShooting" || m_animName == "LandingAndShooting")
//		project = std::make_shared<BusterBullet>(sf::Vector2f((m_facingRight ? sf::Vector2f{ 50.f,13.f + (GetVelocity().y * 0.0166f) } : sf::Vector2f{ -27.f , 13.f + (GetVelocity().y * 0.0166f) })) + GetPosition());
//	else
//		project = std::make_shared<BusterBullet>(sf::Vector2f((m_facingRight ? sf::Vector2f{ 0.f,0.f } : sf::Vector2f{ 0.f , 0.f }) + GetPosition()));
//
//	dynamic_cast<BusterBullet*>(project.get())->SetVelocity({ (m_facingRight ? 700.f : -700.f ), 0.f});
//	return project;
//}
//
//PlayerObj::~PlayerObj()
//{
//}
//
//void PlayerObj::handleInput()
//{
//}
//
//void PlayerObj::UpdateDPad(bool* pressed)
//{
//	upPressed = pressed[0];
//	downPressed = pressed[1];
//	leftPressed = pressed[2];
//	rightPressed = pressed[3];
//}
//
//std::vector<std::shared_ptr<Projectile>>& PlayerObj::getBullets()
//{
//	// TODO: insert return statement here
//	return m_bullets;
//}
//
//FSM_Player& PlayerObj::getFsm()
//{
//	return fsmPlayer;
//}
//
//void PlayerObj::update(float dt_)
//{
//
//	animHandler.update(dt_);
//		// DrawableObj just renders the updated sprite later
//
//
//	if (m_onGround == true && ((fsmPlayer.getStateName() == "Landing" && m_animName == "Landing") || (fsmPlayer.getStateName() == "LandingAndShooting" && m_animName == "LandingAndShooting")))
//	{
//		dispatch(fsmPlayer, EventLanding2{});
//	}
//
//
//	auto* drO = dynamic_cast<DrawableObj*>(this);
//
//	if ((!leftPressed && !rightPressed) || (leftPressed && rightPressed))
//	{
//		SetVelocity({ 0.f,GetVelocity().y });
//		if (m_animName != "Idle")
//		{
//			//			ChangeAnim("Idle");
//			dispatch(fsmPlayer, EventStoppedMoving{});
//		}
//	}
//	else
//	{
//		if (rightPressed)
//		{
//			SetVelocity({ 350.f, GetVelocity().y });
//			drO->m_facingRight = true;
//			if (m_animName != "Moving" && m_animName == "StartedMoving" && m_currentFrame == m_texFramesRight.at("StartedMoving").size() - 1)
//			{
//				dispatch(fsmPlayer, EventMoveStartFinished{});
//			}
//			else if (m_animName != "Moving" && m_animName != "StartedMoving")
//			{
//				dispatch(fsmPlayer, EventStartedMoving{});
//			}
//		}
//		if (leftPressed)
//		{
//			SetVelocity({ -350.f, GetVelocity().y });
//			drO->m_facingRight = false;
//			if (m_animName != "Moving" && m_animName == "StartedMoving" && m_currentFrame == m_texFramesRight.at("StartedMoving").size() - 1)
//			{
//				dispatch(fsmPlayer, EventMoveStartFinished{});
//			}
//			else if (m_animName != "Moving" && m_animName != "StartedMoving")
//			{
//				dispatch(fsmPlayer, EventStartedMoving{});
//			}
//		}
//	}
//
//	static float shootSetupElapsed = 0.f;
//	static bool shootSetupDone = false;
//	static float shootWaitElapsed = 0.f;
//	static bool justStoppedShooting = false;
//	static float shootElapsed = 0.f;
//
//	auto  it = m_bullets.begin();
//	while (it != m_bullets.end()) {
//		if (!(*it)->isAlive()) {
//			it = m_bullets.erase(it);
//		}
//		else
//		{
//			it++;
//		}
//	}
//	static bool firstTimeShot = true;
//	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Enter))
//	{
//
//	
//		if (m_animName == "Idle" || m_animName == "Moving" || (shootElapsed >= 1.f && m_animName == "Shooting"))
//		{
//
//			
//			dispatch(fsmPlayer, EventStartedShooting{});
//			shootSetupElapsed = 0.f;
//			shootSetupDone = false;
//			shootWaitElapsed = 0.f;
//			justStoppedShooting = false;
//			shootElapsed = 0.f;
//		}
//		else	if(!shootSetupDone)
//		{
//
//
//
//			shootSetupElapsed += dt_;
//
//			if ((firstTimeShot &&  (m_animName == "StartedJumpAndShooting" || m_animName == "MovingAndShooting" || m_animName == "StartedShooting")) || (m_animName == "Shooting") || (m_animName == "RisingAndShooting") || (m_animName == "AtJumpTopAndShooting") || (m_animName == "FallingAndShooting") || (m_animName == "LandingAndShooting") || (m_animName == "MovingAndShooting"))
//			{
//				if (firstTimeShot)
//					firstTimeShot = false;
//
//				if (m_bullets.size() < this->MAXBULLETS)
//				{
//					sounds.at(Cfg::Sounds::BustershotNormal)->play();
//					m_bullets.push_back(CreateBullet());
//				}
//				dispatch(fsmPlayer,  EventShootSetupDone{});
//				shootSetupDone = true;
//				shootElapsed = 0.f;
//				shootWaitElapsed = 0.f;
//				shootSetupElapsed = 0.f;
//				// FIRE BULLET
//			}
//		}
//		else
//		{
//		     	dispatch(fsmPlayer, EventStartedShooting{});
//
//				// is shooting already and key is held down
//				shootElapsed += dt_;
//				if (shootElapsed > 0.3f) //fireBulletWait)
//				{
//					shootElapsed = 0.f;
//					shootWaitElapsed = 0.f;
//
//					if (m_animName.find("Shooting") != std::string::npos)
//					{
//						// FIRE BULLET
//						std::cout << "Fire bullet" << std::endl;
//						//m_bullets.push_back(CreateBullet());
//					}
//				}
//
//		}
//	}
//	else
//	{
//		shootElapsed = 1.f;
//		shootSetupDone = false;
//		firstTimeShot = true;
//		if ((m_animName == "Shooting") || (m_animName == "StartedJumpAndShooting") || (m_animName == "RisingAndShooting") || (m_animName == "AtJumpTopAndShooting") || (m_animName == "FallingAndShooting") || (m_animName == "LandingAndShooting") || (m_animName == "MovingAndShooting"))
//		{
//			shootWaitElapsed += dt_;
//			if (shootWaitElapsed > 0.35f)
//			{
//				{
//					shootWaitElapsed = 0.f;
//					dispatch(fsmPlayer, EventStoppedShooting());
//					
//				}
//			}
//		}
//		else
//		{
//			dispatch(fsmPlayer, EventShootSetupDone());
//		}
//	}
//
//	if (!m_onGround)
//	{
//		if (m_animName == "StartedJump" || m_animName == "StartedMovingAndJumping" || m_animName == "StartedJumpAndShooting")
//		{
//			if (m_currentFrame = 1)
//			{
//				dispatch(fsmPlayer, EventJumpStartFinished{});
//				dispatch(fsmPlayer, EventMoveStartFinished{});
//			}
//
//		}
//		else if ((m_animName != "StartedJump") && rising == true && m_animName != "StartedMovingAndJumping" && m_animName != "StartedJumpAndShooting")
//		{
//			rising = false;
//		}
//		else if (m_animName == "Rising" || m_animName == "RisingAndShooting")
//		{
//
//			if (GetVelocity().y < 50.f)
//			{
//				dispatch(fsmPlayer, EventNearingTopOfJump{});
//			}
//		}
//		else if (m_animName == "AtJumpTop" || m_animName == "AtJumpTopAndShooting")
//		{
//			if (GetVelocity().y > 10.f)
//				dispatch(fsmPlayer, EventReachedJumpHeight{});
//		}
//	}
//	if (m_onGround && m_animName == "Falling" || m_animName =="FallingAndShooting")
//	{
//		dispatch(fsmPlayer, EventLanding2{});
//
//	}
//
//
//	if (m_onGround)
//	{
//		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space))
//		{
//			SetVelocity({ GetVelocity().x, -1200.f });
//			m_onGround = false;
//			dispatch(fsmPlayer, EventStartedJumping{});
//			rising = true;
//		}
//	}
//	else
//	{
//		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Enter))
//		{
//			dispatch(fsmPlayer, EventStartedShooting{});
//		}
//	}
//	
//
//	if (!this->m_onGround)
//		AdjustVelocity({ 0.f, GRAVITY * dt_ });
//	
//	if (GetVelocity().y > 1600.f)
//		SetVelocity({ GetVelocity().x, 1600.f });
//
//	//animHandler->update(dt_);
//
//
//
//
//	// FSM updates based on input/physics/etc.
//	std::string nextAnim = fsmPlayer.getStateName();
//
//	// Animation handler handles the rest
//	if (animHandler.getCurrentAnim() != nextAnim) {
//		animHandler.changeAnim(nextAnim);
//	}
//
//
//	DrawableObj::update(dt_);
//
//	animHandler.update(dt);
//}
//
//			/*if (m_animName == "Idle")
//			{
//				dispatch(fsmPlayer, EventStartedShooting{});
//				shootSetupElapsed = 0.f;
//			}
//			else if (m_animName == "Shooting")
//			{
//				int i = 0;
//			}
//			else
//			{
//				dispatch(fsmPlayer, EventStartedShooting{}, EventShootSetupDone());
//				shootSetupElapsed = 0.51f;
//			}
//
//		}
//		else
//		{
//			shootSetupElapsed += dt_;
//
//			if (shootSetupElapsed >= 0.5f)
//			{
//				if (m_animName != "Shooting")
//				{
//					dispatch(fsmPlayer, EventStartedShooting{}, EventShootSetupDone{});
//				}
//			}
//		}*/
//	
//	
//	  /*	if (m_animName != "Idle")
//		{
//			dispatch(fsmPlayer, EventStoppedShooting{});
//		}*/
//    
//
//	//if (this->m_onGround)
//	//{
//	//	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Enter))
//	//}
//
//	
//
//void PlayerObj::render(sf::RenderWindow& wnd_)
//{
//	if (m_animName != fsmPlayer.getStateName())
//		ChangeAnim(fsmPlayer.getStateName());
//
//
//	//animHandler.render(wnd_);
//	DrawableObj::render(wnd_);
//
//
//}
//
//sf::Vector2i PlayerObj::getTexRectSize()
//{
//	return (sf::Vector2i)DrawableObj::getTexRectSize();
//}
//
//Cfg::Textures PlayerObj::getTextureID()
//{
//	return DrawableObj::getTextureID();
//}
//
//sf::Vector2i PlayerObj::getTexPos()
//{
//	return (sf::Vector2i)DrawableObj::getTexRectPos();
//}
//
//void PlayerObj::SetOnGround(bool cond_)
//{
//	if (cond_ == true)
//	{
//		sounds.at(Cfg::Sounds::XLand)->play();
//	}
//	m_onGround = cond_;
//}
//


// ===== PlayerObj.cpp =====
#include "PlayerObj.h"
#include <Physics/Physics.h>
#include <core/IO/Input.h>
#include <core/Resources/Cfg.h>

#include <Animation/AnimHandler.h>
PlayerObj::PlayerObj() : DrawableObj(Cfg::textures.get((int)Cfg::Textures::PlayerAtlas))
{
    

    initialize("Player.anim", { 49.f,85.f }, { 400.f - 65.f,300.f - 80.f }, Cfg::textures.get((int)Cfg::Textures::PlayerAtlas), { 0.f,0.f });
    setTexture(Cfg::textures.get((int)Cfg::Textures::PlayerAtlas));

    m_bullets.clear();

   // sounds.clear();

    sf::SoundBuffer* snd1 = &Cfg::sounds.get((int)Cfg::Sounds::BustershotCharged);
    sf::SoundBuffer* snd2 = &Cfg::sounds.get((int)Cfg::Sounds::BustershotNormal);
    sf::SoundBuffer* snd3 = &Cfg::sounds.get((int)Cfg::Sounds::XDie);
    sf::SoundBuffer* snd4 = &Cfg::sounds.get((int)Cfg::Sounds::XHurt);
    sf::SoundBuffer* snd5 = &Cfg::sounds.get((int)Cfg::Sounds::XCharging);
    sf::SoundBuffer* snd6 = &Cfg::sounds.get((int)Cfg::Sounds::XJump);
    sf::SoundBuffer* snd7 = &Cfg::sounds.get((int)Cfg::Sounds::XLand);


    sounds[Cfg::Sounds::BustershotCharged] = std::make_shared<sf::Sound>(*snd1);
    sounds[Cfg::Sounds::BustershotNormal] = std::make_shared<sf::Sound>(*snd2);
    sounds[Cfg::Sounds::XDie] = std::make_shared<sf::Sound>(*snd3);
    sounds[Cfg::Sounds::XHurt] = std::make_shared<sf::Sound>(*snd4);
    sounds[Cfg::Sounds::XCharging] = std::make_shared<sf::Sound>(*snd5);
    sounds[Cfg::Sounds::XJump] = std::make_shared<sf::Sound>(*snd6);
    sounds[Cfg::Sounds::XLand] = std::make_shared<sf::Sound>(*snd7);

    sounds.at(Cfg::Sounds::BustershotNormal)->setVolume(100);
    sounds.at(Cfg::Sounds::XJump)->setVolume(100);
    sounds.at(Cfg::Sounds::XLand)->setVolume(100);
    
    dispatch(_fsm, EventFell{});
    animHandler.changeAnim("Falling");

}

std::vector<std::weak_ptr<ProjectileObj>> PlayerObj::getBullets()
{
    std::vector<std::weak_ptr<ProjectileObj> > tmp;
    tmp.clear();
    tmp.reserve(m_bullets.size());

    for (auto& b : m_bullets)
    {
        tmp.push_back(b);
    }
    return tmp;
}

void PlayerObj::updateState() {
    // Get input/physics contextand change FSM state

    std::string animNameOld = _fsm.getStateName();

    if (animNameOld == "Landing")
    {
        _onGround = true;
    }

    if (_onGround && getVelocity().x != 0.f) {
        if (animNameOld != "Moving" && animNameOld != "StartedMoving" && animNameOld != "MovingAndShooting" && animNameOld != "StartedMovingAndShooting")
         dispatch(_fsm, EventStartedMoving{});
    }
    
    if (!_onGround) {
        if (animNameOld != "Landing")
             dispatch(_fsm, EventFell{});

    }

    if (abs(getVelocity().x) < 0.1f)
    {
        if (animNameOld != "Idle")
            dispatch(_fsm, EventStoppedMoving{});

    }

    // Hook FSM into AnimHandler
    if (_fsm.getStateName() != animNameOld)
        animHandler.changeAnim(_fsm.getStateName());
}

void PlayerObj::commit(float dt)
{
}

void PlayerObj::update(float dt) {
    auto vel = handleInput();           // Input + velocity logic
    //applyPhysics(dt);        // Physics + collisions
    
    updateState();           // FSM + AnimHandler


    if (!_onGround)
        vel.y = 600.f;
    setPos(getPos() + (vel * dt));



    animHandler.update(dt);
  
}

void PlayerObj::setOnGround(bool cond_)
{
    _onGround = cond_;
}

bool PlayerObj::isOnGround() const
{
    return _onGround;
}



sf::Vector2f PlayerObj::handleInput() {
    sf::Vector2f vel = getVelocity();

    if (Input::isKeyPressed(Input::Key::Left)) {
        vel.x = -100.f;
    }
    if (Input::isKeyPressed(Input::Key::Right)) {
        vel.x = 100.f;
        
    }


    if (Input::isKeyJustPressed(Input::Key::Jump)) {
        vel.y = -400.f;
    }
    
    return vel;
 }
    // FSM triggers animation changes here (not implemented in this sample)


void PlayerObj::applyPhysics(float dt) {
    setPos(getPos() + (getVelocity() * dt));
}