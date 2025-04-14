#ifndef TITLESTATE_H__
#define TITLESTATE_H__
#include "StateBase.h"
#include <SFML/Graphics.hpp>
class GameStateMgr;

class TitleState : public StateBase
{

	sf::Sprite bgSpr;
	sf::Sprite titleTextSpr;
	float alphaValue{ 0.f };
	float choiceAlpha{ 0.f };
	float timeTillEndOfDisplay{ 2.f };
	sf::Text playGameText;
	sf::Text quitGameText;

	int choice{ 0 };

	const sf::Color SelectedColor{ sf::Color::White };
	const sf::Color SelectedOutlineColor{ sf::Color::Black };

	const sf::Color NotSelectedColor{ sf::Color::Black };
	const sf::Color NotSelectedOutlineColor{ sf::Color::White };

	bool musicStarted{ false };
	bool bringInTextStart{ false };
	float musicVolume{ 100.f };
	float timeInStateElapsed{ 0.f };
public:
	using StateBase::StateBase;

	TitleState(GStateMgr* stateMgr, sf::RenderWindow* pWnd_, float* pDT_);

	//void processEvents() override final;
	//void runScripts() override final;
	std::string handleInput() override final;
	std::string update() override final;
	std::string finalize() override final;
	std::string render() override final;
	std::string tick() override final;

};

#endif