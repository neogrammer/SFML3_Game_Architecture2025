#include "TitleState.h"
#include <iostream>
#include <handlers/GStateMgr.h>
#include <core/states/PlayState.h>
#include <core/resources/Cfg.h>

TitleState::TitleState(GStateMgr& stateMgr, sf::RenderWindow* pWnd_, float* pDT_)
	: StateBase{stateMgr, pWnd_, pDT_ }
	, bgSpr{ Cfg::textures.get((int)Cfg::Textures::TitleBG) }
{
	std::cout << "TitleState created" << std::endl;

	bgSpr.setColor(sf::Color(255, 255, 255, (std::uint8_t)alphaValue));
}

std::string TitleState::handleInput()
{
	std::string res = "OK";
	static bool keyPIsDown = false;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::P))
	{
		keyPIsDown = true;
	}
	else
	{
		if (keyPIsDown)
		{
			keyPIsDown = false;



			/*removeMe();

			for (auto& state : pStateMgr->states)
			{
				if (dynamic_cast<PlayState*>(state.get()) != nullptr)
				{
					pStateMgr->toAdd = state;
					exiting = true;
				}
			}*/


		}
	}
	return res;
}

std::string TitleState::update()
{
	//std::cout << "TitleState Updating" << std::endl;

	if (entering)
	{
		if (!musicStarted)
		{
			musicVolume = 0.f;
			Cfg::music.get((int)Cfg::Music::TitleBGMusic).setVolume(musicVolume);
			Cfg::music.get((int)Cfg::Music::TitleBGMusic).play();
			Cfg::music.get((int)Cfg::Music::TitleBGMusic).setLooping(true);

			musicStarted = true;
			
		}

		enterTimeElapsed += *pGameTime;
		alphaValue += 100.f * *pGameTime;
		musicVolume += 100.f * *pGameTime;
		if (musicVolume >= 100.f)
		{
			musicVolume = 100.f;
		}
		if (alphaValue >= 255.f)
		{
			alphaValue = 255.f;
		}
		bgSpr.setColor(sf::Color(255, 255, 255, (std::uint8_t)alphaValue));
		if (enterTimeElapsed >= 3.f)
		{
			entering = false;
			alphaValue = 255.f;
			exitTimeElapsed = 0.f;
			enterTimeElapsed = 0.f;
			timeInStateElapsed = 0.f;
		}
	}
	else if (exiting)
	{
		exitTimeElapsed += *pGameTime;
		alphaValue -= 100.f * *pGameTime;
		musicVolume -= 100.f * *pGameTime;
		if (musicVolume < 0.f)
		{
			musicVolume = 0.f;
		}
		if (alphaValue < 0.f)
		{
			alphaValue = 0.f;
		}
		bgSpr.setColor(sf::Color(255, 255, 255, (std::uint8_t)alphaValue));
		if (exitTimeElapsed >= 3.f)
		{
			exiting = false;
			alphaValue = 0.f;
			exitTimeElapsed = 0.f;
			enterTimeElapsed = 0.f;
			timeInStateElapsed = 0.f;
			doSwitch = true;
			Cfg::music.get((int)Cfg::Music::TitleBGMusic).stop();
		}
	}
	else
	{
		/*timeInStateElapsed += *pGameTime;

		if (timeInStateElapsed >= timeTillEndOfDisplay)
		{
			exiting = true;
			timeInStateElapsed = 0.f;
			return "OK";
		}*/
	}

	Cfg::music.get((int)Cfg::Music::TitleBGMusic).setVolume(musicVolume);
	

	return "OK";
}

std::string TitleState::finalize()
{
	return "OK";
}

std::string TitleState::render()
{

	pWnd->draw(bgSpr);
	return "OK";
}

std::string TitleState::tick()
{
	return "OK";
}
