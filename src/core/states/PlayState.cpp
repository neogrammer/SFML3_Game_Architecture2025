#include "PlayState.h"
#include <handlers/GStateMgr.h>
#include <err/ErrorMacros.h>

PlayState::PlayState(GStateMgr* stateMgr, sf::RenderWindow* pWnd_, float* pDT_)
	: StateBase{stateMgr, pWnd_, pDT_ }
	, player{}
{
	std::cout << "PlayState created" << std::endl;
	player.setPosition({ 0.f,0.f });
	player.setTexRect({ {1,1},{48,48} });

	// causes a memory leak when failing, may want to set up a deferred Errorfunction called after construction before any other functions or summin
	chk(player.loadInFile("Player.anim"));

	player.setScale({ 5.f,5.f });
	//player.animMgr.switchAnim(AnimName::Run, AnimDir::Right);
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
		player.animMgr.animate(*pGameTime);
	}
	return "OK";
}



std::string PlayState::finalize()
{
	if (player.animMgr.getNumAnims() > 0)
	{
		if (player.animMgr.getTexID() != player.getTexID())
		{
			player.setTexID(player.animMgr.getTexID());
		}
		player.setTexRect(player.animMgr.currFrame());
	}
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

