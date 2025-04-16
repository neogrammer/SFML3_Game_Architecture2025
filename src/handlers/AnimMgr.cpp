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
	texIDs[name_] = texID_;
	animMap[name_].name = name_;
}


void AnimMgr::AddLeftFrames(AnimName name_, Cfg::Textures texID_, int numFrames_, int numRows_, int startCol_, int startRow_, int pitch_, int frameW_, int frameH_, float frameDelay_, AnimSheetType sheetType_, int pad_, int spacer_, bool loops_, bool loopWaits_, float loopDelay_)
{
	if (animMap.find(name_) == animMap.end())
	{
		allocateAnim(name_,texID_);

	}
	

	if (animMap[name_].leftFrames.empty())
	{
		animMap[name_].leftFrames.clear();
	

		animMap[name_].leftFrames.reserve(numFrames_);
		animMap[name_].numFrames = numFrames_;


		for (int row = startRow_; row < startRow_ + 1; row++)
		{
			for (int col = startCol_; col < pitch_ && (row * pitch_ + col) - (startRow_ * pitch_ + startCol_) < numFrames_; col++)
			{
				if (sheetType_ == AnimSheetType::Padded)
				{
					animMap[name_].leftFrames.emplace_back(sf::IntRect{ {col * frameW_ + ((spacer_*col) + (col * (2 * pad_)) + pad_), row * frameH_ + ((spacer_ * row) + (row * (2 * pad_)) + pad_)},{frameW_,frameH_}});
				}
				else if (sheetType_ == AnimSheetType::Normal)
				{
					animMap[name_].leftFrames.emplace_back(sf::IntRect{ {col * frameW_, row * frameH_},{frameW_,frameH_} });
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
				}
				else if (sheetType_ == AnimSheetType::Normal)
				{
					animMap[name_].leftFrames.emplace_back(sf::IntRect{ {col * frameW_, row * frameH_},{frameW_,frameH_} });
				}

			}
		}
		worldSizeMap.clear();
		worldSizeMap.emplace(name_, sf::Vector2f{});
		worldSizeMap[name_] = { (float)frameW_,(float)frameH_ };
		animMap[name_].loops = loops_;
		animMap[name_].loopWaits = loopWaits_;
		animMap[name_].loopWaitDelay = loopDelay_;
		animMap[name_].frameDelay = frameDelay_;
		animMap[name_].texID = texID_;
		this->currAnim = name_;
		this->currDir = AnimDir::Left;
		this->currIndex = 0;
		this->currTex = texIDs[name_];
	

	}
}


void AnimMgr::AddRightFrames(AnimName name_, Cfg::Textures texID_, int numFrames_, int numRows_, int startCol_, int startRow_, int pitch_, int frameW_, int frameH_, float frameDelay_, AnimSheetType sheetType_, int pad_, int spacer_, bool loops_, bool loopWaits_, float loopDelay_)
{

	if (animMap.find(name_) == animMap.end())
	{
		allocateAnim(name_,texID_);

	}
	if (animMap[name_].rightFrames.empty())
	{
		animMap[name_].rightFrames.clear();
		animMap[name_].rightFrames.reserve(numFrames_);
		animMap[name_].numFrames = numFrames_;

		for (int row = startRow_; row < startRow_ + 1; row++)
		{
			for (int col = startCol_; col < pitch_ && (row * pitch_ + col) - (startRow_ * pitch_ + startCol_) < numFrames_; col++)
			{
				if (sheetType_ == AnimSheetType::Padded)
				{
					animMap[name_].rightFrames.emplace_back(sf::IntRect{ {col * frameW_ + ((col*spacer_)+(col * (2 * pad_)) + pad_), row * frameH_ + ((row*spacer_)+(row * (2 * pad_)) + pad_)},{frameW_,frameH_} });
				}
				else if (sheetType_ == AnimSheetType::Normal)
				{
					animMap[name_].rightFrames.emplace_back(sf::IntRect{ {col * frameW_, row * frameH_},{frameW_,frameH_} });
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
				}
				else if (sheetType_ == AnimSheetType::Normal)
				{
					animMap[name_].rightFrames.emplace_back(sf::IntRect{ {col * frameW_, row * frameH_},{frameW_,frameH_} });
				}

			}
		}

		worldSizeMap.clear();
		worldSizeMap.emplace(name_, sf::Vector2f{});
		worldSizeMap[name_] = { (float)frameW_,(float)frameH_ };
		animMap[name_].loops = loops_;
		animMap[name_].loopWaits = loopWaits_;
		animMap[name_].loopWaitDelay = loopDelay_;
		animMap[name_].frameDelay = frameDelay_;
		animMap[name_].texID = texID_;

		this->currAnim = name_;
		this->currDir = AnimDir::Right;
		this->currIndex = 0;
		this->currTex = texIDs[name_];

	}
}

void AnimMgr::AddUniFrames(AnimName name_, Cfg::Textures texID_, int numFrames_, int numRows_, int startCol_, int startRow_, int pitch_, int frameW_, int frameH_, float frameDelay_, AnimSheetType sheetType_, int pad_, int spacer_, bool loops_, bool loopWaits_, float loopDelay_)
{
	if (animMap.find(name_) == animMap.end())
	{
		allocateAnim(name_,texID_);

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
				}
				else if (sheetType_ == AnimSheetType::Normal)
				{
					animMap[name_].uniFrames.emplace_back(sf::IntRect{ {col * frameW_, row * frameH_},{frameW_,frameH_} });
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
					
				}
				else if (sheetType_ == AnimSheetType::Normal)
				{
					animMap[name_].uniFrames.emplace_back(sf::IntRect{ {col * frameW_, row * frameH_},{frameW_,frameH_} });
				}

			}
		}
		worldSizeMap.clear();
		worldSizeMap.emplace(name_, sf::Vector2f{});
		worldSizeMap[name_] = { (float)frameW_,(float)frameH_ };
		animMap[name_].loops = loops_;
		animMap[name_].loopWaits = loopWaits_;
		animMap[name_].loopWaitDelay = loopDelay_;
		animMap[name_].frameDelay = frameDelay_;
		animMap[name_].texID = texID_;

		this->currAnim = name_;
		this->currDir = AnimDir::Uni;
		this->currIndex = 0;
		this->currTex = texIDs[name_];

	}
}

Cfg::Textures AnimMgr::getTexID()
{
	return texIDs[currAnim];
}

sf::IntRect AnimMgr::currFrame()
{
	return animMap[currAnim].getFrame(currDir, currIndex);
}

sf::Vector2f AnimMgr::currOffset()
{

	return animMap[currAnim].getOffset(currDir, currIndex);
}

sf::Vector2f AnimMgr::currSize()
{
	return worldSizeMap[currAnim];
}

void AnimMgr::animate(float dt_)
{
	if (animMap[currAnim].playing)
	{
		if (!animMap[currAnim].loopWaits)
		{
			frameElapsed += dt_;
			if (frameElapsed >= animMap[currAnim].frameDelay)
			{
				frameElapsed = 0.f;
				if (++currIndex >= animMap[currAnim].numFrames)
				{

					if (animMap[currAnim].loops)
						currIndex = 0;
					else
						currIndex = animMap[currAnim].numFrames - 1;
				}
			}
		}
		else
		{
			// does loop wait
			

			if (currIndex == animMap[currAnim].numFrames - 1)
			{
				// currently loopWaiting, increment the timer
				loopWaitElapsed += dt_;

				if (loopWaitElapsed >= animMap[currAnim].loopWaitDelay)
				{
					loopWaitElapsed = 0.f;
					frameElapsed = 0.f;
					if (animMap[currAnim].loops)
						currIndex = 0;
					else
						currIndex = animMap[currAnim].numFrames - 1;
				}
			}
			else
			{
				
				frameElapsed += dt_;
				if (frameElapsed >= animMap[currAnim].frameDelay)
				{
					++currIndex;
				
					frameElapsed = 0.f;

					if (currIndex >= animMap[currAnim].numFrames)
					{
						loopWaitElapsed = 0.f;
						currIndex = animMap[currAnim].numFrames - 1;
					}
				}
			}
		}
	}
}

void AnimMgr::resizeOffsets(AnimName animName_, AnimDir animDir_, int numFrames_)
{
	if (animMap.find(animName_) != animMap.end())
	{
		switch (animDir_)
		{
		case AnimDir::Left:
			animMap[animName_].leftOffsets.resize(numFrames_);
			break;
		case AnimDir::Right:
			animMap[animName_].rightOffsets.resize(numFrames_);
			break;
		case AnimDir::Uni:
			animMap[animName_].uniOffsets.resize(numFrames_);
			break;
		default:
			break;
		}
	}
}

void AnimMgr::setOffset(AnimName animName_, AnimDir animDir_, int index_, int x_, int y_)
{
	switch (animDir_)
	{
	case AnimDir::Left:
		animMap[animName_].leftOffsets[index_] = { (float)x_,(float)y_ };

		break;
	case AnimDir::Right:
		animMap[animName_].rightOffsets[index_] = { (float)x_,(float)y_ };

		break;
	case AnimDir::Uni:
		animMap[animName_].uniOffsets[index_] = { (float)x_,(float)y_ };
		break;
	default:
		break;
	}
}

// call after loading frames or the size will be the frame size
void AnimMgr::setSize(AnimName animName_, int sizeX, int sizeY)
{
	this->worldSizeMap[animName_] = {(float)sizeX,(float)sizeY};
}

void AnimMgr::switchAnim(AnimName name_, AnimDir dir_)
{
	this->currAnim = name_;
	this->currDir = dir_;
	this->currIndex = 0;
	this->currTex = texIDs[name_];

}
