#include "TitleState.h"
#include <iostream>
#include <handlers/GStateMgr.h>
#include <core/states/PlayState.h>
#include <core/resources/Cfg.h>

TitleState::TitleState(GStateMgr* stateMgr, sf::RenderWindow* pWnd_, float* pDT_)
	: StateBase{stateMgr, pWnd_, pDT_ }
	, bgSpr{ Cfg::textures.get((int)Cfg::Textures::TitleBG) }
	, titleTextSpr{Cfg::textures.get((int)Cfg::Textures::TitleText)}
	, playGameText{ Cfg::fonts.get((int)Cfg::Fonts::Font1) }
	, quitGameText{Cfg::fonts.get((int)Cfg::Fonts::Font1)}
{
	std::cout << "TitleState created" << std::endl;

	bgSpr.setColor(sf::Color(255, 255, 255, (std::uint8_t)alphaValue));
	titleTextSpr.setPosition({0.f,900.f});

	playGameText.setCharacterSize(44U);
	playGameText.setPosition({ 1200.f, 400.f });
	playGameText.setFillColor(sf::Color::Transparent);
	playGameText.setOutlineThickness(2);
	playGameText.setOutlineColor(sf::Color(255,255,255,0));
	playGameText.setString("Play Game");
	quitGameText.setCharacterSize(44U);
	quitGameText.setPosition({ 1200.f, 550.f });
	quitGameText.setFillColor(sf::Color::Transparent);
	quitGameText.setOutlineThickness(2);
	quitGameText.setOutlineColor(sf::Color(255, 255, 255, 0));
	quitGameText.setString("Quit Game");



}

std::string TitleState::handleInput()
{
	std::string res = "OK";
	static bool keyPIsDown = false;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::P))
	{
		keyPIsDown = true;
	}
	else
	{
		if (keyPIsDown)
		{
			keyPIsDown = false;



			/*removeMe();

			for (auto& state : pStateMgr->states)
			{
				if (dynamic_cast<PlayState*>(state.get()) != nullptr)
				{
					pStateMgr->toAdd = state;
					exiting = true;
				}
			}*/


		}
	}
	
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up))
	{
		if (choice > 0)
			choice--;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down))
	{
		if (choice < 1)
			choice++;
	}

	return res;
}

std::string TitleState::update()
{
	//std::cout << "TitleState Updating" << std::endl;

	if (entering)
	{
		if (!musicStarted)
		{
			musicVolume = 0.f;
			Cfg::music.get((int)Cfg::Music::TitleBGMusic).setVolume(musicVolume);
			Cfg::music.get((int)Cfg::Music::TitleBGMusic).play();
			Cfg::music.get((int)Cfg::Music::TitleBGMusic).setLooping(true);

			musicStarted = true;
			
		}

		enterTimeElapsed += *pGameTime;
		alphaValue += 100.f * *pGameTime;
		musicVolume += 100.f * *pGameTime;
		if (musicVolume >= 100.f)
		{
			musicVolume = 100.f;
		}
		if (alphaValue >= 255.f)
		{
			alphaValue = 255.f;
		}
		bgSpr.setColor(sf::Color(255, 255, 255, (std::uint8_t)alphaValue));
		if (enterTimeElapsed >= 3.f)
		{
			entering = false;
			alphaValue = 255.f;
			exitTimeElapsed = 0.f;
			enterTimeElapsed = 0.f;
			timeInStateElapsed = 0.f;
			bringInTextStart = true;
		}
	}
	else if (exiting)
	{
		exitTimeElapsed += *pGameTime;
		alphaValue -= 100.f * *pGameTime;
		musicVolume -= 100.f * *pGameTime;
		if (musicVolume < 0.f)
		{
			musicVolume = 0.f;
		}
		if (alphaValue < 0.f)
		{
			alphaValue = 0.f;
		}
		bgSpr.setColor(sf::Color(255, 255, 255, (std::uint8_t)alphaValue));
		if (exitTimeElapsed >= 3.f)
		{
			exiting = false;
			alphaValue = 0.f;
			exitTimeElapsed = 0.f;
			enterTimeElapsed = 0.f;
			timeInStateElapsed = 0.f;
			doSwitch = true;
			Cfg::music.get((int)Cfg::Music::TitleBGMusic).stop();
		}
	}
	else
	{
		/*timeInStateElapsed += *pGameTime;

		if (timeInStateElapsed >= timeTillEndOfDisplay)
		{
			exiting = true;
			timeInStateElapsed = 0.f;
			return "OK";
		}*/
	}

	if (bringInTextStart)
	{
		titleTextSpr.setPosition({ 0.f, titleTextSpr.getPosition().y - (450.f * *pGameTime)});
		if (titleTextSpr.getPosition().y < 0.f)
		{
			titleTextSpr.setPosition({ 0.f,0.f });
			bringInTextStart = false;
		}
	}
	else
	{
		if (entering == false)
			choiceAlpha += 100 * *pGameTime;
		if (choiceAlpha > 255.f) { choiceAlpha = 255.f; }



	}


	static bool enterIsPressed{ false };
	static bool enterIsDown{ false };



	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Enter))
	{
		if (!enterIsDown)
		{
			enterIsPressed = true;
		}
		else
		{
			enterIsPressed = false;
		}
		enterIsDown = true;
	}
	else
	{
		enterIsDown = false;
		enterIsPressed = false;
	}
	
	if (choice == 0 && !bringInTextStart && !entering)
	{
		playGameText.setFillColor(sf::Color(0,0,0,(std::uint8_t)choiceAlpha));
		playGameText.setOutlineColor(sf::Color(255, 255, 255, (std::uint8_t)choiceAlpha));
		quitGameText.setFillColor(sf::Color(255, 255, 255, (std::uint8_t)choiceAlpha));
		quitGameText.setOutlineColor(sf::Color(0, 0, 0, (std::uint8_t)choiceAlpha));

		if (enterIsPressed)
		{
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Enter))
			{
				for (auto& state : pStateMgr->states)
				{
					if (dynamic_cast<PlayState*>(state.get()) != nullptr)
					{
						removeMe();
						pStateMgr->toAdd = state;
						exiting = true;
					}
				}
			}
		}

	}
	else if (choice == 1 && !bringInTextStart && !entering)
	{
		quitGameText.setFillColor(sf::Color(0, 0, 0, (std::uint8_t)choiceAlpha));
		quitGameText.setOutlineColor(sf::Color(255, 255, 255, (std::uint8_t)choiceAlpha));
		playGameText.setFillColor(sf::Color(255, 255, 255, (std::uint8_t)choiceAlpha));
		playGameText.setOutlineColor(sf::Color(0, 0, 0, (std::uint8_t)choiceAlpha));

		if (enterIsPressed)
		{
					*pStateMgr->gameOver = true;
					//pStateMgr->toAdd = state;
					exiting = true;
				
		}
	}



	Cfg::music.get((int)Cfg::Music::TitleBGMusic).setVolume(musicVolume);
	

	return "OK";
}

std::string TitleState::finalize()
{
	return "OK";
}

std::string TitleState::render()
{

	pWnd->draw(bgSpr);
	pWnd->draw(titleTextSpr);
	pWnd->draw(playGameText);
	pWnd->draw(quitGameText);

	return "OK";
}

std::string TitleState::tick()
{
	return "OK";
}
