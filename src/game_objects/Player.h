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