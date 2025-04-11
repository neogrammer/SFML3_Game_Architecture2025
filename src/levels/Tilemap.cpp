#include "Tilemap.h"
#include <utility>
void Tilemap::Initialize(LevelName level)
{
	TSET ts = GetTilesetData(level);
	this->SetupTileset(ts.tileDataType, { (float)ts.tw,(float)ts.th }, ts.texID, ts.cols * ts.rows, ts.cols);
	TMAP tmapData = GetLevelData(level);
	this->SetupTilemap(tmapData.level, (int)tmapData.cols, (int)tmapData.rows, { (float)tmapData.tw, (float)tmapData.th });
}

void Tilemap::SetupTileset(std::vector<int> tilesetDataType, sf::Vector2f texRectSize, const sf::Texture& texID, int numFrames, int pitch)
{
	if (tilesetDataType.empty())
		return;

	

	for (int y = 0; y < numFrames / pitch; y++)
	{
		for (int x = 0; x < pitch; x++)
		{
			int num = y * pitch + x;
			int theType = tilesetDataType[num];
			tset_.setPitch(pitch);
			TileType type;
			FunType fType;
			if (theType == (int)TileType::AnimatedAndEmpty || theType == (int)TileType::VisibleAndEmpty || theType == (int)TileType::InvisibleAndEmpty)
			{
				type = TileType::VisibleAndEmpty;
				fType = FunType::MapTile;
				tset_.AddTile(texID, sf::IntRect{ sf::Vector2i{ (int)(x * (int)texRectSize.x), (int)(y * (int)texRectSize.y) }, sf::Vector2i(texRectSize) }, type, fType, true, { (float)x * texRectSize.x, (float)y * texRectSize.y });
				tset_.getTiles().at(y * pitch + x)->setPos({(float)x * (float)texRectSize.x, (float)y* (float)texRectSize.y});
				tset_.getTiles().at(y * pitch + x)->setPrevPos({ x * texRectSize.x,y * texRectSize.y });
				tset_.getTiles().at(y * pitch + x)->setSize( texRectSize );

			}
			else
			{
				type = TileType::VisibleAndSolid;
				fType = FunType::MapTile;
				tset_.AddTile(texID, sf::IntRect{ sf::Vector2i{ (int)(x * (int)texRectSize.x), (int)(y * (int)texRectSize.y) }, sf::Vector2i(texRectSize) }, type, fType, true, { (float)x * texRectSize.x, (float)y * texRectSize.y });
				tset_.getTiles().at(y * pitch + x)->setPos({ (float)x * (float)texRectSize.x, (float)y * (float)texRectSize.y });
				tset_.getTiles().at(y * pitch + x)->setPrevPos({ x * texRectSize.x,y * texRectSize.y });
				tset_.getTiles().at(y * pitch + x)->setSize(texRectSize);
			}
		}
	}
}

void Tilemap::SetupTilemap(std::vector<int> tilesetTileNums, int cols, int rows, sf::Vector2f size_)
{
	cols_ = cols;
	rows_ = rows;
	tw_ = (int)size_.x;
	th_ = (int)size_.y;

	if (tset_.getTiles().empty())
		return;

	
		std::vector<std::unique_ptr<TileObj>>& tileset = tset_.getTiles();
		tiles_.clear();
		tiles_.reserve(cols * rows);
		for (int y = 0; y < rows; y++)
		{
			for (int x = 0; x < cols; x++)
			{
				int num = tilesetTileNums[y * cols + x];
				if (num >= tset_.getTiles().size())
				{
					continue;
				}
				//std::unique_ptr<Tile> aTile = std::move(tset_.copyTile(num));
//				std::unique_ptr<TileObj> aTile = std::move(tset_.copyTile(num));

				const auto& tex = tileset.at(num)->getTexture();
				sf::IntRect texRect = sf::IntRect{ (sf::Vector2i)tileset.at(num)->getTexRect().position, (sf::Vector2i)tileset.at(num)->getTexRect().size };
				int pitch = cols;
				TileType type = tileset.at(num)->getType();
				bool empty = tileset.at(num)->isEmpty();

				FunType fType = tileset.at(num)->getFunType();


				//tiles_.push_back(TileObj{ tex, texRect, type, fType, empty,sf::Vector2f{(float)(x * texRect.size.x),(float)(y * texRect.size.y)}, false,   texRect.size });
				TileObj tmp{ tex, texRect, type, fType, empty, sf::Vector2f{ ((float)x * (float)texRect.size.x),((float)y * (float)texRect.size.y) }, false, texRect.size };
				AddTile(tmp);
				tiles_.at(static_cast<std::vector<TileObj, std::allocator<TileObj>>::size_type>(y) * pitch + x).setPos({ (float)x * (float)texRect.size.x, (float)y * (float)texRect.size.y });
				tiles_.at(static_cast<std::vector<TileObj, std::allocator<TileObj>>::size_type>(y) * pitch + x).setPrevPos({ (float)x * (float)texRect.size.x,(float)y * (float)texRect.size.y });
				tiles_.at(static_cast<std::vector<TileObj, std::allocator<TileObj>>::size_type>(y) * pitch + x).setSize((sf::Vector2f)texRect.size);
				//(sf::Vector2f)aTile->getTexRectSize(), aTile->getTextureID(), (sf::Vector2f)aTile->getTexPos(), aTile->getPitch(), aTile->isVisible(), aTile->getType()
					//tiles_.at(y*cols+x).setType(tiles_.back().isSolid(), tiles_.back().isVisible(), tiles_.back().isAnimated());
				if (tiles_.at(static_cast<std::vector<TileObj, std::allocator<TileObj>>::size_type>(y) * cols + x).getType() == TileType::VisibleAndEmpty || tiles_.at(y * cols + x).getType() == TileType::VisibleAndSolid ||
					tiles_.at(static_cast<std::vector<TileObj, std::allocator<TileObj>>::size_type>(y) * cols + x).getType() == TileType::AnimatedAndEmpty || tiles_.at(y * cols + x).getType() == TileType::AnimatedAndSolid)
				{
						visibleTiles_.push_back(&tiles_[tiles_.size() - 1]);
				}
			}
		}
		/*for (int y = 0; y < rows; y++)
		{
			for (int x = 0; x < cols; x++)
			{
				tiles_[y * cols + x].SetPosition({ (float)x * size_.x, (float)y * size_.y });

			}
		}*/
	
}

std::vector<TileObj*>& Tilemap::getTiles()
{
	return visibleTiles_;
}

void Tilemap::Render(sf::RenderWindow& wnd_, float dt_)
{
	sf::View vw = wnd_.getView();

	auto center = vw.getCenter();
	auto left = center.x - (vw.getSize().x / 2.f);
	left /= tiles_.at(0).getTexRect().size.x;
	left = std::max(left, 0.f);
	auto top = center.y - (vw.getSize().y / 2.f);
	top /= tiles_.at(0).getTexRect().size.y;
	top = std::max(top, 0.f);

	int numTilesX = (int)vw.getSize().x / tiles_.at(0).getTexRect().size.x;
	int numTilesY = (int)vw.getSize().y / tiles_.at(0).getTexRect().size.y;

	int right = (int)(left + numTilesX);
	int bottom = (int)(top + numTilesY);

	right = (int)std::max((float)std::min(right + 1, cols_), 0.f);
	bottom = (int)std::max((float)std::min(bottom + 1, rows_), 0.f);


	for (int y = (int)top; y < bottom; y++)
	{
		if (y >= bottom - top)
			break;
		for (int x = (int)left; x < right; x++)
		{
			if (x >= right - left)
				break;
			int i = y * cols_ + x;
			if (i >= tiles_.size())
				break;
			tiles_[i].render(wnd_);
		}
	}
}

void Tilemap::AddTile(TileObj& tile_)
{
	//std::unique_ptr<TileObj> tmp = std::make_unique<TileObj>((sf::Texture&)tile_->getTexture(), sf::IntRect{ (sf::Vector2i)tile_->getTexRect().position, (sf::Vector2i)tile_->getTexRect().size }, (TileType)tile_->getType(), (FunType)tile_->getFunType(), (bool)tile_->isEmpty(), (sf::Vector2f)tile_->getPos(), true, (sf::Vector2i)tile_->getSize());
	auto& t = tiles_.emplace_back(TileObj{});
	t.init((sf::Texture&)tile_.getTexture(), sf::IntRect{ (sf::Vector2i)tile_.getTexRect().position, (sf::Vector2i)tile_.getTexRect().size }, (TileType)tile_.getType(), (FunType)tile_.getFunType(), (bool)tile_.isEmpty(), (sf::Vector2f)tile_.getPos(), false, (sf::Vector2i)tile_.getSize());
	t.setTexRect(tile_.getTexRect());
	t.setPos(tile_.getPos());
	t.setType(tile_.isSolid(), tile_.isVisible(), tile_.isAnimated());
	t.setFunType(tile_.getFunType());
	t.setFacingRight(tile_.isFacingRight());
	t.setFrameDelay(tile_.getFrameDelay());
	t.setSize(tile_.getSize());


		
}

void Tilemap::AddTile(const sf::Texture& tex_, sf::IntRect texRect_, TileType type_, FunType fType_, bool empty_, sf::Vector2f pos_)
{
	//std::unique_ptr<TileObj> tmp = std::make_unique<TileObj>(tex_, texRect_, type_, fType_, empty_, pos_, true, texRect_.size);

	//tiles_.emplace_back(std::move(tmp));

	auto& tile = tiles_.emplace_back(TileObj{});
	tile.init((sf::Texture&)tex_, texRect_, type_, fType_, empty_, pos_, false, texRect_.size);

}

void Tilemap::setPitch(int pitch_)
{
	_pitch = pitch_;
}

int Tilemap::getPitch()
{
	return _pitch;
}
