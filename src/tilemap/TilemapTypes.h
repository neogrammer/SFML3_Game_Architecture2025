#pragma once
#include <Resources/Cfg.h>

enum class TileType : int
{
    InvisibleAndEmpty = 0,
    VisibleAndSolid = 1,
    VisibleAndEmpty = 2,
    InvisibleAndSolid = 3,
    AnimatedAndSolid = 4,
    AnimatedAndEmpty = 5,
    TypeCount = 6,
    Unknown = 7
};

enum class FunType : int
{
    MapTile = 0,
    TrapTile = 1,
    WarpTile = 2,
    HealTile = 3,
    StairTile = 4,
    EventTile = 5,
    DecorTile = 6,
    TypeCount = 7,
    Unknown = 8
};

enum class  LevelName : int
{
    Intro = 0,
    LevelCount = 1,
    Unknown = 2
};


struct TMAP
{
    TMAP();
    ~TMAP();
    TMAP(const TMAP& other);
    TMAP& operator=(const TMAP& other);
    TMAP(TMAP&&);
    TMAP& operator=(TMAP&&);

    std::vector<int> level{};
    int cols{ 1 };
    int rows{ 1 };
    int tw{ 50 };
    int th{ 50 };

};

struct TSET
{
    TSET();
    ~TSET();
    TSET(const TSET& other);
    TSET& operator=(const TSET& other);
    TSET(TSET&&);
    TSET& operator=(TSET&&);


    sf::Texture texID;
    std::vector<int> tileDataType{};
    int cols{ 1 };
    int rows{ 1 };
    int tw{ 50 };
    int th{ 50 };

    TSET(const sf::Texture& texID_, int cols_, int rows_, int tw_, int th_)
        : texID{texID_}
        , cols{cols_}
        , rows{rows_}
        , tw{tw_}
        , th{th_}
    {}
};

extern TMAP GetLevelData(LevelName level);
extern TSET GetTilesetData(LevelName level);