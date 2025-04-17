#include "PlayState.h"
#include <handlers/GStateMgr.h>
#include <err/ErrorMacros.h>

PlayState::PlayState(GStateMgr* stateMgr, sf::RenderWindow* pWnd_, float* pDT_)
	: StateBase{stateMgr, pWnd_, pDT_ }
	, player{}
{
}

std::string PlayState::update()
{

	//std::cout << "PlayState updating..." << std::endl;
	if (entering)
	{


		enterTimeElapsed += *pGameTime;
		if (enterTimeElapsed > 1.f)
		{
			entering = false;
		}

	}
	else if (exiting)
	{
		exitTimeElapsed += *pGameTime;
	}
	else
	{
		player.update(*pGameTime);
	}
	return "OK";
}



std::string PlayState::finalize()
{
	player.finalize(*pGameTime);

	return "OK";
}

std::string PlayState::render()
{
	pStateMgr->pWnd->draw(player);
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

