#include "GObj.h"

int GObj::_numObjects = { 0 };

GObj::GObj()
    : _worldPosition(0.f, 0.f), _size(0.f, 0.f), _velocity(0.f, 0.f) 
{
    _prevPosition = _worldPosition;
}

GObj::GObj(const GObj& o)
    : _worldPosition{o._worldPosition}, _size{ o._size }, _velocity{ o._velocity }
{
    _prevPosition = o._worldPosition;
}

GObj& GObj::operator=(const GObj& o)
{

    this->_worldPosition = o._worldPosition;
    this->_prevPosition = o._prevPosition;
    this->_velocity = o._velocity;
    this->_size = o._size;

    return *this;

}


const sf::Vector2f& GObj::getPos() const
{
    return _worldPosition;
}
void GObj::setPos(sf::Vector2f pos_)
{
    _worldPosition = pos_;
}
const sf::Vector2f& GObj::getSize() const
{
    return _size;
}
void GObj::setSize(sf::Vector2f size_)
{
    _size = size_;
}
const sf::Vector2f& GObj::getVelocity() const
{
    return _velocity;
}
void GObj::setVelocity(sf::Vector2f velocity_)
{
    _velocity = velocity_;
}
const sf::Vector2f& GObj::getPrevPos() const
{
    return _prevPosition;
}

void GObj::setPrevPos(sf::Vector2f prevPos_)
{
    _prevPosition = prevPos_;
}

GObj::GObj(GObj&& o)
    : _worldPosition(o._worldPosition), _size(o._size), _velocity(o._velocity), _prevPosition(o._prevPosition)
{
    this->_id = o.getID();
    _numObjects--;
}

GObj& GObj::operator=(GObj&& o)
{

    this->_worldPosition = o._worldPosition;
    this->_prevPosition = o._prevPosition;
    this->_velocity = o._velocity;
    this->_size = o._size;


    this->_id = o.getID();
    _numObjects--;
    
    return *this;
}

void GObj::initialize(sf::Vector2f size_, sf::Vector2f pos_, sf::Vector2f vel_)
{
    _size = size_;
    _worldPosition = pos_;
    _prevPosition = _worldPosition;
    _velocity = vel_;
}
int GObj::getID() const
{
    return _id;
}
//#include "GObj.h"
//#include <iostream>
//size_t GObj::totalGameObjects = { 0 };
//
//GObj::GObj(){ }
//
//GObj::~GObj(){  }
//
//void GObj::tick(float dt_)
//{
//	m_position += m_velocity * dt_;
//
//	static bool moved = false;
//	if (m_position != m_prevPosition)
//	{
//		moved = true;
//	}
//	else
//	{
//		moved = false;
//	}
//
//	if (moved)
//	{
//		m_prevMoveAmt = {m_position.x - m_prevPosition.x, m_position.y - m_prevPosition.y};
//		m_prevPosition = m_position;
//	}
//}
//
//void GObj::initialize(sf::Vector2f size_, sf::Vector2f pos_, sf::Vector2f vel_)
//{
//	m_size = size_;
//	m_position = pos_;
//	m_prevPosition = m_position;
//	m_velocity = vel_;
//	m_prevMoveAmt = { 0.f, 0.f };
//}
//
//void GObj::SetSize(const sf::Vector2f& size_)
//{
//	m_size = size_;
//}
//
//void GObj::AdjustPosition(const sf::Vector2f& amt_)
//{
//	m_position += amt_;
//}
//
//void GObj::SetPosition(const sf::Vector2f& pos_)
//{
//	m_position = pos_;
//}
//
//void GObj::AdjustVelocity(const sf::Vector2f& amt_)
//{
//	m_velocity += amt_;
//}
//
//void GObj::SetVelocity(const sf::Vector2f& vel_)
//{
//	m_velocity = vel_;
//}
//
//bool operator==(GObj& lhs_, GObj& rhs_)
//{
//	return (lhs_.m_id == rhs_.m_id);
//}
