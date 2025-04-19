#ifndef TILE_H__
#define TILE_H__
#include <game_objects/GameObject.h>

class Tile : public GameObject
{
public:
	virtual ~Tile() override {}
	virtual void update(float dt_) override {}
	virtual void finalize(float dt_, sf::RenderWindow& wnd_) override {}
};

#endif