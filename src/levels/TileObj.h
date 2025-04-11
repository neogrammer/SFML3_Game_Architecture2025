
// ===== TileObj.h =====
#pragma once
#include <GameObjects/DrawableObj.h>
#include <core/Resources/Cfg.h>
#include <Tilemap/TilemapTypes.h>


class TileObj : public DrawableObj {
public:
    TileObj();
    TileObj(const sf::Texture& tex_, sf::IntRect rect_, TileType type_, FunType fType_, bool empty_ = false, sf::Vector2f pos_ = { 0.f,0.f }, bool tilesetTile_ = false, sf::Vector2i tileSize_ = {0,0});
    virtual ~TileObj() = default;

    void setType(bool solid_, bool visible_, bool animated_);
    bool isSolid() const;
    bool isAnimated() const;
    void update(float dt) override;

    TileObj(const TileObj&) = default;
    TileObj& operator=(const TileObj&) = default;
    TileObj(TileObj&&) = default;
    TileObj& operator=(TileObj&&) = default;


    friend bool operator==(TileObj& lhs_, TileObj& rhs_);


    bool isVisible() const;
    bool isEmpty() const;

    bool isTilesetTile() const;
    void setIsTilesetTile(bool cond_ = true);

    TileType getType() const;

    FunType getFunType() const;
    void setFunType(FunType fType_);

    void init(const sf::Texture& tex_, sf::IntRect rect_, TileType type_, FunType fType_, bool empty_, sf::Vector2f pos_, bool tilesetTile_, sf::Vector2i tileSize_);
    const sf::IntRect& getTexRect(int index = -1);


private:

    bool _tilesetTile{ true };
    TileType _type{ TileType::VisibleAndSolid };
    FunType _fType{ FunType::MapTile };

    // Inherited via DrawableObj
    void commit(float dt) override;
};
  //#pragma once
//#include <GameObjects/DrawableObj.h>
//#include "TilemapTypes.h"
//c
//class TileObj : public DrawableObj
//{
//	int m_pitch{ 0 };
//	TileType m_type{ TileType::InvisibleAndEmpty };
//
//public:
//	TileObj() {};
//	TileObj(Cfg::Textures tex_, sf::IntRect rect_, int pitch, TileType type_, bool empty_= false, sf::Vector2f pos_ = {0.f,0.f});
//	virtual ~TileObj() override;
//	
//	TileObj(const TileObj&) = default;
//	TileObj& operator=(const TileObj&)=default;
//	TileObj(TileObj&&)=default;
//	TileObj& operator=(TileObj&&)=default;
//
//
//	friend bool operator==(TileObj& lhs_, TileObj& rhs_);
//
//	virtual void update(float dt_) override;
//	virtual void render(sf::RenderWindow& wnd_);
//
//	sf::Vector2i getTexRectSize();
//	Cfg::Textures getTextureID();
//	sf::Vector2i getTexPos();
//
//	int getPitch();
//
//	bool isSolid();
//	bool isVisible();
//	bool isEmpty();
//
//	
//	TileType getType();
//
//};