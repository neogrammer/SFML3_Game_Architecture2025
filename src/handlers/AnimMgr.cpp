#include "AnimMgr.h"

AnimMgr::AnimMgr()
{

}
AnimMgr::~AnimMgr()
{

}
void AnimMgr::allocateAnim(AnimName name_, Cfg::Textures  texID_, int numFrames_, float frameDelay_, bool loops_, bool loopWaits_, float loopWaitDelay_)
{
	animMap.emplace(name_, Animation{});

	animMap[name_].name = name_;
	animMap[name_].texID = texID_;
	animMap[name_].currState = AnimState::Playing;
	animMap[name_].frameDelay = frameDelay_;
	animMap[name_].loops = loops_;
	animMap[name_].loopWaits = loopWaits_;
	animMap[name_].loopWaitDelay = loopWaitDelay_;
	animMap[name_].numFrames = numFrames_;
	animMap[name_].playing = true;
	animMap[name_].previousState = AnimState::Playing;
	animMap[name_].transientState = AnimState::Playing;
}

AnimDir AnimMgr::getCurrDir()
{
	return currDir;
}

void AnimMgr::setCurrDir(AnimDir dir_)
{
	currDir = dir_;
}

int AnimMgr::getNumAnims()
{
	return (int)animMap.size();
}




void AnimMgr::AddLeftFrames(AnimName name_, Cfg::Textures texID_, int numFrames_, int numRows_, int startCol_, int startRow_, int pitch_, int frameW_, int frameH_, float frameDelay_, AnimSheetType sheetType_, int pad_, int spacer_, bool loops_, bool loopWaits_, float loopDelay_)
{



	auto found = this->animMap.find(name_);
	if (found == animMap.end()) { allocateAnim(name_, texID_, numFrames_, frameDelay_, loops_, loopWaits_, loopDelay_); }

	

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


			this->currDir = AnimDir::Left;

			this->currIndex = 0;

			this->currAnim = name_;
			switchAnim(name_, AnimDir::Left);
		

	}
}


void AnimMgr::AddRightFrames(AnimName name_, Cfg::Textures texID_, int numFrames_, int numRows_, int startCol_, int startRow_, int pitch_, int frameW_, int frameH_, float frameDelay_, AnimSheetType sheetType_, int pad_, int spacer_, bool loops_, bool loopWaits_, float loopDelay_)
{
	auto found = this->animMap.find(name_);
	if (found == animMap.end()) { allocateAnim(name_, texID_, numFrames_, frameDelay_, loops_, loopWaits_, loopDelay_); }

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
					animMap[name_].rightFrames.emplace_back(sf::IntRect{ {col * frameW_ + ((col * spacer_) + (col * (2 * pad_)) + pad_), row * frameH_ + ((row * spacer_) + (row * (2 * pad_)) + pad_)},{frameW_,frameH_} });
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
					animMap[name_].rightFrames.emplace_back(sf::IntRect{ {col * frameW_ + ((spacer_ * col) + (col * (2 * pad_)) + pad_), row * frameH_ + ((spacer_ * row) + (row * (2 * pad_)) + pad_)},{frameW_,frameH_} });
				}
				else if (sheetType_ == AnimSheetType::Normal)
				{
					animMap[name_].rightFrames.emplace_back(sf::IntRect{ {col * frameW_, row * frameH_},{frameW_,frameH_} });
				}

			}
		}

		this->currDir = AnimDir::Right;

		this->currIndex = 0;

		this->currAnim = name_;
		switchAnim(name_, AnimDir::Right);
	
	}
}

void AnimMgr::AddUniFrames(AnimName name_, Cfg::Textures texID_, int numFrames_, int numRows_, int startCol_, int startRow_, int pitch_, int frameW_, int frameH_, float frameDelay_, AnimSheetType sheetType_, int pad_, int spacer_, bool loops_, bool loopWaits_, float loopDelay_)
{

	auto found = this->animMap.find(name_);
	if (found == animMap.end()) { allocateAnim(name_, texID_, numFrames_, frameDelay_, loops_, loopWaits_, loopDelay_); }

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

			this->currDir = AnimDir::Uni;
		
			this->currIndex = 0;
	
			this->currAnim = name_;
			switchAnim(name_, AnimDir::Uni);
	
	}
}

Cfg::Textures AnimMgr::getTexID()
{
	return animMap[currAnim].texID;
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
	return animMap[currAnim].getWorldSize(currDir, currIndex);
}

void AnimMgr::reset()
{
	currIndex = 0;
	frameElapsed = 0.f;
	loopWaitElapsed = 0.f;
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

int AnimMgr::getCurrIndex()
{
	return currIndex;
}

int AnimMgr::getCurrNumFrames()
{
	return animMap[currAnim].getNumFrames();
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

void AnimMgr::resizeWorldSizes(AnimName animName_, AnimDir animDir_, int numFrames_)
{
	if (animMap.find(animName_) != animMap.end())
	{
		switch (animDir_)
		{
		case AnimDir::Left:
			animMap[animName_].leftSizes.resize(numFrames_);
			break;
		case AnimDir::Right:
			animMap[animName_].rightSizes.resize(numFrames_);
			break;
		case AnimDir::Uni:
			animMap[animName_].uniSizes.resize(numFrames_);
			break;
		default:
			break;
		}
	}
}

AnimName AnimMgr::getCurrAnimName()
{
	return currAnim;
}

void AnimMgr::resizeBulletPoints(AnimName aName, AnimDir aDir, int numFrames)
{
	if (animMap.find(aName) != animMap.end())
	{
		switch (aDir)
		{
		case AnimDir::Left:
			animMap[aName].leftBulletAnchors.resize(numFrames);
			break;
		case AnimDir::Right:
			animMap[aName].rightBulletAnchors.resize(numFrames);
			break;
		case AnimDir::Uni:
			animMap[aName].uniBulletAnchors.resize(numFrames);
			break;
		default:
			break;
		}
	}
}

void AnimMgr::setBulletAnchorPoint(AnimName aName, AnimDir aDir, int index, int numX, int numY)
{
	if (animMap.find(aName) != animMap.end())
	{
		switch (aDir)
		{
		case AnimDir::Left:
			if (index >= 0 && index < animMap[aName].leftBulletAnchors.size())
				animMap[aName].leftBulletAnchors[index] = { (float)numX,(float)numY };

			break;
		case AnimDir::Right:
			if (index >= 0 && index < animMap[aName].rightBulletAnchors.size())
				animMap[aName].rightBulletAnchors[index] = { (float)numX,(float)numY };

			break;
		case AnimDir::Uni:
			if (index >= 0 && index < animMap[aName].uniBulletAnchors.size())
				animMap[aName].uniBulletAnchors[index] = { (float)numX,(float)numY };
			break;
		default:
			break;
		}
	}
}

sf::Vector2f AnimMgr::getBulletPoint(AnimName aName, AnimDir aDir, int index)
{
	
	return animMap[aName].getBulletPoint(aDir, index);
}

void AnimMgr::setFrameWorldSize(AnimName animName_, AnimDir animDir_, int index_, int width_, int height_)
{
	if (animMap.find(animName_) != animMap.end())
	{
		switch (animDir_)
		{
		case AnimDir::Left:
			if (index_ >= 0 && index_ < animMap[animName_].leftSizes.size())
				animMap[animName_].leftSizes[index_] = { (float)width_,(float)height_ };

			break;
		case AnimDir::Right:
			if (index_ >= 0 && index_ < animMap[animName_].rightSizes.size())
				animMap[animName_].rightSizes[index_] = { (float)width_,(float)height_ };

			break;
		case AnimDir::Uni:
			if (index_ >= 0 && index_ < animMap[animName_].uniSizes.size())
				animMap[animName_].uniSizes[index_] = { (float)width_,(float)height_ };
			break;
		default:
			break;
		}
	}
}

void AnimMgr::setOffset(AnimName animName_, AnimDir animDir_, int index_, int x_, int y_)
{
	if (animMap.find(animName_) != animMap.end())
	{
		switch (animDir_)
		{
		case AnimDir::Left:
			if (index_ >= 0 && index_ < animMap[animName_].leftOffsets.size())
				animMap[animName_].leftOffsets[index_] = { (float)x_,(float)y_ };

			break;
		case AnimDir::Right:
			if (index_ >= 0 && index_ < animMap[animName_].rightOffsets.size())
				animMap[animName_].rightOffsets[index_] = { (float)x_,(float)y_ };

			break;
		case AnimDir::Uni:
			if (index_ >= 0 && index_ < animMap[animName_].uniOffsets.size())
				animMap[animName_].uniOffsets[index_] = { (float)x_,(float)y_ };
			break;
		default:
			break;
		}
	}
}

// call after loading frames or the size will be the frame size
void AnimMgr::setSize(AnimName animName_, AnimDir animDir_, int currIndex_, int sizeX, int sizeY)
{
	switch (animDir_)
	{
	case AnimDir::Left:
		animMap[animName_].leftSizes[currIndex_] = {(float)sizeX,(float)sizeY};

		break;
	case AnimDir::Right:
		animMap[animName_].rightSizes[currIndex_] = { (float)sizeX,(float)sizeY };
		break;
	case AnimDir::Uni:
		animMap[animName_].uniSizes[currIndex_] = { (float)sizeX,(float)sizeY };
		break;
	}
	
}

void AnimMgr::switchAnim(AnimName name_, AnimDir dir_)
{
	this->currAnim = name_;
	this->currDir = dir_;
	this->currIndex = 0;
}

sf::IntRect AnimMgr::getTexRect()
{
	return animMap[currAnim].getFrame(currDir, getCurrIndex());
}

void AnimMgr::pauseAnim()
{
	animMap[currAnim].playing = false;
}

void AnimMgr::resumeAnim()
{
	animMap[currAnim].playing = true;
}
