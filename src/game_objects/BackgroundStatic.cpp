#include "BackgroundStatic.h"
BackgroundStatic::BackgroundStatic(Cfg::Textures texID_)
	: sf::Sprite(Cfg::textures.get((int)texID_))
{
}

BackgroundStatic::~BackgroundStatic()
{
}

void BackgroundStatic::update(float dt_)
{
}

void BackgroundStatic::finalize(float dt_, sf::RenderWindow& wnd_)
{
	
	setTextureRect({ { (int)accum, 0 },{1600,900} });
	// position never moves, the view moves across the world, and the tex rect changes its position to match the displacement of the view
	auto vw = wnd_.getView();
	setPosition({ vw.getCenter().x - 800.f, getPosition().y });
}
