#include "Enemy.h"


Enemy::Enemy(Cfg::Textures tex_, sf::Vector2f pos_, sf::IntRect rect_, sf::Vector2f off_, sf::Vector2f size_, std::vector<void**> loadData)
	: rawInput{ std::vector<void**>{} }
{
	rawInput.clear();
	rawInput.reserve(loadData.size());

	if (rawInput.capacity() == 0)
	{
		// do nothing with the data

	}
	else
	{
		for (int i = 0; i < loadData.size(); i++)
		{
			rawInput.emplace_back(loadData[i]);
		}
	}

	if (!rawInput.empty())
	{
		//translateData(rawInput.data(), rawInput.size(), sizeof(rawInput[0]));
	}
}
