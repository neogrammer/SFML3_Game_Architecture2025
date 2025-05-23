#ifndef ANIMATION_H__
#define ANIMATION_H__
#include <map>
#include <animation/AnimTypes.h>
#include <vector>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/System/Vector2.hpp>
#include <string>
#include <core/resources/Cfg.h>


extern std::unordered_map<std::string, AnimName> AnimNameLUT;
extern std::unordered_map < std::string, AnimDir> DirectionLUT;
extern std::unordered_map < std::string, Cfg::Textures> TextureIDLUT;
extern std::unordered_map < std::string, AnimSheetType> AnimSheetTypeLUT;
extern std::unordered_map < AnimName, std::string > FSMStateNameLUT;
extern std::unordered_map < std::string, AnimName > FSMAnimNameLUT;


struct Animation
{
public:
	int numFrames{ 0 };
	
	std::vector<sf::IntRect> leftFrames{};
	std::vector<sf::IntRect> rightFrames{};
	std::vector<sf::IntRect> uniFrames{};

	std::vector<sf::Vector2f> leftOffsets{};
	std::vector<sf::Vector2f> rightOffsets{};
	std::vector<sf::Vector2f> uniOffsets{};

	std::vector<sf::Vector2f> leftSizes{};
	std::vector<sf::Vector2f> rightSizes{};
	std::vector<sf::Vector2f> uniSizes{};

	std::vector<sf::Vector2f> leftBulletAnchors{};
	std::vector<sf::Vector2f> rightBulletAnchors{};
	std::vector<sf::Vector2f> uniBulletAnchors{};

	AnimState previousState{ AnimState::Invariant };
	AnimState transientState{ AnimState::Invariant };
	AnimState currState{ AnimState::Invariant };
	AnimName name{ AnimName::Invariant };
	Cfg::Textures texID{ Cfg::Textures::Invariant };

	float frameDelay{ 0.f };
	float loopWaitDelay{ 0.f };
	bool loopWaits{ false };
	bool loops{true};
	bool playing{ true };

	bool hasLeftFrames();
	bool hasRightFrames();
	bool hasUniFrames();

	sf::IntRect getFrame(AnimDir dir_, int index);
	sf::Vector2f getOffset(AnimDir dir_, int index);
	sf::Vector2f getWorldSize(AnimDir dir_, int index_);
	sf::Vector2f getBulletPoint(AnimDir dir_, int index_);
	int getNumFrames();

};


#endif