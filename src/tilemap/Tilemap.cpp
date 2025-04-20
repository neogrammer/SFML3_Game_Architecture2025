#include "Tilemap.h"
#include <utility>
#include <fstream>
#include <string>
#include <err/CidError.h>
#include <animation/Animation.h>
#include <iostream>
//
//void Tilemap::Initialize(LevelName level)
//{
//	TSET ts = GetTilesetData(level);
//	this->SetupTileset(ts.tileDataType, { (float)ts.tw,(float)ts.th }, ts.texID, ts.cols * ts.rows, ts.cols);
//	TMAP tmapData = GetLevelData(level);
//	this->SetupTilemap(tmapData.level, (int)tmapData.cols, (int)tmapData.rows, { (float)tmapData.tw, (float)tmapData.th });
//}

Tilemap::Tilemap(std::string tilesetFile_, std::string tilemapFile)
{
	std::ifstream iFile;
	iFile.open("Config/tilesets/" + tilesetFile_);

	if (!iFile.is_open() || !iFile.good())
		throw CidError(__LINE__, __FILE__, R"(Unable to open the file at location : $(ProjectDir)Config/tilesets/)" + tilesetFile_);
	else
	{
		std::string fileType;
		iFile >> fileType;

		if (fileType.substr(fileType.find_first_of('T'), (size_t)std::min(std::max((float)(fileType.length() - fileType.find_first_of('T')), 0.f), 7.f)) != "TILESET")
		{
			iFile.close();
			throw CidError(__LINE__, __FILE__, R"(Wrong file type for tileset!)");
		}
		else
		{

			//iFile >> theTexIDStr;

			//theTexID = TextureIDLUT[theTexIDStr];
			texID = Cfg::Textures::TilesetIntro;
			// tileset file loaded, now lets fill in the void
			iFile >> tilesheetPitch >> tilesheetNumTiles >> tw >> th;
			int rows = tilesheetNumTiles / tilesheetPitch;

			tilesetTiles_.reserve(tilesheetNumTiles);


			for (int y = 0; y < rows; y++)
			{
				for (int x = 0; x < tilesheetPitch; x++)
				{
					tilesetTiles_.push_back(std::make_shared<Tile>(texID, sf::IntRect{ sf::Vector2i{(int)(x * tw),(int)(y * th)}, sf::Vector2i{ (int)tw,(int)th} }, sf::Vector2f{ 0.f,0.f }, sf::Vector2f{ (float)tw,(float)th }, sf::Vector2f{ (float)(x * tw),(float)(y * th) }));
					tilesetTiles_.back()->setTexID(texID);
					tilesetTiles_.back()->setTW(tw);
					tilesetTiles_.back()->setTH(th);
					tilesetTiles_.back()->setTexRect(sf::IntRect{ sf::Vector2i{(int)(x * tw),(int)(y * th)}, sf::Vector2i{ (int)tw,(int)th} });

				}
			}

			for (int y = 0; y < rows; y++)
			{
				for (int x = 0; x < tilesheetPitch; x++)
				{
					int num;
					num = y * tilesheetPitch + x;

					int sol;

					iFile >> sol;

					tilesetTiles_[num]->setSolid(sol);
				}
			}

			for (int y = 0; y < rows; y++)
			{
				for (int x = 0; x < tilesheetPitch; x++)
				{
					int num;
					num = y * tilesheetPitch + x;

					int vis;

					iFile >> vis;

					tilesetTiles_[num]->setVisible(vis);
				}
			}

		}
		iFile.close();
	}



	std::ifstream iFile2;
	iFile2.open("Config/tilemaps/" + tilemapFile);


	if (!iFile2.is_open() || !iFile2.good())
		throw CidError(__LINE__, __FILE__, R"(Unable to open the file at location : $(ProjectDir)Config/tilemaps/)" + tilemapFile);
	else
	{
		std::string fileType;
		iFile2 >> fileType;

		if (fileType.substr(fileType.find_first_of('T'), (size_t)std::min(std::max((float)(fileType.length() - fileType.find_first_of('T')), 0.f), 7.f)) != "TILEMAP")
		{
			iFile2.close();
			throw CidError(__LINE__, __FILE__, R"(Wrong file type for tilemap!)");
		}
		else 
		{
			std::string tex;
			iFile2 >> tex >> cols >> rows;
			texID = TextureIDLUT[tex];
			for (int y = 0; y < rows; y++)
			{
				for (int x = 0; x < cols; x++)
				{
					int num;
					iFile2 >> num;
					int n = y * cols + x;
					std::unique_ptr<Tile> aTile = std::move(tilesetTiles_[num]->copyTile());

					tilemapTiles_.emplace_back(std::make_shared<Tile>(aTile->getTexID(), aTile->getWorldSize(), aTile->getTexRect().position, sf::Vector2f{ (float)(x * tw),(float)(y * th) }, aTile->isSolid(), aTile->isVisible()));

					if (aTile->isSolid())
					{
						std::shared_ptr<Tile> tileShared = tilemapTiles_.back();
						solidTiles_.push_back(tileShared);
					}
				}
			}
			iFile2.close(); 
		}	
	} 
}


std::vector<std::weak_ptr<Tile>>& Tilemap::getSolidTiles(sf::FloatRect testArea_)
{
	solidTiles_.clear();
	int left = std::max((int)testArea_.position.x / tw - 1, 0);
	int top = std::max((int)testArea_.position.y / th - 1, 0);
	int right = std::min((int)(testArea_.position.x + testArea_.size.x) / tw + 1, cols -1);
	int bottom = std::min((int)(testArea_.position.y + testArea_.size.y) / th + 1, rows -1);

	for (int y = top; y < bottom; y++)
	{
		for (int x = left; x < right; x++)
		{
			int index = y * cols + x;
			if (index > tilemapTiles_.size())
				break;
			if (tilemapTiles_[index]->isSolid())
			{
				solidTiles_.push_back(tilemapTiles_[index]);
			}
		}
	}

	return solidTiles_;
}

void Tilemap::Render(sf::RenderWindow& wnd_, float dt_)
{
	sf::View vw = wnd_.getView();

	auto center = vw.getCenter();
	auto left = (int)(center.x - (vw.getSize().x / 2.f));
	left /= (int)tilemapTiles_.at(0)->getWorldSize().x;
	left = std::max(left, 0);
	auto top = (int)(center.y - (vw.getSize().y / 2.f));
	top /= (int)tilemapTiles_.at(0)->getTexRect().size.y;
	top = std::max(top, 0);

	int numTilesX = (int)vw.getSize().x / tilemapTiles_.at(0)->getTexRect().size.x;
	int numTilesY = (int)vw.getSize().y / tilemapTiles_.at(0)->getTexRect().size.y;

	int right = (int)(left + numTilesX);
	int bottom = (int)(top + numTilesY);

	right = (int)std::max((float)std::min(right + 1, cols), 0.f);
	bottom = (int)std::max((float)std::min(bottom + 1, rows), 0.f);

	left = (int)((vw.getCenter().x - (int)(vw.getSize().x / 2.f)) / (float)tw);
	top = (int)((vw.getCenter().y - (int)(vw.getSize().y / 2.f)) / (float)th);
	right = left + 33;
	bottom = top + 19;

	for (int y = top; y < bottom; y++)
	{
		for (int x = left; x < right; x++)
		{
			int i = y * cols + x;
			if (i >= tilemapTiles_.size())
				break;
			if (tilemapTiles_[i]->isVisible())
			{
				wnd_.draw(*tilemapTiles_[i]);
			}
		}
	}

	/*for (int y = (int)top; y < bottom; y++)
	{
		if (y >= bottom - top)
			break;
		for (int x = (int)left; x < right; x++)
		{
			if (x >= right - left)
				break;
			int i = y * cols + x;
			if (i >= tilemapTiles_.size())
				break;
			if (tilemapTiles_[i]->isVisible())
			{
				wnd_.draw(*tilemapTiles_[i]);
			}
		}
	}*/
}