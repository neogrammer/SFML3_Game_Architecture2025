#include "PlayState.h"
#include <handlers/GStateMgr.h>
#include <err/ErrorMacros.h>

PlayState::PlayState(GStateMgr* stateMgr, sf::RenderWindow* pWnd_, float* pDT_)
	: StateBase{stateMgr, pWnd_, pDT_ }
	, face{Cfg::Textures::MegaManSheet1x48x48x1}
{
	std::cout << "PlayState created" << std::endl;
	face.setPosition({ 0.f,0.f });
	face.setTexRect({ {0,0},{132,150} });

	// causes a memory leak when failing, may want to set up a deferred Errorfunction called after construction before any other functions or summin
	chk(face.loadInFile("Player.anim"));

	face.setScale({ 5.f,5.f });
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
		face.animMgr.animate(*pGameTime);
	}
	return "OK";
}



std::string PlayState::finalize()
{
	if (face.animMgr.getTexID() != face.getTexID())
	{
		face.setTexID(face.animMgr.getTexID());
	}
	face.setTexRect(face.animMgr.currFrame());
	
	return "OK";
}

std::string PlayState::render()
{
	pStateMgr->pWnd->draw(face);
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

