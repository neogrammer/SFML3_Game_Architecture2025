#ifndef SPLASHSTATE_H__
#define SPLASHSTATE_H__
#include "StateBase.h"
#include <SFML/Graphics.hpp>
class GameStateMgr;

class SplashState : public StateBase
{

	sf::Sprite bgSpr;
	float alphaValue{ 0.f };

	float timeTillEndOfDisplay{ 2.f };

	float timeInStateElapsed{ 0.f };
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