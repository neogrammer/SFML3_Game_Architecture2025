// DrawableObj =  Drawable GameObject
//  Justin Layne Hardee
//  copyright 3-7-2025
// MIT liscense
// Use it, abuse it, don't get used to ti

// DrawableObj.h
// DrawableObj.h

// ===== DrawableObj.h =====
#pragma once
#include "GObj.h"
#include <Animation/AnimHandler.h>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <core/Resources/Cfg.h>
class TileObj;
class DrawableObj : public GObj 
{
    bool _initialized{ false };
  
public:
    DrawableObj();
    DrawableObj(const sf::Texture& tex_);

    DrawableObj(const DrawableObj& o);
    DrawableObj& operator=(const DrawableObj& o);
    DrawableObj(DrawableObj&& o);
    DrawableObj& operator=(DrawableObj&& o);


    virtual ~DrawableObj() = default;

    virtual void render(sf::RenderWindow& window);
    inline bool isUni() { return animHandler.isUni(); }

    // Texture handling
    void setTexture(const sf::Texture& texture, bool resetRect_ = false);
    sf::Texture& getTexture();
    void setTexRect(const sf::IntRect& rect);
    const sf::IntRect& getTexRect() const; // <-- Added gettet
    void setAnimName(std::string animName_);
    void setFacingRight(bool cond_);
    bool isFacingRight() const;
    void setFrameDelay(float frameDelay_, std::string animName = "Current");
    void setFrameOffsets(sf::Vector2i off_, std::string animName = "Current");
    sf::Vector2i getFrameOffsets(std::string animName = "Current");
    float getFrameDelay(std::string animName = "Current");

    

  

protected:
    inline bool isInitialized() { return _initialized; };
    inline void setInitialized(bool cond_ = true) { _initialized = cond_; }
    // these are called by the derived class
    void initialize(const std::string& filepath_, sf::Vector2f size_ = { 50.f,50.f }, sf::Vector2f pos_ = { 0.f,0.f }, const sf::Texture& tex_ = Cfg::textures.get((int)Cfg::Textures::Invariant), sf::Vector2f vel_ = sf::Vector2f{ 0.f,0.f });
    void initializeAsTile(sf::IntRect rect_, sf::Vector2f pos_ = { 0.f,0.f }, const sf::Texture& tex_ = Cfg::textures.get((int)Cfg::Textures::Invariant), const sf::Vector2i& offs_ = sf::Vector2i{0,0});

    AnimHandler animHandler;
    sf::Sprite _sprite{ Cfg::textures.get((int)Cfg::Textures::Invariant) };
};


//class DrawableObj : public GObj
//{
//
//	template<class FSM_TYPE, class STATE_VAR>
//	friend class AnimHandler;
//protected:
//	bool m_playing{ true };
//	bool m_loopWaits{ false };
//	bool m_looping{ true };
//
//	bool m_uniDirectional{ false };
//	
//
//	std::unordered_map<std::string, float> m_startDelays{};
//	std::unordered_map<std::string, float> m_loopDelays{};
//	
//	std::unordered_map<std::string, float> m_frameDelays{};
//
//	std::string recoveryAnim = "Idle";
//
//	// Animation Parameters
//	std::vector<sf::IntRect>* m_anim{ nullptr };
//	std::string m_animName{ "None" };
//	size_t m_currentFrame{ (size_t)0 };
//	Cfg::Textures m_texture{ Cfg::Textures::Invariant };
//	/// <summary>
//	/// each animation has a specific point from the tl corner where the image will be displayed to the tl corner of the objects bounding box, in world coords, the frameOffset, one per animation. 
//	/// .  can be outside of texture bounds
//	/// </summary>
//	std::unordered_map<std::string, sf::Vector2f> m_frameOffset{};
//	// default position to 0.f,0.f and make size mandatory and size will be constant per animation
//	/// <summary>
//	/// position and size of animation in the sprite atlas,
//	/// </summary>
//	std::unordered_map<std::string, std::vector<sf::IntRect>> m_texFramesRight{};
//	std::unordered_map<std::string, std::vector<sf::IntRect>> m_texFramesLeft{};
//	std::unordered_map<std::string, std::vector<sf::IntRect>> m_texFramesUni{};
//	
//protected:
//	void initialize(const std::string& filepath_, sf::Vector2f size_ = { 50.f,50.f }, Cfg::Textures tex_ = Cfg::Textures::Invariant, sf::Vector2f pos_ = { 0.f,0.f }, sf::Vector2f vel_ = sf::Vector2f{ 0.f,0.f });
//	void initializeAsTile(sf::IntRect rect_, Cfg::Textures tex_ = Cfg::Textures::Invariant, sf::Vector2f pos_ = { 0.f,0.f });
//
//public:
//	DrawableObj();
//	virtual ~DrawableObj() override;
//	
//	DrawableObj(const DrawableObj&);
//	DrawableObj& operator=(const DrawableObj&);
//	DrawableObj(DrawableObj&&) = default;
//	DrawableObj& operator=(DrawableObj&&)=default;
//	bool m_facingRight{ true };
//
//
//	friend bool operator==(DrawableObj& lhs_, DrawableObj& rhs_);
//
//	void update(float dt_) override;
//	virtual void render(sf::RenderWindow& wnd_);
//
//	void ChangeAnim(const std::string& animName);
//	void animate();
//
//	inline size_t ID() const { return GObj::ID(); }
//	void SetSize(const sf::Vector2f& size_);
//	inline sf::Vector2f GetSize() const {
//		return GObj::GetSize();
//	};
//
//	inline int GetCurrentFrame()
//	{
//		return (int)m_currentFrame;
//	};
//	/// <summary>
//	/// Adjust world coordinates a set amount (amount should include the game's frame time 
//	/// </summary>
//	void AdjustPosition(const sf::Vector2f& amt_);
//	/// <summary>
//	/// Set to specific coordinate in world coordinates
//	/// </summary>
//	void SetPosition(const sf::Vector2f& pos_);
//	inline sf::Vector2f GetPosition() const {
//		return GObj::GetPosition();
//	};
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
//		return GObj::GetVelocity();
//	};
//
//	sf::Vector2f getTexRectSize();
//	Cfg::Textures getTextureID();
//	sf::Vector2f getTexRectPos();
//	void setFrameOffset(std::string animName_, sf::Vector2f offset_);
//	sf::Vector2f getFrameOffset();
//
//};