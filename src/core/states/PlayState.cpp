#include "PlayState.h"
#include <handlers/GStateMgr.h>
PlayState::PlayState(GStateMgr& stateMgr, sf::RenderWindow* pWnd_, float* pDT_)
	: StateBase{stateMgr, pWnd_, pDT_ }
{
	std::cout << "PlayState created" << std::endl;
}

std::string PlayState::update()
{

	//std::cout << "PlayState updating..." << std::endl;
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

std::string PlayState::finalize()
{
	return "OK";
}

std::string PlayState::render()
{
	return "OK";
}

std::string PlayState::tick()
{
	return "OK";
}

std::string PlayState::handleCollisions()
{
	return "OK";
}

