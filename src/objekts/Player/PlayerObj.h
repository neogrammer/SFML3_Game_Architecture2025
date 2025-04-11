
// ===== PlayerObj.h =====
#pragma once
#include <memory>
#include <utility>
#include <SFML/Audio.hpp>
#include <GameObjects/Projectiles/Projectile.h>
#include <FSM/PlayerAnimFSM.h>

class PlayerObj : public DrawableObj {
public:
    PlayerObj();
    virtual ~PlayerObj() = default;
    std::vector<std::weak_ptr<ProjectileObj> > getBullets();
    void update(float dt) override;
    const int MAXBULLETS{ 5 };
    void setOnGround(bool cond_);
    bool isOnGround() const;

    template <class EventType>
    void handleEvent(EventType evt_)
    {
        dispatch(_fsm, evt_);
    };
private:
    sf::Vector2f handleInput();
    void applyPhysics(float dt);
    void updateState();

    std::vector<std::shared_ptr<ProjectileObj>> m_bullets;
    std::unordered_map<Cfg::Sounds, std::shared_ptr<sf::Sound>> sounds;
    bool _onGround{ false };
    // Your FSM is specific to the player
    FSM_Player _fsm;

    // Inherited via DrawableObj
    void commit(float dt) override;
};


//#pragma once
//#include <GameObjects/DrawableObj.h>
//#include <Tilemap/TilemapTypes.h>
//#include <FSM/PlayerAnimFSM.h>
//
//#include <Animation/AnimHandler.h>
//#include <memory>
//#include  <utility>
//class Tilemap;
//class TileObj;
//class Projectile;
//class PlayerObj : public DrawableObj
//{
//	const int MAXBULLETS = 5;
//	bool m_onGround{ false };
//	const int GRAVITY{ 3200 };
//	bool rising{ false };
//	FSM_Player fsmPlayer;
//	bool leftPressed{ false }, rightPressed{ false }, upPressed{ false }, downPressed{ false };
//
//	std::vector<std::shared_ptr<Projectile>> m_bullets;
//
//	std::unordered_map<Cfg::Sounds, std::shared_ptr<sf::Sound>> sounds;
//
//public:
//	
//	PlayerObj(); 
//	virtual ~PlayerObj() override;
//
//	PlayerObj(const PlayerObj&)=delete;
//	PlayerObj& operator=(const PlayerObj&)=delete;
//	PlayerObj(PlayerObj&&)=delete;
//	PlayerObj& operator=(PlayerObj&&)=delete;
//
//	void handleInput();
//	std::shared_ptr<Projectile> CreateBullet();
//	void UpdateDPad(bool* pressed);
//	std::vector<std::shared_ptr<Projectile>>& getBullets();
//
//
//	FSM_Player& getFsm();
//
//	template<typename EVT>
//	void disp(EVT event)
//	{
//
//		dispatch(fsmPlayer, event);
//	};
//	void update(float dt_) override final;
//
//	virtual void render(sf::RenderWindow& wnd_) override final;
//
//	sf::Vector2i getTexRectSize();
//	Cfg::Textures getTextureID();
//	sf::Vector2i getTexPos();
//
//	void SetOnGround(bool cond_);
//	inline bool GetOnGround()
//	{
//		return m_onGround;
//	};
//};
//
