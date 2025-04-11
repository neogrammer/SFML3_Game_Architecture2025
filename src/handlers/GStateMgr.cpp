#include <handlers/GStateMgr.h>

#include <core/states/WorldMapState.h>
#include <core/states/MenuState.h>
#include <core/states/PlayState.h>
#include <core/states/GameOverState.h>
#include <core/states/TitleState.h>
#include <core/states/SplashState.h>
#include <core/states/PausedState.h>

GStateMgr::GStateMgr(sf::RenderWindow& wnd_, float& gameTime_)
	: states{}
	, activeStates{}
{
	states.emplace(std::make_shared<SplashState>(*this, &wnd_,&gameTime_));
	states.emplace(std::make_shared<MenuState>(*this, &wnd_, &gameTime_));
	states.emplace(std::make_shared<PlayState>(*this,&wnd_, &gameTime_));
	states.emplace(std::make_shared<GameOverState>(*this,&wnd_, &gameTime_));
	states.emplace(std::make_shared<TitleState>(*this,&wnd_, &gameTime_));
	states.emplace(std::make_shared<PausedState>(*this,&wnd_, &gameTime_));
	states.emplace(std::make_shared<WorldMapState>(*this, &wnd_, &gameTime_));

	push<SplashState>();

	/*for (auto& state : states)
	{
		if (dynamic_cast<SplashState*>(state.get()) != nullptr)
		{
			activeStates.push_back(state);
			break;
		}
	}*/
}

GStateMgr::~GStateMgr()
{
}

std::string  GStateMgr::processEvents()
{
	std::string res = "OK";

	for (auto& st : activeStates)
	{
		res = st.lock()->processEvents();
	}
	return res;
}

std::string  GStateMgr::runScripts()
{
	std::string res = "OK";

	for (auto& st : activeStates)
	{
		res = st.lock()->runScripts();
	}
	return res;

}

std::string  GStateMgr::handleStaticInput()
{
	std::string res = "OK";

	for (auto& st : activeStates)
	{
		res = st.lock()->handleInput();
	}

	
	return res;

}

std::string  GStateMgr::updateGame()
{
	std::string res = "OK";

	while (toRemoveCount > 0)
	{
		pop();
		toRemoveCount--;
	}
	if (toAdd != nullptr)
	{
		activeStates.push_back(toAdd);
		toAdd = nullptr;
	}
	

	for (auto& st : activeStates)
	{
		res = st.lock()->update();
	}
	return res;

}

std::string GStateMgr::handleCollisions()
{
	std::string res = "OK";
	for (auto& st : activeStates)
	{
		if (typeid(*st.lock()).name() == typeid(PlayState).name())
		{
			res = dynamic_cast<PlayState*>(st.lock().get())->handleCollisions();
		} 
		else if (typeid(*st.lock()).name() == typeid(WorldMapState).name())
		{
			res = dynamic_cast<WorldMapState*>(st.lock().get())->handleCollisions();

		}
	
	}
	return res;
}

std::string  GStateMgr::finalizeState()
{
	std::string res = "OK";

	for (auto& st : activeStates)
	{
		res = st.lock()->finalize();
	}
	return res;

}

std::string  GStateMgr::renderScene()
{
	std::string res = "OK";

	for (auto& st : activeStates)
	{
		res = st.lock()->render();
	}
	return res;

}

std::string GStateMgr::tickSimulation()
{
	std::string res = "OK";
	for (auto& st : activeStates)
	{
		res = st.lock()->tick();
	}
	return res;

}

std::string GStateMgr::pop()
{
	if (activeStates.empty())
	{
		return "Empty POP!";
	}
	else
	{
		activeStates.back().reset();
		activeStates.pop_back();
	}
	return "OK";
}


