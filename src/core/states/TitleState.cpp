#include "TitleState.h"
#include <iostream>
#include <handlers/GStateMgr.h>
#include <core/states/PlayState.h>
TitleState::TitleState(GStateMgr& stateMgr, sf::RenderWindow* pWnd_, float* pDT_)
	: StateBase{stateMgr, pWnd_, pDT_ }
{
	std::cout << "TitleState created" << std::endl;

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

			removeMe();

			for (auto& state : pStateMgr->states)
			{
				if (dynamic_cast<PlayState*>(state.get()) != nullptr)
				{
					pStateMgr->toAdd = state;
				}
			}


		}
	}
	return res;
}

std::string TitleState::update()
{
	//std::cout << "TitleState Updating" << std::endl;

	return "OK";
}

std::string TitleState::finalize()
{
	return "OK";
}

std::string TitleState::render()
{
	return "OK";
}

std::string TitleState::tick()
{
	return "OK";
}
