#include "SplashState.h"
#include <string>
#include <iostream>
#include <handlers/GStateMgr.h>
#include <core/states/TitleState.h>
#include <core/resources/Cfg.h>
SplashState::SplashState(GStateMgr& stateMgr, sf::RenderWindow* pWnd_, float* pDT_)
	: StateBase{stateMgr, pWnd_, pDT_ }
	, bgSpr{Cfg::textures.get((int)Cfg::Textures::SplashBG)}
{
	std::cout << "SplashState created" << std::endl;
	bgSpr.setColor(sf::Color(255, 255, 255, (std::uint8_t)alphaValue));
}


std::string SplashState::handleInput()
{
	std::string res = "OK";
	static bool keyPIsDown = false;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::P))
	{
		keyPIsDown = true;
	}
	else
	{
		if (keyPIsDown || exiting)
		{
			keyPIsDown = false;

			removeMe();

			if (!exiting)
			{
				for (auto& state : pStateMgr->states)
				{
					if (dynamic_cast<TitleState*>(state.get()) != nullptr)
					{
						pStateMgr->toAdd = state;
						exiting = true;
					}
				}
			}
			else
			{
				
					if (pStateMgr->toAdd == nullptr)
					{
						for (auto& st : pStateMgr->states)
						{
							if (dynamic_cast<TitleState*>(st.get()) != nullptr)
							{
								pStateMgr->toAdd = st;
								break;
							}
						}
					}
				
			}




		}
	}
	return res;
}

std::string SplashState::update()
{
//	std::cout << "SplashState updating..." << std::endl;
	if (entering)
	{
		enterTimeElapsed += *pGameTime;
		alphaValue += 100.f * *pGameTime;
		if (alphaValue >= 255.f)
		{
			alphaValue = 255.f;
		}
		bgSpr.setColor(sf::Color(255, 255, 255, (std::uint8_t)alphaValue));
		if (enterTimeElapsed >= 3.0f)
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
		}
	}
	else
	{
		// not entering nor exiting, run as normal
		timeInStateElapsed += *pGameTime;

		if (timeInStateElapsed >= timeTillEndOfDisplay)
		{
			exiting = true;
			timeInStateElapsed = 0.f;
			return "OK";
		}

	}

	return "OK";
}

std::string SplashState::finalize()
{
	return "OK";
}

std::string SplashState::render()
{

	pWnd->draw(bgSpr);
	return "OK";
}

std::string SplashState::tick()
{
	return "OK";
}

