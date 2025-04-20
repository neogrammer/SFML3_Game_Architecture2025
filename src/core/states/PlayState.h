#ifndef PLAYSTATE_H__
#define PLAYSTATE_H__
#include "StateBase.h"

#include <game_objects/Player.h>

#include <game_objects/InvariantObject.h>
#include <tilemap/Tile.h>
#include <game_objects/BackgroundStatic.h>
#include <tilemap/Tilemap.h>
#include <game_objects/SimplePlatform.h>

class GameStateMgr;
class Physics;

class PlayState : public StateBase
{

	Player player{};
	Tile aTile{};
	BackgroundStatic bgIntro;
	SimplePlatform plat1{};

	Tilemap tmap;

	sf::View gameView;
	sf::View guiView;
public:
	using StateBase::StateBase;

	PlayState(GStateMgr* stateMgr, sf::RenderWindow* pWnd_, float* pDT_);

	//void processEvents() override final;
	//void runScripts() override final;
	//void handleInput() override final;
	std::string update() override final;
	std::string finalize() override final;
	std::string render() override final;
	std::string tick() override final;

	std::string handleCollisions();

};

#endif