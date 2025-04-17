#include "AnimObject.h"
#include <fstream>

void AnimObject::setTexRect(sf::IntRect tRect_)
{
	GameObject::setTexRect(tRect_);
}

std::string AnimObject::loadInFile(std::string animFile_)
{

	std::ifstream iFile;
	iFile.open("Config/Animations/" + animFile_);

	if (!iFile.is_open() || !iFile.good())
		return std::string{ R"(Unable to open the file at location : $(ProjectDir)Config/Animations/)" } + animFile_;
	else
	{
		std::string fileType;
		iFile >> fileType;

		if (fileType.substr(fileType.find_first_of('A'), (size_t)std::min(std::max((float)(fileType.length() - fileType.find_first_of('A')), 0.f), 9.f)) != "ANIMATION")
		{
			iFile.close();
			return std::string{ R"(Wrong file type for animation load!)" };
		}
		else
		{


			// correct file type and it is open

			// File codex

			// Header before the +
			// +
		// numAnimations
		//	NameAnim1:string DirAnim1:string
		//	TextureID:string numFrames:int numRows:int StartTileX:int StartTileY:int pitch:int frameWidth:int frameHeight:int frameDelay:int(MS) AnimSheetType:string AnimSheetPadding:int AnimSheetSpacerSize:int FrameDelay:int(MS) loops:boolint loopWaits:boolint loopWaitDelay:int(MS)
		//	worldSizeX:int worldSizeY:int HasVariableOffsets:boolint(1 - true or 0 - false) ((TexOffsetFrame1X TexOffsetFrame1Y..TexOffsetFrameNX TexOffsetFrameNY) || texOffset1toNX texOffset1toNY)
		//	...
		//	...AnimN

			std::string junk;
			iFile >> junk;
			while (junk != "+")
			{
				iFile >> junk;
			}
			// junk contains +, so time to start reading the file in
			int numAnimations;

			iFile >> numAnimations;


			for (int i = 0; i < numAnimations; i++)
			{

				std::string animName, direction, textureID, animSheetType;
				int rows, numFrames, startTileX, startTileY, pitch, frameW, frameH, animPadding, spacerSize, frameDelay, loops, loopWaits, loopWaitDelay, worldSizeX, worldSizeY, hasVariableOffsets;

				iFile >> animName >> direction >> textureID >> numFrames >> rows >> startTileX >> startTileY >> pitch >> frameW >> frameH >> frameDelay >> animSheetType >> animPadding >> spacerSize >> loops >> loopWaits >> loopWaitDelay;
				AnimName aName = AnimNameLUT[animName];
				AnimDir aDir = DirectionLUT[direction];
				Cfg::Textures aTex = TextureIDLUT[textureID];
				AnimSheetType aSheetType = AnimSheetTypeLUT[animSheetType];
				bool aLoops = loops == 1 ? true : false;
				bool aLoopWaits = loopWaits == 1 ? true : false;
				float aFrameDelay = (float)frameDelay / 1000.f;
				float aLoopWaitDelay = (float)loopWaitDelay / 1000.f;
				iFile >> worldSizeX >> worldSizeY;
				switch (aDir)
				{
				case AnimDir::Left:
					animMgr.AddLeftFrames(aName, aTex, numFrames, rows, startTileX, startTileY, pitch, frameW, frameH, aFrameDelay, aSheetType, animPadding, spacerSize, aLoops, aLoopWaits, aLoopWaitDelay, { (float)worldSizeX, (float)worldSizeY });
					break;
				case AnimDir::Right:
					animMgr.AddRightFrames(aName, aTex, numFrames, rows, startTileX, startTileY, pitch, frameW, frameH, aFrameDelay, aSheetType, animPadding, spacerSize, aLoops, aLoopWaits, aLoopWaitDelay, { (float)worldSizeX, (float)worldSizeY });
					break;
				case AnimDir::Uni:
					animMgr.AddUniFrames(aName, aTex, numFrames, rows, startTileX, startTileY, pitch, frameW, frameH, aFrameDelay, aSheetType, animPadding, spacerSize, aLoops, aLoopWaits, aLoopWaitDelay, { (float)worldSizeX, (float)worldSizeY });
					break;
				default:
					break;
				}

				iFile >> hasVariableOffsets;
				bool aHasVariableOffsets = hasVariableOffsets == 1 ? true : false;

				if (aHasVariableOffsets)
				{
					animMgr.resizeOffsets(aName, aDir, numFrames);
					for (int j = 0; j < numFrames; j++)
					{
						int x, y;
						iFile >> x >> y;
						animMgr.setOffset(aName, aDir, j, x, y);
					}
				}
				else
				{
					int x, y;
					iFile >> x >> y;
					animMgr.resizeOffsets(aName, aDir, numFrames);
					for (int j = 0; j < numFrames; j++)
					{
						animMgr.setOffset(aName, aDir, j, x, y);
					}

				}
			} // animation completed, loop for all animations
		} // success reading in file

		iFile.close();
	}

	return "OK";

}
