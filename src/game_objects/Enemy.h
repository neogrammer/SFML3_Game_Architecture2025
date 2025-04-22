#ifndef ENEMY_H__
#define ENEMY_H__
#include <game_objects/AnimObject.h>
class Enemy : public AnimObject
{
	std::vector<void**> rawInput{};
	bool hasFedData{ false };

public:
	using AnimObject::AnimObject;

	Enemy(Cfg::Textures tex_, sf::Vector2f pos_, sf::IntRect rect_, sf::Vector2f off_, sf::Vector2f size_, std::vector<void**> loadData = {});
	virtual ~Enemy() override {}
	//virtual void translateData(void*** outToBase_, size_t numElems_, size_t elemSize_) = 0;
	virtual void update(float dt_) override = 0;
	virtual void finalize(float dt_, sf::RenderWindow& wnd_) override = 0;
};

#endif