#ifndef CFG_H__
#define CFG_H__

#include <SFML/Graphics.hpp>
#include "ResourceManager.h"
#include <vector>
#include <SFML/Audio.hpp>

#define SCREENTILESX 16
#define SCREENTILESY 12

class Cfg
{
public:
	Cfg() = delete;
	Cfg(const Cfg&) = delete;
	Cfg& operator=(const Cfg&) = delete;


	//globals 
	//static sol::state lua; // globals are bad, but we'll use it for simpler implementation
	static void Initialize();
	static void Uninitialize();
	// Resource Enums 
	enum class Textures : int { GooglyEye, GooglyEyeShot, BusterShot, Platform1, SplashBG, TitleBG,TitleText,Invariant, PlayerAtlas132x150, MegaManSheet1x48x48x1, TilesetIntro, BGIntro, Invalid };
	enum class Fonts : int { Font1 };
	enum class Music : int { TitleBGMusic, IntroLevel };
  enum class Sounds : int { XHurt, XDie, BustershotNormal, BustershotCharged, XCharging, EnemyHurt1, EnemyDie1, HelmetHit, XJump, XLand, };

	// inputs the player will be able to use
	enum PlayerInputs : int
	{
		// Keyboard mappable Keypresses
		Up, Down, Left, Right, A, X, Y, B, Start, Select, R1, L1,

		//// Joystick input, like a ps5 controller, DPad* and Axis* are handled differently than the rest of the joystick
		DPadX, DPadY, AxisX, AxisY,
		JoyA, JoyB, JoyX, JoyY, JoyR1, JoyL1, JoyStart, JoySelect
	};

	// resource buckets for each type of resource
	static ResourceManager<sf::Texture, int> textures;
	static ResourceManager<sf::Font, int> fonts;
	static ResourceManager<sf::Music, int> music;
	static ResourceManager<sf::SoundBuffer, int> sounds;

	//static ActionMap<int> playerInputs;

private:
    // initalize the resources for the entire game
    static void initFonts();
    static void initMusic();
    static void initSounds();
    static void initTextures();
	static void initPlayerInputs(); 
	static void destroyTextures();
};


#endif