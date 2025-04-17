//AGameApp.cpp
#include <core/app/AGameApp.h>
#include <err/ErrorMacros.h>
#include <core/resources/Cfg.h>

AGameApp::AGameApp() : mWnd{ sf::VideoMode{{gWndWidth,gWndHeight}, 32U }, "Xastle Xashers", sf::State::Windowed }, mGameOver{ false }, mGameTime{ 0.f }, pStateMgr{ nullptr } {}
AGameApp::~AGameApp() {}

void AGameApp::run()
{
	sf::Clock frameClock = {};

	GStateMgr stateMgr{ mWnd,mGameTime, mGameOver };
	pStateMgr = &stateMgr;
	/// GameStateMgr create

	if (!mWnd.isOpen())
	{
		mGameOver = true;
	}

	while (!mGameOver)
	{
		mGameTime = frameClock.restart().asSeconds();

		// only changes state flags, does not move any positions
		if (!mGameOver)
		{
			
			chk(processEvents());
			chk(handleStaticInput());
			chk(runScripts());
		}


		if (!mGameOver)
		{
			chk(updateGame());
			chk(handleCollisions());
			chk(tickSimulation());
		}

		if (!mGameOver)
		{
			chk(finalizeState());
			chk(renderScene());
		}


	}

	if (mWnd.isOpen())
		mWnd.close();

	//pStateMgr = nullptr;
	Cfg::textures.clear();
	Cfg::textures;

}

std::string AGameApp::processEvents()
{

	while (const std::optional event = mWnd.pollEvent())
	{
		if (event->is<sf::Event::Closed>())
		{
			mGameOver = true;
			mWnd.close();

		}
		if (event->is<sf::Event::KeyReleased>()) 
		{
			const auto* keyReleased = event->getIf<sf::Event::KeyReleased>();
			if (!keyReleased) break;

			if (keyReleased->scancode == sf::Keyboard::Scancode::Escape) 
			{
				mGameOver = true;
			}
			
		}
	}
	return "OK";
}

std::string AGameApp::runScripts()
{
	return pStateMgr->runScripts();
}


std::string  AGameApp::handleStaticInput()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape))
	{
		mGameOver = true;
	}

	return pStateMgr->handleStaticInput();

}


std::string  AGameApp::updateGame()
{
	
	return pStateMgr->updateGame();

	// std::string stateMgr.updateStateStack();
}


std::string  AGameApp::handleCollisions()
{
	return pStateMgr->handleCollisions();

}


std::string  AGameApp::finalizeState()
{
	return pStateMgr->finalizeState();

}


std::string  AGameApp::tickSimulation()
{
	return pStateMgr->tickSimulation();

}



std::string  AGameApp::renderScene()
{
	std::string res = "Ok";

	mWnd.clear(sf::Color(0, 0, 0, 255));
	
	res = pStateMgr->renderScene();

	mWnd.display();

	return res;
}

