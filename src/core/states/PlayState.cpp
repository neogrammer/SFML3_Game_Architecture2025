#include "PlayState.h"
#include <handlers/GStateMgr.h>
#include <err/ErrorMacros.h>
#include <physics/Physics.h>

PlayState::PlayState(GStateMgr* stateMgr, sf::RenderWindow* pWnd_, float* pDT_)
	: StateBase{ stateMgr, pWnd_, pDT_ }
	, player{}
	, aTile{}
	, bgIntro{ Cfg::Textures::BGIntro }
	, plat1{ Cfg::Textures::Platform1, {{262,269},{191,61}},{0.f,0.f},{191.f,61.f},{900.f,450.f} }
	, gameView{}
	, guiView{}
	, tmap{"intro.tset", "intro2.tmap"}
	, busterShot{ &player, Cfg::Textures::BusterShot, {{0,0},{24,14}}, {0.f,0.f}, {24.f,14.f},player.getPosition() } 
{
	aTile.setTexID(Cfg::Textures::TilesetIntro);

	bgIntro.setTextureRect({ {0,0},{1600,900} });
	gameView = pWnd_->getDefaultView();
	guiView = pWnd_->getDefaultView();
	pWnd_->setView(gameView);

	busterShot.loadInFile("BusterShot.anim");

}

std::string PlayState::update()
{
	player.handleInput();
	Physics::applyGravity(player, *pGameTime);
	plat1.update(*pGameTime);

	busterShot.update(*pGameTime);

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

	// before final moves,handle collisions
	
	for (auto& t : tmap.getSolidTiles(player.getTestArea(*pGameTime)))
	{
		Physics::resolveCollision(&player, t.lock().get());
	}

	Physics::resolveCollision(&player, &plat1);

	//before finalizing other objects, after collision detection, finalize the platforms so attached objects move with the platform
	plat1.finalize(*pGameTime, *pWnd);
	busterShot.finalize(*pGameTime, *pWnd);

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
	pStateMgr->pWnd->draw(plat1);
	pStateMgr->pWnd->draw(player);
	pStateMgr->pWnd->draw(busterShot);
	
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

