#pragma once

#include <SFML/Graphics/RenderWindow.hpp>
#include "Tile.h"
#include <memory>
#include <utility>
#include <core/resources/Cfg.h>

class Tilemap
{
	std::vector<std::shared_ptr<Tile>> tilesetTiles_{};
	std::vector<std::shared_ptr<Tile>> tilemapTiles_{};
	std::vector<std::weak_ptr<Tile>> solidTiles_{};



	int cols{ 0 };
	int rows{ 0 };
	
	int tilesheetPitch{ 0 };
	int tilesheetNumTiles{ 0 };

	int tw{ 0 };
	int th{ 0 };

	Cfg::Textures texID;


public:

	Tilemap() = delete;
	Tilemap(std::string tilesetFile_, std::string tilemapFile);

	std::vector<std::weak_ptr<Tile>>& getSolidTiles(sf::FloatRect testArea_);
	int getCols() { return cols; }
	int getRows() { return rows; }
	int getTW() { return tw; }
	int getTH() { return th; }
	

	void Render(sf::RenderWindow& wnd_, float dt_);

	int getTilesetPitch() { return tilesheetPitch; }
};