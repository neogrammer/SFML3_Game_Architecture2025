#ifndef TITLESTATE_H__
#define TITLESTATE_H__
#include "StateBase.h"
class GameStateMgr;

class TitleState : public StateBase
{
public:
	using StateBase::StateBase;

	TitleState(GStateMgr& stateMgr, sf::RenderWindow* pWnd_, float* pDT_);

	//void processEvents() override final;
	//void runScripts() override final;
	std::string handleInput() override final;
	std::string update() override final;
	std::string finalize() override final;
	std::string render() override final;
	std::string tick() override final;

};

#endif