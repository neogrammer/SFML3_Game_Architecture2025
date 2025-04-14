#ifndef GAMEOVERSTATE_H__
#define GAMEOVERSTATE_H__
#include "StateBase.h"
class GameStateMgr;

class GameOverState : public StateBase
{
public:
	using StateBase::StateBase;

	GameOverState(GStateMgr* stateMgr, sf::RenderWindow* pWnd_, float* pDT_);

	//void processEvents() override final;
	//void runScripts() override final;
	//void handleInput() override final;
	std::string update() override final;
	std::string finalize() override final;
	std::string render() override final;
	std::string tick() override final;

};

#endif