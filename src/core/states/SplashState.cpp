#include "SplashState.h"
#include <string>
#include <iostream>
#include <handlers/GStateMgr.h>
#include <core/states/TitleState.h>
SplashState::SplashState(GStateMgr& stateMgr, sf::RenderWindow* pWnd_, float* pDT_)
	: StateBase{stateMgr, pWnd_, pDT_ }
{
	std::cout << "SplashState created" << std::endl;
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
		if (keyPIsDown)
		{
			keyPIsDown = false;

			removeMe();

			for (auto& state : pStateMgr->states)
			{
				if (dynamic_cast<TitleState*>(state.get()) != nullptr)
				{
					pStateMgr->toAdd = state;
				}
			}


		}
	}
	return res;
}

std::string SplashState::update()
{
//	std::cout << "SplashState updating..." << std::endl;

	return "OK";
}

std::string SplashState::finalize()
{
	return "OK";
}

std::string SplashState::render()
{
	return "OK";
}

std::string SplashState::tick()
{
	return "OK";
}

