

// ===== AnimHandler.h =====
#pragma once
#include <SFML/Graphics/Rect.hpp>
#include <SFML/System/Vector2.hpp>
#include <unordered_map>
#include <string>
#include <vector>

class AnimHandler {
private:
    std::size_t _currIndex{ 0 };

    struct Animation {
        std::vector<sf::IntRect> framesLeft;
        std::vector<sf::IntRect> framesRight;
        std::vector<sf::IntRect> framesUni;

        std::vector<sf::Vector2i> textureOffsets;
        float frameDelay = 0.1f;
        bool loop = true;
        bool uniDir = false;
        Animation() {}
        Animation(std::vector<sf::IntRect>& frames_, std::vector<sf::Vector2i>& offsets_, float frameDelay_, bool looping_, bool facingRight_, bool isUniDir_ = false)
            : loop{ looping_ }
            , uniDir{ isUniDir_ }
            , frameDelay{ frameDelay_ }
        {
            if (isUniDir_)
            {
                framesUni.clear();
                framesUni.reserve(frames_.size());
                for (auto& fr : frames_)
                {
                    framesUni.push_back(fr);
                }
               

            }
            else
            {
                if (facingRight_ == true)
                {
                    framesRight.clear();
                    framesRight.reserve(frames_.size());
                    for (auto& fr : frames_)
                    {
                        framesRight.push_back(fr);
                    }

                }
                else
                {
                    framesLeft.clear();
                    framesLeft.reserve(frames_.size());
                    for (auto& fr : frames_)
                    {
                        framesLeft.push_back(fr);
                    }

                }
            }

            textureOffsets.clear();
            textureOffsets.reserve(offsets_.size());
            for (auto& off : offsets_)
            {
                textureOffsets.push_back(off);
            }
        }
    };

public:
    AnimHandler();

    void changeAnim(const std::string& animName);
    void update(float dt);
    bool isLooping(const std::string& animName);
    void setLooping(const std::string& animName, bool cond_); 
    void setUniDir(bool cond_);

    std::unordered_map<std::string, Animation>& getAnims();

    const sf::IntRect& getCurrFRect() const;
    const sf::Vector2i& getCurrTexOff() const;

    void setFacingRight(bool cond_);
    bool isFacingRight() const;
    bool isCurrUniDir();
    void setFrameOffsets(sf::Vector2i off_,  int index = -1, std::string animName = "Current");
    sf::Vector2i getFrameOffsets(int index = -1, std::string animName = "Current", bool uniDirectional = true);
    sf::Vector2i getTexOffset(const std::string& animName);
    void resizeFrames(const std::string& animName_, const std::string& dir_, int size_);
    void addAnim(const std::string& name,std::vector<sf::IntRect>& frames,std::vector<sf::Vector2i>& offsets,float frameDelay, bool loop = true, bool facingRight_ = true, std::string dir_ = "Uni");

    
    sf::IntRect getLeftFrame(int index = -1);
    sf::IntRect getRightFrame(int index = -1);
    sf::IntRect getUniFrame(int index = -1);
    int getCurrentIndex();
    void setCurrentIndex(int index);
    size_t getNumAnims();
    std::vector<std::string> getAnimNames(const std::string& dir_);

    void setFrameDelay(float frameDelay_, std::string animName = "Current");
    float getFrameDelay(std::string animName = "Current");
    inline bool isUni() { return _uniDirectional; }

    std::string getAnimName() const;

    const std::vector<sf::IntRect>& getFrames(std::string dir_ = "Uni", std::string anim_ = "Current") const;
    void setFrame(const sf::IntRect& rect_, const std::string& animName_, int index, const std::string& dir_ = "Uni");



private:
    Animation& getAnimation(std::string animName_ = "Current");

    std::unordered_map<std::string, Animation> _animations;
    bool _uniDirectional{ true };
    std::string _currentAnim{""};

    float _frameElapsed{ 0.f };

    const sf::IntRect _nullFrame{ {0,0},{0,0} };
    const sf::Vector2i _nullOffset{ 0,0 };

    bool _facingRight{ true };

};

//template <class FSM_TYPE, class STATE_VAR>
//class AnimHandler
//{
//	bool alreadyStarted{ false };
//	float startElapsed{ 0.f };
//	float frameElapsed{ 0.f };
//	float loopElapsed{ 0.f };
//public:
//	DrawableObj* parent;
//
//
//	FSM_TYPE* ownerFSM;
//
//
//	std::vector<PlayerEventVar> events;
//
//	std::vector<sf::IntRect> animFrames;
//	std::vector<sf::Vector2i> textureOffsets;
//
////	AnimHandler<FSM_TYPE, STATE_VAR>() : ownerFSM{ nullptr }, parent{ nullptr }, events{ std::vector<PlayerEventVar>{} } {}
//
//	AnimHandler<FSM_TYPE, STATE_VAR>(FSM_TYPE* fsm_, DrawableObj* parent_) : ownerFSM{ fsm_ }, parent{ parent_ }, events{ std::vector<PlayerEventVar>()} {}
//
//
//	~AnimHandler() = default;
//
//	void update(float dt_)
//	{
//		bool animate = false;
//	if (parent->m_playing)
//	{
//		if (!parent->m_startDelays.empty() && !alreadyStarted)
//		{
//			if (parent->m_startDelays[parent->m_animName] != 0.f)
//			{
//				startElapsed += dt_;
//				if (startElapsed >= parent->m_startDelays[parent->m_animName])
//				{
//					startElapsed = 0.f;
//					alreadyStarted = true;
//					animate = true;
//				}
//			}
//			else
//			{
//				alreadyStarted = true;
//				frameElapsed = 0.f;
//				animate = false;
//			}
//		}
//		else	if (parent->m_currentFrame == ((parent->m_facingRight) ? parent->m_texFramesRight[parent->m_animName].size() : parent->m_texFramesLeft[parent->m_animName].size()) - 1)
//		{
//			if (parent->m_loopWaits)
//			{
//				loopElapsed += dt_;
//				if (loopElapsed > parent->m_loopDelays[parent->m_animName])
//				{
//					loopElapsed = 0.f;
//					animate = true;
//				}
//			}
//			else
//			{
//				if (parent->m_looping)
//				{
//					parent->m_currentFrame = 0;
//				}
//			}
//		}
//		else
//		{
//			frameElapsed += dt_;
//			if (frameElapsed >= parent->m_frameDelays[parent->m_animName])
//			{
//				frameElapsed = 0.f;
//				animate = true;
//			}
//		}
//
//		if (animate == true)
//			parent->animate();
//
//	}
//	for (auto& evt : events)
//	{
//		dispatch(*ownerFSM, evt);
//	}
//
//
//
//	events.clear();
//}
//
//	void render(sf::RenderWindow& wnd_)
//	{
//		sf::IntRect texRect = parent->m_texFramesRight[parent->m_animName].at(parent->m_currentFrame);
//		sf::Vector2f pos = { parent->GetPosition().x - parent->m_frameOffset[parent->m_animName].x, parent->GetPosition().x - parent->m_frameOffset[parent->m_animName].y };
//		pos.x -= parent->m_frameOffset[parent->m_animName].x;
//		pos.y -= parent->m_frameOffset[parent->m_animName].y;
//		Cfg::Textures texID = parent->getTextureID();
//
//		sf::Sprite spr{ Cfg::textures.get((int)texID) };
//		spr.setPosition(pos);
//		spr.setTextureRect(texRect);
//
//		wnd_.draw(spr);
//	}
//
//};
