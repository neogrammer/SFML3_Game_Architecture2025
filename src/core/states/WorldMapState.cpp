#include "WorldMapState.h"
#include <handlers/GStateMgr.h>
#include <iostream>
WorldMapState::WorldMapState(GStateMgr& stateMgr, sf::RenderWindow* pWnd_, float* pDT_)
	: StateBase{stateMgr, pWnd_, pDT_ }
{
	std::cout << "WorldMapState created" << std::endl;
}

std::string WorldMapState::update()
{
	//std::cout << "WorldMapState updating" << std::endl;
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

std::string WorldMapState::finalize()
{
	return "OK";
}

std::string WorldMapState::render()
{
	return "OK";
}

std::string WorldMapState::tick()
{
	return "OK";
}

std::string WorldMapState::handleCollisions()
{
	return "OK";
}
