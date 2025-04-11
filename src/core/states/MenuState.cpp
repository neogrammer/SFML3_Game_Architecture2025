#include "MenuState.h"
#include <handlers/GStateMgr.h>
#include <iostream>
MenuState::MenuState(GStateMgr& stateMgr, sf::RenderWindow* pWnd_, float* pDT_)
	: StateBase{stateMgr, pWnd_, pDT_ }
{
	std::cout << "MenuState created" << std::endl;
}

std::string MenuState::update()
{
	//std::cout << "MenuState updating" << std::endl;

	return "OK";
}

std::string MenuState::finalize()
{
	return "OK";
}

std::string MenuState::render()
{
	return "OK";
}

std::string MenuState::tick()
{
	return "OK";
}
