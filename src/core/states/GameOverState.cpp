#include "GameOverState.h"
#include <handlers/GStateMgr.h>
#include <iostream>
GameOverState::GameOverState(GStateMgr& stateMgr, sf::RenderWindow* pWnd_, float* pDT_)
	: StateBase{ stateMgr, pWnd_, pDT_}
{
	std::cout << "GameOverState created" << std::endl;
}

std::string GameOverState::update()
{
	//std::cout << "GameOverState updating" << std::endl;
	if (entering)
	{


		enterTimeElapsed += *pGameTime;
	}
	else if (exiting)
	{
		exitTimeElapsed += *pGameTime;
	}
	else
	{

	}
	return "OK";
}

std::string GameOverState::finalize()
{
	return "OK";
}

std::string GameOverState::render()
{
	return "OK";
}

std::string GameOverState::tick()
{
	return "OK";
}


