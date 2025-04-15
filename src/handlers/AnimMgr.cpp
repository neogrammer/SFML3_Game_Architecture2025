#include "AnimMgr.h"

AnimMgr::AnimMgr()
{

}
AnimMgr::~AnimMgr()
{

}
void AnimMgr::allocateAnim(AnimName name_, Cfg::Textures  texID_)
{
	animMap.emplace(name_, Animation{});
	worldSizeMap.emplace(name_, std::vector<sf::Vector2f>{});
	texIDs[name_] = texID_;
	animMap[name_].name = name_;
}


void AnimMgr::AddLeftFrames(AnimName name_, Cfg::Textures texID_, int numFrames_, int numRows_, int startCol_, int startRow_, int pitch_, int frameW_, int frameH_, AnimSheetType sheetType_, int pad_, int spacer_, bool loopWaits_, float loopDelay_)
{
	if (animMap.find(name_) == animMap.end())
	{
		allocateAnim(name_,texID_);
		this->texIDs[name_] = texID_;

	}

	if (animMap[name_].leftFrames.empty())
	{
		animMap[name_].leftFrames.clear();
		worldSizeMap.clear();
		worldSizeMap.emplace(name_, std::vector<sf::Vector2f>{});
		
	

		animMap[name_].leftFrames.reserve(numFrames_);
		animMap[name_].numFrames = numFrames_;


		for (int row = startRow_; row < startRow_ + 1; row++)
		{
			for (int col = startCol_; col < pitch_ && (row * pitch_ + col) - (startRow_ * pitch_ + startCol_) < numFrames_; col++)
			{
				if (sheetType_ == AnimSheetType::Padded)
				{
					animMap[name_].leftFrames.emplace_back(sf::IntRect{ {col * frameW_ + ((spacer_*col) + (col * (2 * pad_)) + pad_), row * frameH_ + ((spacer_ * row) + (row * (2 * pad_)) + pad_)},{frameW_,frameH_}});
					worldSizeMap[name_].push_back({ (float)frameW_,(float)frameH_ });
				}
				else if (sheetType_ == AnimSheetType::Normal)
				{
					animMap[name_].leftFrames.emplace_back(sf::IntRect{ {col * frameW_, row * frameH_},{frameW_,frameH_} });
					worldSizeMap[name_].push_back({ (float)frameW_,(float)frameH_ });
				}
			}
		}
		for (int row = startRow_ + 1; row < numRows_; row++)
		{
			for (int col = 0; col < pitch_ && (row * pitch_ + col) - (startRow_ * pitch_ + startCol_) < numFrames_; col++)
			{
				if (sheetType_ == AnimSheetType::Padded)
				{
					animMap[name_].leftFrames.emplace_back(sf::IntRect{ {col * frameW_ + ((spacer_ * col) + (col * (2 * pad_)) + pad_), row * frameH_ + ((spacer_ * row) + (row * (2 * pad_)) + pad_)},{frameW_,frameH_} });
					worldSizeMap[name_].push_back({ (float)frameW_,(float)frameH_ });
				}
				else if (sheetType_ == AnimSheetType::Normal)
				{
					animMap[name_].leftFrames.emplace_back(sf::IntRect{ {col * frameW_, row * frameH_},{frameW_,frameH_} });
					worldSizeMap[name_].push_back({ (float)frameW_,(float)frameH_ });
				}

			}
		}

		this->currAnim = name_;
		this->currDir = AnimDir::Left;
		this->currIndex = 0;
	

	}
}


void AnimMgr::AddRightFrames(AnimName name_, Cfg::Textures texID_, int numFrames_, int numRows_, int startCol_, int startRow_, int pitch_, int frameW_, int frameH_, AnimSheetType sheetType_, int pad_, int spacer_, bool loopWaits_, float loopDelay_)
{

	if (animMap.find(name_) == animMap.end())
	{
		allocateAnim(name_,texID_);
		this->texIDs[name_] = texID_;

	}

	if (animMap[name_].rightFrames.empty())
	{
		animMap[name_].rightFrames.clear();
		animMap[name_].rightFrames.reserve(numFrames_);
		animMap[name_].numFrames = numFrames_;
		animMap[name_].frameDelay = 0.24f;

		for (int row = startRow_; row < startRow_ + 1; row++)
		{
			for (int col = startCol_; col < pitch_ && (row * pitch_ + col) - (startRow_ * pitch_ + startCol_) < numFrames_; col++)
			{
				if (sheetType_ == AnimSheetType::Padded)
				{
					animMap[name_].rightFrames.emplace_back(sf::IntRect{ {col * frameW_ + ((col*spacer_)+(col * (2 * pad_)) + pad_), row * frameH_ + ((row*spacer_)+(row * (2 * pad_)) + pad_)},{frameW_,frameH_} });
					worldSizeMap[name_].push_back({ (float)frameW_,(float)frameH_ });
				}
				else if (sheetType_ == AnimSheetType::Normal)
				{
					animMap[name_].rightFrames.emplace_back(sf::IntRect{ {col * frameW_, row * frameH_},{frameW_,frameH_} });
					worldSizeMap[name_].push_back({ (float)frameW_,(float)frameH_ });
				}
			}
		}
		for (int row = startRow_ + 1; row < numRows_; row++)
		{
			for (int col = 0; col < pitch_ && (row * pitch_ + col) - (startRow_ * pitch_ + startCol_) < numFrames_; col++)
			{
				if (sheetType_ == AnimSheetType::Padded)
				{
					animMap[name_].rightFrames.emplace_back(sf::IntRect{ {col * frameW_ + ((spacer_*col)+(col * (2 * pad_)) + pad_), row * frameH_ + ((spacer_*row) + (row * (2 * pad_)) + pad_)},{frameW_,frameH_}});
					worldSizeMap[name_].push_back({ (float)frameW_,(float)frameH_ });
				}
				else if (sheetType_ == AnimSheetType::Normal)
				{
					animMap[name_].rightFrames.emplace_back(sf::IntRect{ {col * frameW_, row * frameH_},{frameW_,frameH_} });
					worldSizeMap[name_].push_back({ (float)frameW_,(float)frameH_ });
				}

			}
		}

		this->currAnim = name_;
		this->currDir = AnimDir::Right;
		this->currIndex = 0;
	}
}

void AnimMgr::AddUniFrames(AnimName name_, Cfg::Textures texID_, int numFrames_, int numRows_, int startCol_, int startRow_, int pitch_, int frameW_, int frameH_, AnimSheetType sheetType_, int pad_, int spacer_, bool loopWaits_, float loopDelay_)
{
	if (animMap.find(name_) == animMap.end())
	{
		allocateAnim(name_,texID_);
		this->texIDs[name_] = texID_;

	}

	if (animMap[name_].uniFrames.empty())
	{
		animMap[name_].uniFrames.clear();
		animMap[name_].uniFrames.reserve(numFrames_);
		animMap[name_].numFrames = numFrames_;

		for (int row = startRow_; row < startRow_ + 1; row++)
		{
			for (int col = startCol_; col < pitch_ && (row * pitch_ + col) - (startRow_ * pitch_ + startCol_) < numFrames_; col++)
			{
				if (sheetType_ == AnimSheetType::Padded)
				{
					animMap[name_].uniFrames.emplace_back(sf::IntRect{ {col * frameW_ + ((spacer_ * col) + (col * (2 * pad_)) + pad_), row * frameH_ + ((spacer_ * row) + (row * (2 * pad_)) + pad_)}, {frameW_,frameH_} });
					worldSizeMap[name_].push_back({ (float)frameW_,(float)frameH_ });
				}
				else if (sheetType_ == AnimSheetType::Normal)
				{
					animMap[name_].uniFrames.emplace_back(sf::IntRect{ {col * frameW_, row * frameH_},{frameW_,frameH_} });
					worldSizeMap[name_].push_back({ (float)frameW_,(float)frameH_ });
				}

			}
		}
		for (int row = startRow_ + 1; row < numRows_; row++)
		{
			for (int col = 0; col < pitch_ && (row * pitch_ + col) - (startRow_ * pitch_ + startCol_) < numFrames_; col++)
			{

				if (sheetType_ == AnimSheetType::Padded)
				{
					animMap[name_].uniFrames.emplace_back(sf::IntRect{ {col * frameW_ + ((spacer_ * col) + (col * (2 * pad_)) + pad_), row * frameH_ + ((spacer_ * row) + (row * (2 * pad_)) + pad_)},{frameW_,frameH_}});
					worldSizeMap[name_].push_back({ (float)frameW_,(float)frameH_ });
				}
				else if (sheetType_ == AnimSheetType::Normal)
				{
					animMap[name_].uniFrames.emplace_back(sf::IntRect{ {col * frameW_, row * frameH_},{frameW_,frameH_} });
					worldSizeMap[name_].push_back({ (float)frameW_,(float)frameH_ });
				}

			}
		}

		this->currAnim = name_;
		this->currDir = AnimDir::Uni;
		this->currIndex = 0;
	}
}

Cfg::Textures AnimMgr::getTexID()
{
	return texIDs[currAnim];
}

sf::IntRect AnimMgr::currFrame()
{
	switch (currDir)
	{
	case AnimDir::Left:
	{
		return animMap[currAnim].leftFrames.at(currIndex);
	}
		break;
	case AnimDir::Right:
	{
		return animMap[currAnim].rightFrames.at(currIndex);

	}
	break;
	case AnimDir::Uni:
	{
		return animMap[currAnim].uniFrames.at(currIndex);

	}
	break;
	default:
	{}
	break;
	}
}

sf::Vector2f AnimMgr::currOffset()
{
	switch (currDir)
	{
	case AnimDir::Left:
	{
		return animMap[currAnim].leftOffsets.at(currIndex);
	}
	break;
	case AnimDir::Right:
	{
		return animMap[currAnim].rightOffsets.at(currIndex);

	}
	break;
	case AnimDir::Uni:
	{
		return animMap[currAnim].uniOffsets.at(currIndex);

	}
	break;
	default:
	{}
	break;
	}
}

sf::Vector2f AnimMgr::currSize()
{
	return worldSizeMap[currAnim].at(currIndex);
}

void AnimMgr::animate(float dt_)
{
	frameElapsed += dt_;
	if (frameElapsed >= animMap[currAnim].frameDelay)
	{
		frameElapsed = 0.f;
		if (++currIndex >= animMap[currAnim].numFrames)
		{
			currIndex = 0;
		}
	}
}
