#pragma once
#include <SFML/Graphics.hpp>
#include <global.h>
#include <handlers/GStateMgr.h>
#include <optional>


class AGameApp
{
	sf::RenderWindow mWnd;
	bool mGameOver;

	float mGameTime;

	GStateMgr* pStateMgr{ nullptr };


    std::string processEvents();
	std::string runScripts();
	std::string handleStaticInput();
	std::string updateGame();
	std::string handleCollisions();
	std::string finalizeState();
	std::string renderScene();
	std::string tickSimulation();



public:
	AGameApp();
	~AGameApp();
	AGameApp(const AGameApp&) = delete;
	AGameApp& operator=(const AGameApp&) = delete;


	void run();


};