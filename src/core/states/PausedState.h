#ifndef PAUSEDSTATE_H__
#define PAUSEDSTATE_H__
#include "StateBase.h"
class GameStateMgr;

class PausedState : public StateBase
{
public:
	using StateBase::StateBase;

	 PausedState(GStateMgr& stateMgr, sf::RenderWindow* pWnd_, float* pDT_);

	//void processEvents() override final;
	//void runScripts() override final;
	//void handleInput() override final;
	std::string update() override final;
	std::string finalize() override final;
	std::string render() override final;
	std::string tick() override final;

};

#endif