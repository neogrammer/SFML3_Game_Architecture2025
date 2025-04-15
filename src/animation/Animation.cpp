#include "Animation.h"


std::unordered_map<std::string, AnimName> AnimNameLUT = {
    {"Idle",AnimName::Idle},
    {"Invariant",AnimName::Invariant},
    {"Fly",AnimName::Fly}
};
std::unordered_map < std::string, AnimDir> DirectionLUT = {
    {"Left",AnimDir::Left},
    {"Right",AnimDir::Right},
    {"Uni",AnimDir::Uni}
};
std::unordered_map < std::string, Cfg::Textures> TextureIDLUT = {
    {"PlayerAtlas",Cfg::Textures::MegaManSheet1x48x48x1}
};
std::unordered_map < std::string, AnimSheetType> AnimSheetTypeLUT = {
    {"Blocks", AnimSheetType::Blocks},
    {"Normal", AnimSheetType::Normal},
    {"Padded", AnimSheetType::Padded},
    {"Vertical", AnimSheetType::Vertical}
};


bool Animation::hasLeftFrames()
{
    return !leftFrames.empty();
}

bool Animation::hasRightFrames()
{
    return !rightFrames.empty();
}

bool Animation::hasUniFrames()
{
    return !uniFrames.empty();
}

sf::IntRect Animation::getFrame(AnimDir dir_, int index)
{
    using a = AnimDir;
    switch (dir_)
    {
    case a::Right:
        return rightFrames.at(index);
        break;
    case a::Left:
        return leftFrames.at(index);
        break;
    case a::Uni:
        return uniFrames.at(index);
        break;
    default:
        break;
    }
    return sf::IntRect{ sf::Vector2i{ 0,0 }, sf::Vector2i{ 0, 0 } };
}

sf::Vector2f Animation::getOffset(AnimDir dir_, int index)
{
    using a = AnimDir;
    switch (dir_)
    {
    case a::Right:
        return rightOffsets.at(index);
        break;
    case a::Left:
        return leftOffsets.at(index);
        break;
    case a::Uni:
        return uniOffsets.at(index);
        break;
    default:
        break;
    }
    return { 0.f,0.f };
}
