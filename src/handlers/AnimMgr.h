#ifndef ANIMMGR_H__
#define ANIMMGR_H__

#include <animation/Animation.h>
#include <core/resources/Cfg.h>
#include <map>

class AnimMgr
{
	AnimName currAnim{ AnimName::Invariant };
	int currIndex{ 0 };
	AnimDir currDir{AnimDir::Invariant};

	std::map<AnimName, Animation> animMap{};


	float frameElapsed{ 0.f };
	float loopWaitElapsed{ 0.f };
public:
	AnimMgr();
	~AnimMgr();
	AnimMgr(const AnimMgr&) = delete;
	AnimMgr& operator=(const AnimMgr&) = delete;
	AnimMgr(AnimMgr&&) = delete;
	AnimMgr& operator=(AnimMgr&&) = delete;


	void allocateAnim(AnimName name_, Cfg::Textures  texID_, int numFrames_, float frameDelay_, bool loops_, bool loopWaits_, float loopWaitDelay);
	AnimDir getCurrDir();
	void setCurrDir(AnimDir dir_);
	int getNumAnims();
	void AddLeftFrames(AnimName name_, Cfg::Textures texID_, int numFrames_, int numRows_, int startCol_, int startRow_, int pitch_,
		int frameW_, int frameH_, float frameDelay_, AnimSheetType sheetType_ = AnimSheetType::Normal, int pad_ = 0, int spacer_ = 0, 
		bool loops_ = true, bool loopWaits_ = false, float loopDelay_ = 0.f);
	void AddRightFrames(AnimName name_, Cfg::Textures texID_, int numFrames_, int numRows_, int startCol_, int startRow_, int pitch_, 
		int frameW_, int frameH_, float frameDelay_, AnimSheetType sheetType_ = AnimSheetType::Normal, int pad_ = 0 , int spacer_ = 0, 
		bool loops_ = true, bool loopWaits_ = false, float loopDelay_ = 0.f);
	void AddUniFrames(AnimName name_, Cfg::Textures texID_, int numFrames_, int numRows_, int startCol_, int startRow_, int pitch_,
		int frameW_, int frameH_, float frameDelay_, AnimSheetType sheetType_ = AnimSheetType::Normal, int pad_ = 0, int spacer_ = 0, 
		bool loops_ = true, bool loopWaits_ = false, float loopDelay_ = 0.f);
	Cfg::Textures getTexID();
	sf::IntRect currFrame();
	sf::Vector2f currOffset();
	sf::Vector2f currSize();

	void animate(float dt_);
	int getCurrIndex();
	void resizeOffsets(AnimName animName_, AnimDir animDir_, int numFrames_);
	void resizeWorldSizes(AnimName animName_, AnimDir animDir_, int numFrames_);
	AnimName getCurrAnimName();
	void resizeBulletPoints(AnimName aName, AnimDir aDir,int numFrames);
	void setBulletAnchorPoint(AnimName aName,AnimDir aDir,int index,int numX,int numY);
	sf::Vector2f getBulletPoint(AnimName aName, AnimDir aDir, int index);
	void setFrameWorldSize(AnimName aName_, AnimDir aDir_, int currFrameIndex_, int width_, int height_);
	void setOffset(AnimName animName_, AnimDir animDir_, int index_, int x_, int y_);
	void setSize(AnimName animName_, AnimDir animDir_, int currIndex_, int sizeX, int sizeY);
	void switchAnim(AnimName name_, AnimDir dir_);

};

#endif