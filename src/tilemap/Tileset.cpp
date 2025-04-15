#include "Tileset.h"

void Tileset::AddTile(std::unique_ptr<TileObj> tile_)
{
	auto& t = tiles_.emplace_back(std::make_unique<TileObj>(tile_->getTexture(), sf::IntRect{ (sf::Vector2i)tile_->getTexRect().position, tile_->getTexRect().size }, tile_->getType(), tile_->getFunType(), tile_->isEmpty(), tile_->getPos(), true, (sf::Vector2i)tile_->getSize()));
}

void Tileset::AddTile(const sf::Texture& tex_, sf::IntRect texRect_, TileType type_, FunType fType_, bool empty_, sf::Vector2f pos_)
{
	auto& t = tiles_.emplace_back(std::make_unique<TileObj>(tex_,texRect_,type_, fType_, empty_,pos_, true, texRect_.size));
}

void Tileset::setPitch(int pitch_)
{
	m_pitch = pitch_;
}

std::vector<std::unique_ptr<TileObj>>& Tileset::getTiles()
{
	return tiles_;
}

std::unique_ptr<TileObj> Tileset::copyTile(int index)
{
	auto& tile = tiles_.at(index);
	sf::Vector2i texRectPos = (sf::Vector2i)tile->getTexRect().position;
	sf::Vector2i texRectSize = (sf::Vector2i)tile->getTexRect().size;
	tile->setSize((sf::Vector2f)tile->getTexRect().size);
	const sf::Texture& texID = tile->getTexture();
	sf::Vector2i startPos = tile->getTexRect().position;
	int pitch = (int)(tiles_.size() / (size_t)texRectSize.y);
	m_pitch = pitch;
	sf::Vector2f pos = tile->getPos();

	std::unique_ptr<TileObj> aTile = std::make_unique<TileObj>(texID, sf::IntRect{ texRectPos, texRectSize }, tile->getType(), tile->getFunType(), tile->isEmpty(), pos, false, (sf::Vector2i)tile->getSize());
	aTile->setSize((sf::Vector2f)tile->getTexRect().size);
	return std::move(aTile);
}


