#ifndef PLAYSTATE_H__
#define PLAYSTATE_H__
#include "StateBase.h"
<<<<<<< HEAD
#include <game_objects/Player.h>
=======
#include <game_objects/AnimObject.h>
#include <game_objects/Player.h>

>>>>>>> 715163d0180834600f23e60846ea0b9689190064
class GameStateMgr;

class PlayState : public StateBase
{
<<<<<<< HEAD
	Player player;
=======
	Player player{};
>>>>>>> 715163d0180834600f23e60846ea0b9689190064
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