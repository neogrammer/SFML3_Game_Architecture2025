#ifndef TILE_H__
#define TILE_H__
#include <game_objects/GameObject.h>

class Tile : public GameObject
{
	int tw, th;
	bool solid{ false };
	bool visible{ false };
public:
	using GameObject::GameObject;
	Tile();
	Tile(Cfg::Textures texID_, sf::Vector2f size_, sf::Vector2i texPos_, sf::Vector2f pos_, bool solid_, bool visible_);
	~Tile() override final;

	bool isSolid();
	bool isVisible();
	void setSolid(bool cond_);
	void setSolid(int cond_);
	void setVisible(bool cond_);
	void setVisible(int cond_);
	void setTW(int tw_);
	void setTH(int th_);

	std::unique_ptr<Tile> copyTile();

	virtual void update(float dt_) override;
	virtual void finalize(float dt_, sf::RenderWindow& wnd_) override;
};



#endif