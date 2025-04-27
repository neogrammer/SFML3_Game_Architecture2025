#include "Animation.h"


std::unordered_map<std::string, AnimName> AnimNameLUT = {
    {"Idle",AnimName::Idle},
    {"Invariant",AnimName::Invariant},
    {"IdleToRun", AnimName::IdleToRun},
    {"Running", AnimName::Running},
    {"ShootSetup", AnimName::ShootSetup},
    {"Shooting", AnimName::Shooting},
    {"RunningAndShooting", AnimName::RunningAndShooting},
    {"LiftOff", AnimName::LiftOff},
    {"Rising", AnimName::Rising},
    {"JumpPeakRising", AnimName::JumpPeakRising},
    {"JumpPeakFalling", AnimName::JumpPeakFalling},
    {"Falling", AnimName::Falling},
    {"Landing", AnimName::Landing},
    {"LiftOffAndShooting", AnimName::LiftOffAndShooting},
    {"RisingAndShooting", AnimName::RisingAndShooting},
    {"JumpPeakRisingAndShooting", AnimName::JumpPeakRisingAndShooting},
    {"JumpPeakFallingAndShooting", AnimName::JumpPeakFallingAndShooting},
    {"FallingAndShooting", AnimName::FallingAndShooting},
    {"LandingAndShooting", AnimName::LandingAndShooting},
    {"Fly",AnimName::Fly}
};
std::unordered_map < std::string, AnimDir> DirectionLUT = {
    {"Left",AnimDir::Left},
    {"Right",AnimDir::Right},
    {"Uni",AnimDir::Uni}
};
std::unordered_map < std::string, Cfg::Textures> TextureIDLUT = {
    {"PlayerAtlas",Cfg::Textures::MegaManSheet1x48x48x1},
    {"Intro", Cfg::Textures::TilesetIntro},
    {"Platform1", Cfg::Textures::Platform1},
    {"GooglyEye", Cfg::Textures::GooglyEye }

};
std::unordered_map < std::string, AnimSheetType> AnimSheetTypeLUT = {
    {"Blocks", AnimSheetType::Blocks},
    {"Normal", AnimSheetType::Normal},
    {"Padded", AnimSheetType::Padded},
    {"Vertical", AnimSheetType::Vertical}
};


std::unordered_map < AnimName, std::string > FSMStateNameLUT =
{
    {AnimName::Idle                       , "Idle"                          },
    {AnimName::Invariant                  , "Invariant"                     },
    {AnimName::IdleToRun                  , "IdleToRun"                     },
    {AnimName::Running                    , "Running"                       },
    {AnimName::ShootSetup                 , "ShootSetup"                    },
    {AnimName::Shooting                   , "Shooting"                      },
    {AnimName::RunningAndShooting                   , "RunningAndShooting"            },
    {AnimName::LiftOff                    , "LiftOff"                       },
    {AnimName::Rising                     , "Rising"                        },
    {AnimName::JumpPeakRising             , "JumpPeakRising"                },
    {AnimName::JumpPeakFalling            , "JumpPeakFalling"               },
    {AnimName::Falling                    , "Falling"                       },
    {AnimName::Landing                    , "Landing"                       },
    {AnimName::LiftOffAndShooting         , "LiftOffAndShooting"            },
    {AnimName::RisingAndShooting          , "RisingAndShooting"             },
    {AnimName::JumpPeakRisingAndShooting  , "JumpPeakRisingAndShooting"     },
    {AnimName::JumpPeakFallingAndShooting , "JumpPeakFallingAndShooting"     },
    {AnimName::FallingAndShooting         , "FallingAndShooting"            },
    {AnimName::LandingAndShooting         , "LandingAndShooting"            },
    {AnimName::Fly                        , "Fly"                            }
};

std::unordered_map < std::string, AnimName > FSMAnimNameLUT =
{
   {"Idle",AnimName::Idle},
    {"Invariant",AnimName::Invariant},
    {"IdleToRun", AnimName::IdleToRun},
    {"Running", AnimName::Running},
    {"ShootSetup", AnimName::ShootSetup},
    {"Shooting", AnimName::Shooting},
    {"RunningAndShooting", AnimName::RunningAndShooting},
    {"LiftOff", AnimName::LiftOff},
    {"Rising", AnimName::Rising},
    {"JumpPeakRising", AnimName::JumpPeakRising},
    {"JumpPeakFalling", AnimName::JumpPeakFalling},
    {"Falling", AnimName::Falling},
    {"Landing", AnimName::Landing},
    {"LiftOffAndShooting", AnimName::LiftOffAndShooting},
    {"RisingAndShooting", AnimName::RisingAndShooting},
    {"JumpPeakRisingAndShooting", AnimName::JumpPeakRisingAndShooting},
    {"JumpPeakFallingAndShooting", AnimName::JumpPeakFallingAndShooting},
    {"FallingAndShooting", AnimName::FallingAndShooting},
    {"LandingAndShooting", AnimName::LandingAndShooting},
    {"Fly",AnimName::Fly}
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

sf::Vector2f Animation::getWorldSize(AnimDir dir_, int index_)
{
    using a = AnimDir;
    switch (dir_)
    {
    case a::Right:
        return rightSizes.at(index_);
        break;
    case a::Left:
        return leftSizes.at(index_);
        break;
    case a::Uni:
        return uniSizes.at(index_);
        break;
    default:
        break;
    }
    return { 0.f,0.f };
}

sf::Vector2f Animation::getBulletPoint(AnimDir dir_, int index_)
{
    using a = AnimDir;
    switch (dir_)
    {
    case a::Right:
        return rightBulletAnchors.at(index_);
        break;
    case a::Left:
        return leftBulletAnchors.at(index_);
        break;
    case a::Uni:
        return uniBulletAnchors.at(index_);
        break;
    default:
        break;
    }
    return { 0.f,0.f };
}

int Animation::getNumFrames()
{
    if (leftFrames.size() != 0)
    {
        return (int)leftFrames.size();
    }
    else if (rightFrames.size() != 0)
    {
        return (int)rightFrames.size();
    }
    else if (uniFrames.size() != 0)
    {
        return (int)uniFrames.size();
    }
    else
        return 0;
}
