#include "PlayState.h"
#include <handlers/GStateMgr.h>
PlayState::PlayState(GStateMgr* stateMgr, sf::RenderWindow* pWnd_, float* pDT_)
	: StateBase{stateMgr, pWnd_, pDT_ }
	, face{Cfg::Textures::PlayerAtlas132x150}
{
	std::cout << "PlayState created" << std::endl;
	face.setPosition({ 0.f,0.f });
	face.setTexRect({ {0,0},{132,150} });

	face.animMgr.AddRightFrames(AnimName::Idle, Cfg::Textures::MegaManSheet1x48x48x1, 2, 1, 0, 0, 21, 48, 48, AnimSheetType::Padded, 1, 1, true, 3.f);
	face.setTexID(Cfg::Textures::MegaManSheet1x48x48x1);
	face.setScale({ 5.f,5.f });

	face.animMgr.AddLeftFrames(AnimName::Idle, Cfg::Textures::MegaManSheet1x48x48x1, 2, 1, 0, 13, 21, 48, 48, AnimSheetType::Padded, 1, 1, true, 3.f);


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

