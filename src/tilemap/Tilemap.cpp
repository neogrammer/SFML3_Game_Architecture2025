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
			Cfg::Textures theTexID;
			std::string theTexIDStr;
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

					std::cout << n << "\n" << num << std::endl;


					tilemapTiles_.emplace_back(std::make_shared<Tile>(tilesetTiles_[num]->getTexID(), tilesetTiles_[num]->getTexRect(), sf::Vector2f{ 0.f,0.f }, tilesetTiles_[num]->getWorldSize(), sf::Vector2f({ (float)(x * tw), (float)(y * th) })));
					
					tilemapTiles_.back()->setSolid(tilesetTiles_[num]->isSolid());
					tilemapTiles_.back()->setVisible(tilesetTiles_[num]->isVisible());
					tilemapTiles_.back()->setTW(tw);
					tilemapTiles_.back()->setTH(th);

					//tilemapTiles_.back()->setWorldSize({ 50.f,50.f });


					
				/*	if (tilesetTiles_[num]->isVisible())
					{
						visibleTiles_.push_back(tilemapTiles_[num]);
					}*/
				}
			
			}

			iFile2.close(); 
		}	

	} 
}


std::vector<std::weak_ptr<Tile>>& Tilemap::getVisibleTiles()
{
	return visibleTiles_;
}

void Tilemap::Render(sf::RenderWindow& wnd_, float dt_)
{
	sf::View vw = wnd_.getView();

	auto center = vw.getCenter();
	auto left = center.x - (vw.getSize().x / 2.f);
	left /= tilemapTiles_.at(0)->getWorldSize().x;
	left = std::max(left, 0.f);
	auto top = center.y - (vw.getSize().y / 2.f);
	top /= tilemapTiles_.at(0)->getTexRect().size.y;
	top = std::max(top, 0.f);

	int numTilesX = (int)vw.getSize().x / tilemapTiles_.at(0)->getTexRect().size.x;
	int numTilesY = (int)vw.getSize().y / tilemapTiles_.at(0)->getTexRect().size.y;

	int right = (int)(left + numTilesX);
	int bottom = (int)(top + numTilesY);

	right = (int)std::max((float)std::min(right + 1, cols), 0.f);
	bottom = (int)std::max((float)std::min(bottom + 1, rows), 0.f);

	for (auto& t : tilemapTiles_)
	{
		wnd_.draw(*(t.get()));
	}

	for (int y = (int)top; y < bottom; y++)
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
			//wnd_.draw(*tilemapTiles_[i]);
		}
	}
}