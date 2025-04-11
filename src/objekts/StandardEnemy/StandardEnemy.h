
// ===== StandardEnemy.h =====
#pragma once
#include <GameObjects/DrawableObj.h>
#include <FSM/GreenGuyAnimFSM.h>

class StandardEnemy : public DrawableObj {
public:
    StandardEnemy(const sf::Texture& tex_);
    virtual ~StandardEnemy() = default;

    void update(float dt) override;
    std::string getStateName();
    std::unordered_map<Cfg::Sounds, std::shared_ptr<sf::Sound>> sounds;
private:
    float _patrolTimer;
    FSM_GreenGuy _fsm;


    // Inherited via DrawableObj
    void commit(float dt) override;

};


//#pragma once
//#include <GameObjects/DrawableObj.h>
//#include <Animation/AnimHandler.h>
//#include <core/Resources/Cfg.h>
//#include <memory>
//#include <utility>
//#include <FSM/GreenGuyAnimFSM.h>
//
//class StandardEnemy : public DrawableObj
//{
//	FSM_GreenGuy fsmEnemy;
//
//	//std::shared_ptr<AnimHandler<FSM_GreenGuy, AnimVariant>> animHandler;
//	int health{3}, healthmax{3};
//	sf::Color masked{ sf::Color(0, 0, 0,255) };
//	sf::Color normal{ sf::Color::White };
//	bool firstRun{ true };
//	bool takingDmg{ false };
//	float hitWaitDelay{0.05f};
//	float hitWaitElapsed{0.f};
//	bool justDied{ false };
//	sf::Color currMask{ normal };
//	sf::Clock idleTimer{};
//	float idleDuration{ 3.f };
//	float idleElapsed{ 0 };
//public:
//	std::unordered_map<Cfg::Sounds, std::shared_ptr<sf::Sound>> sounds;
//
//	StandardEnemy();
//	virtual ~StandardEnemy() override;
//
//	StandardEnemy(const StandardEnemy&) = delete;
//	StandardEnemy& operator=(const StandardEnemy&) = delete;
//	StandardEnemy(StandardEnemy&&) = delete;
//	StandardEnemy& operator=(StandardEnemy&&) = delete;
//
//	void handleInput();
//
//	FSM_GreenGuy& getFsm();
//	void update(float dt_) override final;
//	virtual void render(sf::RenderWindow& wnd_) override final;
//
//	sf::Vector2i getTexRectSize();
//	Cfg::Textures getTextureID();
//	sf::Vector2i getTexPos();
//	sf::Color DetermineMaskColor(float dt_);
//	bool GetHit(int power);
//
//	sf::Color& getColorMask();
//	
//
//
//};
//
