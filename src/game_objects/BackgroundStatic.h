#ifndef BACKGROUNDSTATIC_H__
#define BACKGROUNDSTATIC_H__
#include "GameObject.h"
#include <SFML/Graphics.hpp>
#include "core/resources/Cfg.h"


class BackgroundStatic : public sf::Sprite
{
	friend class PlayState;
	float accum{ 0.f };
public:
	using sf::Sprite::Sprite;
	BackgroundStatic() = delete;
	BackgroundStatic(Cfg::Textures texID);
	virtual ~BackgroundStatic() override;
	void update(float dt_);
	void finalize(float dt_, sf::RenderWindow& wnd_);
};

#endif