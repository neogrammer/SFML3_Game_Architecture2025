#pragma once
#include <memory>
#include <vector>
#include "TileObj.h"
#include <core/Resources/Cfg.h>
#include <Tilemap/TilemapTypes.h>

class Tileset
{
	std::vector<std::unique_ptr<TileObj> > tiles_{};
	int m_pitch{ 0 };
public:
	void AddTile(std::unique_ptr<TileObj> tile_);
	void AddTile(const sf::Texture& tex_, sf::IntRect texRect_, TileType type_, FunType fType_, bool empty_, sf::Vector2f pos_);
	void setPitch(int pitch_);
	std::vector<std::unique_ptr<TileObj>>& getTiles();
	std::unique_ptr<TileObj> copyTile(int index);

};