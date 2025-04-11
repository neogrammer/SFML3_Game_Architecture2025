#pragma once

#include "Tileset.h"
#include <SFML/Graphics/RenderWindow.hpp>

class Tilemap
{
	Tileset tset_{};
	std::vector<TileObj> tiles_{};
	std::vector<TileObj*> visibleTiles_{};
	int cols_{ 0 };
	int rows_{ 0 };
	int tw_{ 0 };
	int th_{ 0 };
	int _pitch{ 0 };
public:


	void Initialize(LevelName level);

	void SetupTileset(std::vector<int> tilesetDataType, sf::Vector2f texRectSize, const sf::Texture& texID, int numFrames, int pitch);
	void SetupTilemap(std::vector<int> tilesetTileNums, int cols, int rows, sf::Vector2f size_ = { 50.f, 50.f });

	std::vector<TileObj*>& getTiles();
	int Cols() { return cols_; }
	int Rows() { return rows_; }
	int TW() { return tw_; }
	int TH() { return th_; }

	void Render(sf::RenderWindow& wnd_, float dt_);
	void setPitch(int pitch_);
	int getPitch();
	void AddTile(TileObj& tile_);
	void AddTile(const sf::Texture& tex_, sf::IntRect texRect_, TileType type_, FunType fType_, bool empty_, sf::Vector2f pos_);
};