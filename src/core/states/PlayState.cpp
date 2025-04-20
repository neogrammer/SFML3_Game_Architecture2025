#include "PlayState.h"
#include <handlers/GStateMgr.h>
#include <err/ErrorMacros.h>
#include <physics/Physics.h>

PlayState::PlayState(GStateMgr* stateMgr, sf::RenderWindow* pWnd_, float* pDT_)
	: StateBase{ stateMgr, pWnd_, pDT_ }
	, player{}
	, aTile{}
	, bgIntro{ Cfg::Textures::BGIntro }
	, gameView{}
	, guiView{}
	, tmap{"intro.tset", "intro2.tmap"}
{
	aTile.setTexID(Cfg::Textures::TilesetIntro);

	bgIntro.setTextureRect({ {0,0},{1600,900} });
	gameView = pWnd_->getDefaultView();
	guiView = pWnd_->getDefaultView();
	pWnd_->setView(gameView);
}

std::string PlayState::update()
{
	player.handleInput();
	Physics::applyGravity(player, *pGameTime);

	//std::cout << "PlayState updating..." << std::endl;
	if (entering)
	{


		enterTimeElapsed += *pGameTime;
		if (enterTimeElapsed >= 0.f)
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
	// before final moves, handle collisions
	
	for (auto& t : tmap.getSolidTiles(player.getTestArea(*pGameTime)))
	{
		Physics::resolveCollision(&player, t.lock().get());
	}

	// move all objects other than the player

	// move player AND the map, dependency
	pWnd->setView(gameView);
	auto vw = gameView;
	auto oldX = vw.getCenter().x;
	player.finalize(*pGameTime, *pWnd);
	gameView = pWnd->getView();
	auto vwNew = gameView;
	auto newX = vwNew.getCenter().x;
	auto totalX = newX - oldX;
	if (totalX != 0)
	{
		bgIntro.accum += totalX;
	}
	bgIntro.finalize(*pGameTime, *pWnd);
	
	
	return "OK";
}

std::string PlayState::render()
{
	pWnd->setView(gameView);
	pStateMgr->pWnd->draw(bgIntro);
	tmap.Render(*pWnd, *pGameTime);
	pStateMgr->pWnd->draw(player);
	
	//pWnd->setView(guiView);
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

