#include "StateBase.h"
#include <handlers/GStateMgr.h>

void StateBase::removeMe()
{
	pStateMgr->toRemoveCount++;
}

void StateBase::pushState(int index)
{
	std::set<std::shared_ptr<StateBase>>::const_iterator iter = pStateMgr->states.begin();
	std::advance(iter, index);
	pStateMgr->toAdd = *iter;
}

void StateBase::changeState(int index)
{
	removeMe();
	pushState(index);
}

StateBase::StateBase()
	: pWnd{nullptr}
	, pGameTime{nullptr}
{

}

StateBase::StateBase(GStateMgr& stateMgr, sf::RenderWindow* wnd_, float* dt_)
	: pStateMgr{&stateMgr}
	, pWnd{wnd_}
	, pGameTime{dt_}
{
}



StateBase::~StateBase()
{

}

StateBase::StateBase(const StateBase& o)
	: pWnd{o.pWnd}
	, pGameTime{o.pGameTime}
{
}

StateBase& StateBase::operator=(const StateBase& o)
{
	this->pWnd = o.pWnd;
	this->pGameTime = o.pGameTime;


	// TODO: insert return statement here
	return *this;
}

StateBase::StateBase(StateBase&& o) noexcept
	: pWnd{std::move(o.pWnd)}
	, pGameTime{std::move(o.pGameTime)}
{
	o.pWnd = nullptr;
	o.pGameTime = nullptr;

}

StateBase& StateBase::operator=(StateBase&& o) noexcept
{
	this->pWnd = std::move(o.pWnd);
	this->pGameTime = std::move(o.pGameTime);


	// TODO: insert return statement here
	return *this;
}

void StateBase::enter()
{
	std::cout << "Entering new state" << std::endl;
	entering = true;
	exiting = false;
	enterTimeElapsed = 0.f;
}

void StateBase::exitState()
{
	std::cout << "Exitiig new state" << std::endl;

	exiting = true;
	entering = false;
	exitTimeElapsed = 0.f;

}


std::string StateBase::processEvents()
{
	return "OK";
}

std::string StateBase::runScripts()
{
	return "OK";
}

std::string StateBase::handleInput()
{
	return "OK";
}

bool StateBase::shouldDoSwitch()
{
	return doSwitch;
}

bool StateBase::isEntering()
{
	
	return entering;
}

bool StateBase::isExiting()
{
	return exiting;
}
