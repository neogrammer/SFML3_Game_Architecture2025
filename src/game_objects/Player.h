<<<<<<< HEAD
#ifndef PLAYER_H__
#define PLAYER_H__

#include "AnimObject.h"

class Player : public AnimObject
{
public:
	using AnimObject::AnimObject;
	Player();
	virtual ~Player() override final;
	
	void handleInput() override final;
	void update(float dt_) override final;
	void finalize(float dt_) override final;
};

#endif
=======
#pragma once
#include <game_objects/AnimObject.h>
#include <handlers/AnimMgr.h>
#include <SFML/Window/Event.hpp>
class Player : public AnimObject
{

public:

	Player(); 
	virtual ~Player() override final; 
	Player(const Player&) = delete;
	Player& operator=(const Player&) = delete;
	Player& operator=(Player&&) = delete;
	Player(Player&&) = delete;

	void processEvent(sf::Event& e);
	void handleInput();


	void update(float dt_);

	void finalize();

	void render(sf::RenderWindow& wnd_);



};
>>>>>>> 715163d0180834600f23e60846ea0b9689190064
