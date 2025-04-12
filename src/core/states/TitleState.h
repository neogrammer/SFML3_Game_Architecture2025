#ifndef TITLESTATE_H__
#define TITLESTATE_H__
#include "StateBase.h"
#include <SFML/Graphics.hpp>
class GameStateMgr;

class TitleState : public StateBase
{

	sf::Sprite bgSpr;
	float alphaValue{ 0.f };

	float timeTillEndOfDisplay{ 2.f };

	bool musicStarted{ false };
	float musicVolume{ 100.f };
	float timeInStateElapsed{ 0.f };
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