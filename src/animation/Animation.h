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

	AnimState previousState{ AnimState::Invariant };
	AnimState transientState{ AnimState::Invariant };
	AnimState currState{ AnimState::Invariant };
	AnimName name{ AnimName::Invariant };
	Cfg::Textures texID{ Cfg::Textures::Invariant };

	sf::Vector2f worldSize{0.f,0.f};
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

};


#endif