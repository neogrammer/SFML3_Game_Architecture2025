#ifndef SPLASHSTATE_H__
#define SPLASHSTATE_H__
#include "StateBase.h"
class GameStateMgr;

class SplashState : public StateBase
{
public:
	using StateBase::StateBase;

	SplashState(GStateMgr& stateMgr, sf::RenderWindow* pWnd_, float* pDT_);

	//void processEvents() override final;
	//void runScripts() override final;
	std::string handleInput() override final;
	std::string update() override final;
	std::string finalize() override final;
	std::string render() override final;
	std::string tick() override final;

};

#endif