#include "PausedState.h"
#include <handlers/GStateMgr.h>
#include <iostream>
PausedState::PausedState(GStateMgr* stateMgr, sf::RenderWindow* pWnd_, float* pDT_)
	: StateBase{stateMgr, pWnd_, pDT_ }
{
	std::cout << "PausedState created" << std::endl;
}

std::string PausedState::update()
{
	//std::cout << "PausedState updating" << std::endl;
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

std::string PausedState::finalize()
{
	return "OK";
}

std::string PausedState::render()
{
	return "OK";
}

std::string PausedState::tick()
{
	return "OK";
}
