#include "Tile.h"

Tile::Tile()
{
}

Tile::Tile(Cfg::Textures texID_, sf::Vector2f size_, sf::Vector2i texPos_,  sf::Vector2f pos_, bool solid_, bool visible_)
	: GameObject{ texID_, {(sf::Vector2i)texPos_, (sf::Vector2i)size_ }, { 0.f,0.f }, size_, pos_}
	, solid{solid_}
	, visible{ visible_ }
	, tw{(int)size_.x}
	, th{(int)size_.y}
{
}


Tile::~Tile()
{
}

bool Tile::isSolid()
{
	return solid;
}
bool Tile::isVisible()
{
	return visible;
}

void Tile::setSolid(bool cond_)
{
	solid = cond_;
}

void Tile::setSolid(int cond_)
{
	solid = (cond_ == 1) ? true : false;
}

void Tile::setVisible(bool cond_)
{
	visible = cond_;
}

void Tile::setVisible(int cond_)
{
	visible = (cond_ == 1) ? true : false;
}

Tile&& Tile::copyTile()
{
	Tile aTile{ texID,{{0,0}, {tw, th}}, {0.f,0.f}, {(float)tw,(float)th} , {0.f,0.f} };
	aTile.setSolid(this->isSolid());
	aTile.setVisible(this->isVisible());

	return static_cast<Tile&&>(aTile);
}

void Tile::update(float dt_)
{
}

void Tile::finalize(float dt_, sf::RenderWindow& wnd_)
{
}
