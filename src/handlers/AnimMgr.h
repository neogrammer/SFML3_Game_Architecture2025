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
	std::map<AnimName, std::vector<sf::Vector2f> > worldSizeMap{};
	std::map<AnimName, Cfg::Textures> texIDs{};


	float frameElapsed{ 0.f };
	float loopWaitElapsed{ 0.f };
public:
	AnimMgr();
	~AnimMgr();
	AnimMgr(const AnimMgr&) = delete;
	AnimMgr& operator=(const AnimMgr&) = delete;
	AnimMgr(AnimMgr&&) = delete;
	AnimMgr& operator=(AnimMgr&&) = delete;

	void allocateAnim(AnimName name_, Cfg::Textures  texID_);

	void AddLeftFrames(AnimName name_, Cfg::Textures texID_, int numFrames_, int numRows_, int startCol_, int startRow_, int pitch_, int frameW_, int frameH_, AnimSheetType sheetType_ = AnimSheetType::Normal, int pad_ = 0, int spacer_ = 0, bool loopWaits_=false, float loopDelay_ = 0.f);
	void AddRightFrames(AnimName name_, Cfg::Textures texID_, int numFrames_, int numRows_, int startCol_, int startRow_, int pitch_, int frameW_, int frameH_, AnimSheetType sheetType_ = AnimSheetType::Normal, int pad_ = 0 , int spacer_ = 0, bool loopWaits_=false, float loopDelay_=0.f);
	void AddUniFrames(AnimName name_, Cfg::Textures texID_, int numFrames_, int numRows_, int startCol_, int startRow_, int pitch_, int frameW_, int frameH_, AnimSheetType sheetType_ = AnimSheetType::Normal, int pad_ = 0 , int spacer_ = 0, bool loopWaits_=false, float loopDelay_=0.f);
	Cfg::Textures getTexID();
	sf::IntRect currFrame();
	sf::Vector2f currOffset();
	sf::Vector2f currSize();

	void animate(float dt_);
	

};

#endif