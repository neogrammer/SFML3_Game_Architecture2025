#include "PlayState.h"
#include <handlers/GStateMgr.h>
PlayState::PlayState(GStateMgr* stateMgr, sf::RenderWindow* pWnd_, float* pDT_)
	: StateBase{stateMgr, pWnd_, pDT_ }
	, face{Cfg::Textures::PlayerAtlas132x150}
{
	std::cout << "PlayState created" << std::endl;
	face.setPosition({ 0.f,0.f });
	face.setTexRect({ {0,0},{132,150} });

	face.animMgr.AddRightFrames(AnimName::Idle, Cfg::Textures::PlayerAtlas132x150, 1, 1, 0, 0, 21, 132, 150);
	face.setTexID(Cfg::Textures::PlayerAtlas132x150);

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

