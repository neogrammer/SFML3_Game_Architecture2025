#pragma once
#include <SFML/Graphics.hpp>
#include <set>
#include <memory>
#include <utility>
#include <queue>
#include <iostream>

class StateBase;

class GStateMgr
{
	sf::RenderWindow* pWnd;
	sf::Time* pGameTime;

	std::set<std::shared_ptr<StateBase>> states;
	std::deque<std::weak_ptr<StateBase>> activeStates;
	friend class StateBase;
	friend class TitleState;
	friend class SplashState;

	int toRemoveCount{ 0 };
	std::shared_ptr<StateBase> toAdd{ nullptr };
public:


	GStateMgr(sf::RenderWindow& wnd_, float& gameTime_);

	~GStateMgr();
	GStateMgr(const GStateMgr&) = delete;
	GStateMgr& operator=(const GStateMgr&) = delete;

	std::string processEvents();
	std::string runScripts();
	std::string handleStaticInput();
	std::string updateGame();
	std::string handleCollisions();
	std::string finalizeState();
	std::string renderScene();
	std::string tickSimulation();

	std::string pop();


	template<typename STATE>
	void push()
	{

		for (auto& state : states)
		{
			if (dynamic_cast<STATE*>(state.get()) != nullptr)
			{
				activeStates.push_back(state);
				break;
			}
		}

		return;
	};

};