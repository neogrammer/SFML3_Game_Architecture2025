// GObj = GameObject
//  Justin Layne Hardee
// GObj.h
// ===== GObj.h =====
#pragma once
#include <SFML/System/Vector2.hpp>

class GObj 
{
    static int _numObjects;
    int _id{ ++_numObjects };

public:
    GObj();
    virtual ~GObj() = default;
    GObj(const GObj& o);
    GObj& operator=(const GObj& o);
    GObj(GObj&& o);
    GObj& operator=(GObj&& o);

    
    int getID() const;

    static int getNumObjects()
    {
        return _numObjects;
    };

    virtual void update(float dt) = 0;
    virtual void commit(float dt) = 0;


    const sf::Vector2f& getPos() const;
    void setPos(sf::Vector2f pos_);
    const sf::Vector2f& getSize()const;
    void setSize(sf::Vector2f size_);
    const sf::Vector2f& getVelocity() const;
    void setVelocity(sf::Vector2f velocity_);
    const sf::Vector2f& getPrevPos() const;
    void setPrevPos(sf::Vector2f prevPos_);

protected:
    void initialize(sf::Vector2f size_, sf::Vector2f pos_, sf::Vector2f vel_ = sf::Vector2f{ 0.f,0.f });

 


private:
    sf::Vector2f _worldPosition;
    sf::Vector2f _prevPosition;
    sf::Vector2f _size;

    sf::Vector2f _velocity; // Moved here for universal access



};

/// <summary>
/// Contains world properties for every entity - or "thing" - in the game
///// </summary>
//class GObj
//{
//
//	static size_t totalGameObjects;
//
//    size_t m_id{ ++totalGameObjects };
//	sf::Vector2f m_size{ 0.f,0.f };
//	sf::Vector2f m_position{ 0.f,0.f };
//	sf::Vector2f m_velocity{ 0.f,0.f };
//	sf::Vector2f m_prevPosition{ 0.f,0.f };
//	sf::Vector2f m_prevMoveAmt{ 0.f,0.f };
//protected:
//	// access propogates to child but does not bleed out
//	inline sf::Vector2f& getSizeRef() { return m_size; }
//	inline sf::Vector2f& getPositionRef() { return m_position; }
//	inline sf::Vector2f& getVelocityRef() { return m_velocity; }
//	inline sf::Vector2f& getprevPositionRef() { return m_prevPosition; }
//	inline sf::Vector2f& getPrevMoveAmtRef() { return m_prevMoveAmt; }
//	/// <summary>
//	/// Call once per frame, after updates, and before collision detection/resolution
//	/// </summary>
//	void tick(float dt_);
//
//	void initialize(sf::Vector2f size_, sf::Vector2f pos_, sf::Vector2f vel_ = sf::Vector2f{ 0.f,0.f });
//public:
//	GObj();
//	virtual ~GObj();
//
//	GObj(const GObj&) = default;
//	GObj& operator=(const GObj&) = default;
//	GObj(GObj&&) = default;
//	GObj& operator=(GObj&&) = default;
//
//	friend bool operator==(GObj& lhs_, GObj& rhs_);
//
//	virtual void update(float dt_) = 0;
//
//	inline size_t ID() const { return m_id; }
//	void SetSize(const sf::Vector2f& size_);
//	inline sf::Vector2f GetSize() const {
//		return m_size;
//	}
//	/// <summary>
//	/// Adjust world coordinates a set amount (amount should include the game's frame time 
//	/// </summary>
//	void AdjustPosition(const sf::Vector2f& amt_);
//	/// <summary>
//	/// Set to specific coordinate in world coordinates
//	/// </summary>
//	void SetPosition(const sf::Vector2f& pos_);
//	inline sf::Vector2f GetPosition() const {
//		return m_position;
//	}
//	/// <summary>
//	/// (acceleration * frametime) passed in, gets added to the velocity
//	/// </summary>
//	/// <param name="amt"></param>
//	void AdjustVelocity(const sf::Vector2f& amt_);
//	/// <summary>
//	/// Set specific velocity
//	/// </summary>
//	/// <param name="vel_"></param>
//	void SetVelocity(const sf::Vector2f& vel_);
//	inline sf::Vector2f GetVelocity() const {
//		return m_velocity;
//	}
//};