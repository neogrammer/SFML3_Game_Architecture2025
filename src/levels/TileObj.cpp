
// ===== TileObj.cpp =====
#include "TileObj.h"
#include <iostream>
TileObj::TileObj() 
    : DrawableObj(Cfg::textures.get((int)Cfg::Textures::Invariant))
    , _tilesetTile{false}
    , _type{ TileType::VisibleAndEmpty }
    , _fType{FunType::Unknown}
{
    DrawableObj::initializeAsTile({ {0,0},{0,0} }, { 0.f,0.f });
}

TileObj::TileObj(const sf::Texture& tex_, sf::IntRect rect_, TileType type_, FunType fType_, bool empty_, sf::Vector2f pos_, bool tilesetTile_, sf::Vector2i tileSize_)
    : DrawableObj{tex_}
    , _tilesetTile{tilesetTile_}
    , _type{ type_ }  
    , _fType{ fType_ }
{
    if (tileSize_.x == 0 || tileSize_.y == 0)
        setSize((sf::Vector2f)rect_.size);
    else
         setSize((sf::Vector2f)tileSize_);


    DrawableObj::initializeAsTile(rect_, pos_); 
    _sprite.setTextureRect(rect_);
}


void TileObj::update(float dt) {
    if (this->isAnimated())
    {
        //animate logic
        int i = 0;
        std::cout << "We got an animated tile!" << std::endl;
    }
}    // Tiles usually don't need logic, but it's here if necessary


void TileObj::setType(bool solid_, bool visible_, bool animated_)
{
    switch (solid_)
    {
    case true:
    {
        if (visible_ == true || animated_ == true)
        {
            if (animated_ == true)
                _type = TileType::AnimatedAndSolid;
            else
                _type = TileType::VisibleAndSolid;
        }
        else
            _type = TileType::InvisibleAndSolid;
    }
    break;
    default:
    {
        if (visible_ == true || animated_ == true)
        {
            if (animated_ == true)
                _type = TileType::AnimatedAndEmpty;
            else
               _type = TileType::VisibleAndEmpty;
        }
        else
            _type = TileType::InvisibleAndEmpty;
    }
    break;
    }
}

bool TileObj::isSolid() const
{ 
    return (_type == TileType::VisibleAndSolid || _type == TileType::InvisibleAndSolid 
        || _type == TileType::AnimatedAndSolid);
}
bool TileObj::isAnimated() const
{
    return (_type == TileType::AnimatedAndSolid || _type == TileType::AnimatedAndEmpty);
}

bool TileObj::isVisible() const
{
    return (_type == TileType::VisibleAndSolid || _type == TileType::VisibleAndEmpty || 
        _type == TileType::AnimatedAndSolid || _type == TileType::AnimatedAndEmpty);
}

bool TileObj::isEmpty() const
{
    return (_type == TileType::InvisibleAndEmpty || _type == TileType::VisibleAndEmpty  
        || _type == TileType::AnimatedAndEmpty);
}

bool TileObj::isTilesetTile() const
{
    return _tilesetTile;
}

void TileObj::setIsTilesetTile(bool cond_)
{
    _tilesetTile = cond_;
}

TileType TileObj::getType() const
{
    return _type;
}

FunType TileObj::getFunType() const
{
    return _fType;
}

void TileObj::setFunType(FunType fType_)
{
    _fType = fType_;
}

void TileObj::init(const sf::Texture& tex_, sf::IntRect rect_, TileType type_, FunType fType_, bool empty_, sf::Vector2f pos_, bool tilesetTile_, sf::Vector2i tileSize_)
{
    _sprite.setTexture(tex_);
    _sprite.setTextureRect(rect_);
    _type = type_;
    _fType = fType_;
    setPos(pos_);
    _tilesetTile = tilesetTile_;
    setSize((sf::Vector2f)tileSize_);
    animHandler.setFrame(rect_, "Tile", 0, "Uni");
    setInitialized(true);
}

const sf::IntRect& TileObj::getTexRect(int index)
{
    if (index == -1)    
        return animHandler.getAnims().at("Tile").framesUni.at(animHandler.getCurrentIndex());
    else
        return animHandler.getAnims().at("Tile").framesUni.at(index);

}

void TileObj::commit(float dt)
{
}

bool operator==(TileObj& lhs_, TileObj& rhs_)
{
    return lhs_.getID() == rhs_.getID();
}

//#include "TileObj.h"
//#include <iostream>
//
//TileObj::TileObj(Cfg::Textures tex_,sf::IntRect rect_, int pitch_, TileType type_, bool empty_, sf::Vector2f pos_)
//    : DrawableObj{}
//	, m_type{type_}
//	, m_pitch{ pitch_ }
//{
//	DrawableObj::initializeAsTile(rect_, tex_, pos_);
//}
//
//TileObj::~TileObj()
//{
//}
//
//void TileObj::update(float dt_)
//{
//
//	DrawableObj::update(dt_);
//}
//
//void TileObj::render(sf::RenderWindow& wnd_)
//{
//
//	DrawableObj::render(wnd_);
//}
//
//sf::Vector2i TileObj::getTexRectSize()
//{
//	return (sf::Vector2i)this->GetSize();
//}
//
//Cfg::Textures TileObj::getTextureID()
//{
//	return DrawableObj::getTextureID();
//}
//
//sf::Vector2i TileObj::getTexPos()
//{
//	return (sf::Vector2i)DrawableObj::getTexRectPos();
//}
//
//int TileObj::getPitch()
//{
//	return m_pitch;
//}
//
//bool TileObj::isSolid()
//{
//	return (m_type == TileType::InvisibleAndSolid || m_type == TileType::VisibleAndSolid);
//}
//
//bool TileObj::isVisible()
//{
//	return (m_type == TileType::VisibleAndSolid || m_type == TileType::VisibleAndEmpty);
//}
//
//bool TileObj::isEmpty()
//{
//	return m_type == TileType::InvisibleAndEmpty;
//}
//
//
//
//TileType TileObj::getType()
//{
//	return this->m_type;
//}
//
//bool operator==(TileObj& lhs_, TileObj& rhs_)
//{
//	return lhs_.ID() == rhs_.ID();
//}


