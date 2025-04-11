
// ===== DrawableObj.cpp =====
#include "DrawableObj.h"
#include <core/Resources/Cfg.h>
#include <fstream>
#include <iostream>
#include <Tilemap/TileObj.h>
DrawableObj::DrawableObj()
    : DrawableObj{Cfg::textures.get((int)Cfg::Textures::Invariant)}
{
}

DrawableObj::DrawableObj(const sf::Texture& tex_)
    : _sprite{tex_}
    , animHandler{}
{
    // derived class adds the animations


    _sprite.setTexture(tex_);

}

void DrawableObj::setAnimName(std::string animName_)
{
    animHandler.changeAnim(animName_);
}

DrawableObj::DrawableObj(const DrawableObj& o)
    : _sprite{const_cast<DrawableObj&>(o).getTexture()}
    , animHandler{}
{
    _sprite.setPosition(_sprite.getPosition());
    _sprite.setTextureRect(o._sprite.getTextureRect());

    auto& oo = const_cast<AnimHandler&>(o.animHandler);

    auto rects = o.animHandler.getFrames();
    std::string dir = (oo.isCurrUniDir() ? "Uni" : (o.animHandler.isFacingRight() ? "Right" : "Left"));
    for (auto& animName : oo.getAnimNames(dir))
    {
        auto& tmp = oo.getAnims().at(animName);
        animHandler.addAnim(animName, rects, tmp.textureOffsets, tmp.frameDelay, tmp.loop, o.isFacingRight(), dir);
        animHandler.setFrameOffsets((const_cast<DrawableObj&>(o)).animHandler.getTexOffset(animName), animHandler.getCurrentIndex(), animName);
        animHandler.setFrameDelay(0.1f, animName);
        animHandler.setLooping(animName, const_cast<DrawableObj&>(o).animHandler.isLooping(animName));
        animHandler.setUniDir(true);
        animHandler.changeAnim(animName);
    }

   /* const auto& rects = o.animHandler.getFrames();

    if (const_cast<DrawableObj&>(o).animHandler.isUni())
    {
        for (auto r : const_cast<DrawableObj&>(o).animHandler.getAnimNames("Uni"))
        {
            animHandler.resizeFrames(r, "Uni", (int)(const_cast<DrawableObj&>(o)).animHandler.getFrames("Uni", r).size());
            for (int i = 0; i < (int)o.animHandler.getFrames("Uni", r).size(); i++)
            {
                animHandler.setFrame(o.animHandler.getFrames().at(i), r, i, "Uni");
            }
            animHandler.setFrameOffsets((const_cast<DrawableObj&>(o)).animHandler.getTexOffset(r), animHandler.getCurrentIndex(), r);
            animHandler.setFrameDelay(0.1f, r);
            animHandler.setLooping(r, const_cast<DrawableObj&>(o).animHandler.isLooping(r));
            animHandler.setUniDir(true);
            animHandler.changeAnim(r);
        }
    }
    else
    {
        for (auto r : const_cast<DrawableObj&>(o).animHandler.getAnimNames("Right"))
        {
            animHandler.resizeFrames(r, "Right", (int)(const_cast<DrawableObj&>(o)).animHandler.getFrames("Right", r).size());
            for (int i = 0; i < (int)o.animHandler.getFrames("Right", r).size(); i++)
            {
                animHandler.setFrame(o.animHandler.getFrames().at(i), r, i, "Right");
            }
            animHandler.setFrameOffsets((const_cast<DrawableObj&>(o)).animHandler.getTexOffset(r), animHandler.getCurrentIndex(), r);
            animHandler.setFrameDelay(0.1f, r);
            animHandler.setLooping(r, const_cast<DrawableObj&>(o).animHandler.isLooping(r));
            animHandler.setUniDir(false);
            animHandler.changeAnim(r);

        }

        for (auto r : const_cast<DrawableObj&>(o).animHandler.getAnimNames("Left"))
        {
            animHandler.resizeFrames(r, "Left", (int)(const_cast<DrawableObj&>(o)).animHandler.getFrames("Left", r).size());
            for (int i = 0; i < (int)o.animHandler.getFrames("Left", r).size(); i++)
            {
                animHandler.setFrame(o.animHandler.getFrames().at(i), r, i, "Left");
            }
            animHandler.setFrameOffsets((const_cast<DrawableObj&>(o)).animHandler.getTexOffset(r), animHandler.getCurrentIndex(), r);
            animHandler.setFrameDelay(0.1f, r);
            animHandler.setLooping(r, const_cast<DrawableObj&>(o).animHandler.isLooping(r));
            animHandler.setUniDir(false);
            animHandler.changeAnim(r);
        }
    }*/
}

DrawableObj& DrawableObj::operator=(const DrawableObj& o)
{
    this->_sprite = o._sprite;
    this->_sprite.setTexture(const_cast<DrawableObj*>(&o)->getTexture());
    _sprite.setPosition(_sprite.getPosition());
    _sprite.setTextureRect(o._sprite.getTextureRect());
    auto& oo = const_cast<AnimHandler&>(o.animHandler);
    // TODO: insert return statement here
    auto rects = o.animHandler.getFrames();
    std::string dir = (oo.isCurrUniDir() ? "Uni" : (o.animHandler.isFacingRight() ? "Right" : "Left"));
    for (auto& animName : oo.getAnimNames(dir))
    {
        auto& tmp = oo.getAnims().at(animName);
        animHandler.addAnim(animName, rects, tmp.textureOffsets, tmp.frameDelay, tmp.loop, o.isFacingRight(), dir);
        animHandler.setFrameOffsets((const_cast<DrawableObj&>(o)).animHandler.getTexOffset(animName), animHandler.getCurrentIndex(), animName);
        animHandler.setFrameDelay(0.1f, animName);
        animHandler.setLooping(animName, const_cast<DrawableObj&>(o).animHandler.isLooping(animName));
        animHandler.setUniDir(true);
        animHandler.changeAnim(animName);
    }


  /*  const auto& rects = o.animHandler.getFrames();

    if (const_cast<DrawableObj&>(o).animHandler.isUni())
    {
        for (auto r : const_cast<DrawableObj&>(o).animHandler.getAnimNames("Uni"))
        {
            animHandler.resizeFrames(r, "Uni", (int)(const_cast<DrawableObj&>(o)).animHandler.getFrames("Uni", r).size());
            for (int i = 0; i < (int)o.animHandler.getFrames("Uni", r).size(); i++)
            {
                animHandler.setFrame(o.animHandler.getFrames().at(i), r, i, "Uni");
            }
            animHandler.setFrameOffsets((const_cast<DrawableObj&>(o)).animHandler.getTexOffset(r), animHandler.getCurrentIndex(), r);
            animHandler.setFrameDelay(0.1f, r);
            animHandler.setLooping(r, const_cast<DrawableObj&>(o).animHandler.isLooping(r));
            animHandler.setUniDir(true);
            animHandler.changeAnim(r);
        }
    }
    else
    {
        for (auto r : const_cast<DrawableObj&>(o).animHandler.getAnimNames("Right"))
        {
            animHandler.resizeFrames(r, "Right", (int)(const_cast<DrawableObj&>(o)).animHandler.getFrames("Right", r).size());
            for (int i = 0; i < (int)o.animHandler.getFrames("Right", r).size(); i++)
            {
                animHandler.setFrame(o.animHandler.getFrames().at(i), r, i, "Right");
            }
            animHandler.setFrameOffsets((const_cast<DrawableObj&>(o)).animHandler.getTexOffset(r), animHandler.getCurrentIndex(), r);
            animHandler.setFrameDelay(0.1f, r);
            animHandler.setLooping(r, const_cast<DrawableObj&>(o).animHandler.isLooping(r));
            animHandler.setUniDir(false);
            animHandler.changeAnim(r);

        }

        for (auto r : const_cast<DrawableObj&>(o).animHandler.getAnimNames("Left"))
        {
            animHandler.resizeFrames(r, "Left", (int)(const_cast<DrawableObj&>(o)).animHandler.getFrames("Left", r).size());
            for (int i = 0; i < (int)o.animHandler.getFrames("Left", r).size(); i++)
            {
                animHandler.setFrame(o.animHandler.getFrames().at(i), r, i, "Left");
            }
            animHandler.setFrameOffsets((const_cast<DrawableObj&>(o)).animHandler.getTexOffset(r), animHandler.getCurrentIndex(), r);
            animHandler.setFrameDelay(0.1f, r);
            animHandler.setLooping(r, const_cast<DrawableObj&>(o).animHandler.isLooping(r));
            animHandler.setUniDir(false);
            animHandler.changeAnim(r);
        }
    }*/

    return *this;
}

DrawableObj::DrawableObj(DrawableObj&& o)
    : _sprite{o.getTexture()}
    , animHandler{}
{
    _sprite.setPosition(_sprite.getPosition());
    _sprite.setTextureRect(o._sprite.getTextureRect());

    auto rects = o.animHandler.getFrames();
    std::string dir = (o.animHandler.isCurrUniDir() ? "Uni" : (o.animHandler.isFacingRight() ? "Right" : "Left"));
    for (auto& animName : o.animHandler.getAnimNames(dir))
    {
        auto& tmp = o.animHandler.getAnims().at(animName);
        animHandler.addAnim(animName, rects, tmp.textureOffsets, tmp.frameDelay, tmp.loop, o.isFacingRight(), dir);
        animHandler.setFrameOffsets((const_cast<DrawableObj&>(o)).animHandler.getTexOffset(animName), animHandler.getCurrentIndex(), animName);
        animHandler.setFrameDelay(0.1f, animName);
        animHandler.setLooping(animName, const_cast<DrawableObj&>(o).animHandler.isLooping(animName));
        animHandler.setUniDir(true);
        animHandler.changeAnim(animName);
    }
    /*if (const_cast<DrawableObj&>(o).animHandler.isUni())
    {
        for (auto r : const_cast<DrawableObj&>(o).animHandler.getAnimNames("Uni"))
        {
            animHandler.resizeFrames(r, "Uni", (int)(const_cast<DrawableObj&>(o)).animHandler.getFrames("Uni", r).size());
            for (int i = 0; i < (int)o.animHandler.getFrames("Uni", r).size(); i++)
            {
                animHandler.setFrame(o.animHandler.getFrames().at(i), r, i, "Uni");
            }
            animHandler.setFrameOffsets((const_cast<DrawableObj&>(o)).animHandler.getTexOffset(r), animHandler.getCurrentIndex(), r);
            animHandler.setFrameDelay(0.1f, r);
            animHandler.setLooping(r, const_cast<DrawableObj&>(o).animHandler.isLooping(r));
            animHandler.setUniDir(true);
            animHandler.changeAnim(r);
            _initialized = true;
        }
    }
    else
    {
        for (auto r : const_cast<DrawableObj&>(o).animHandler.getAnimNames("Right"))
        {
            animHandler.resizeFrames(r, "Right", (int)(const_cast<DrawableObj&>(o)).animHandler.getFrames("Right", r).size());
            for (int i = 0; i < (int)o.animHandler.getFrames("Right", r).size(); i++)
            {
                animHandler.setFrame(o.animHandler.getFrames().at(i), r, i, "Right");
            }
            animHandler.setFrameOffsets((const_cast<DrawableObj&>(o)).animHandler.getTexOffset(r), animHandler.getCurrentIndex(), r);
            animHandler.setFrameDelay(0.1f, r);
            animHandler.setLooping(r, const_cast<DrawableObj&>(o).animHandler.isLooping(r));
            animHandler.setUniDir(false);
            animHandler.changeAnim(r);
            _initialized = true;

        }

        for (auto r : const_cast<DrawableObj&>(o).animHandler.getAnimNames("Left"))
        {
            animHandler.resizeFrames(r, "Left", (int)(const_cast<DrawableObj&>(o)).animHandler.getFrames("Left", r).size());
            for (int i = 0; i < (int)o.animHandler.getFrames("Left", r).size(); i++)
            {
                animHandler.setFrame(o.animHandler.getFrames().at(i), r, i, "Left");
            }
            animHandler.setFrameOffsets((const_cast<DrawableObj&>(o)).animHandler.getTexOffset(r), animHandler.getCurrentIndex(), r);
            animHandler.setFrameDelay(0.1f, r);
            animHandler.setLooping(r, const_cast<DrawableObj&>(o).animHandler.isLooping(r));
            animHandler.setUniDir(false);
            animHandler.changeAnim(r);
            _initialized = true;
        }
    }*/


}

DrawableObj& DrawableObj::operator=(DrawableObj&& o)
{
    this->_sprite = o._sprite;
    this->_sprite.setTexture(const_cast<DrawableObj*>(&o)->getTexture());
    _sprite.setPosition(_sprite.getPosition());
    _sprite.setTextureRect(o._sprite.getTextureRect());
    // TODO: insert return statement here

    auto rects = o.animHandler.getFrames();
    std::string dir = (o.animHandler.isCurrUniDir() ? "Uni" : (o.animHandler.isFacingRight() ? "Right" : "Left"));
    for (auto& animName : o.animHandler.getAnimNames(dir))
    {
        auto& tmp = o.animHandler.getAnims().at(animName);
        animHandler.addAnim(animName, rects, tmp.textureOffsets, tmp.frameDelay, tmp.loop, o.isFacingRight(), dir);
        animHandler.setFrameOffsets((const_cast<DrawableObj&>(o)).animHandler.getTexOffset(animName), animHandler.getCurrentIndex(), animName);
        animHandler.setFrameDelay(0.1f, animName);
        animHandler.setLooping(animName, const_cast<DrawableObj&>(o).animHandler.isLooping(animName));
        animHandler.setUniDir(true);
        animHandler.changeAnim(animName);
    }


    //const auto& rects = o.animHandler.getFrames();

    //if (const_cast<DrawableObj&>(o).animHandler.isUni())
    //{
    //    for (auto r : const_cast<DrawableObj&>(o).animHandler.getAnimNames("Uni"))
    //    {
    //        animHandler.resizeFrames(r, "Uni", (int)(const_cast<DrawableObj&>(o)).animHandler.getFrames("Uni", r).size());
    //        for (int i = 0; i < (int)o.animHandler.getFrames("Uni", r).size(); i++)
    //        {
    //            animHandler.setFrame(o.animHandler.getFrames().at(i), r, i, "Uni");
    //        }
    //        animHandler.setFrameOffsets((const_cast<DrawableObj&>(o)).animHandler.getTexOffset(r), animHandler.getCurrentIndex(), r);
    //        animHandler.setFrameDelay(0.1f, r);
    //        animHandler.setLooping(r, const_cast<DrawableObj&>(o).animHandler.isLooping(r));
    //        animHandler.setUniDir(true);
    //        animHandler.changeAnim(r);
    //    }
    //}
    //else
    //{
    //    for (auto r : const_cast<DrawableObj&>(o).animHandler.getAnimNames("Right"))
    //    {
    //        animHandler.resizeFrames(r, "Right", (int)(const_cast<DrawableObj&>(o)).animHandler.getFrames("Right", r).size());
    //        for (int i = 0; i < (int)o.animHandler.getFrames("Right", r).size(); i++)
    //        {
    //            animHandler.setFrame(o.animHandler.getFrames().at(i), r, i, "Right");
    //        }
    //        animHandler.setFrameOffsets((const_cast<DrawableObj&>(o)).animHandler.getTexOffset(r), animHandler.getCurrentIndex(), r);
    //        animHandler.setFrameDelay(0.1f, r);
    //        animHandler.setLooping(r, const_cast<DrawableObj&>(o).animHandler.isLooping(r));
    //        animHandler.setUniDir(false);
    //        animHandler.changeAnim(r);

    //    }

    //    for (auto r : const_cast<DrawableObj&>(o).animHandler.getAnimNames("Left"))
    //    {
    //        animHandler.resizeFrames(r, "Left", (int)(const_cast<DrawableObj&>(o)).animHandler.getFrames("Left", r).size());
    //        for (int i = 0; i < (int)o.animHandler.getFrames("Left", r).size(); i++)
    //        {
    //            animHandler.setFrame(o.animHandler.getFrames().at(i), r, i, "Left");
    //        }
    //        animHandler.setFrameOffsets((const_cast<DrawableObj&>(o)).animHandler.getTexOffset(r), animHandler.getCurrentIndex(), r);
    //        animHandler.setFrameDelay(0.1f, r);
    //        animHandler.setLooping(r, const_cast<DrawableObj&>(o).animHandler.isLooping(r));
    //        animHandler.setUniDir(false);
    //        animHandler.changeAnim(r);
    //    }
    //}

    return *this;
}

void DrawableObj::render(sf::RenderWindow& window) 
{
    if (_initialized)
    {
        sf::Vector2f drawPos = getPos() - static_cast<sf::Vector2f>(animHandler.getCurrTexOff());
        _sprite.setPosition(drawPos);
        if (animHandler.isUni())
            _sprite.setTexture(Cfg::textures.get((int)Cfg::Textures::Tileset1));

        if (animHandler.isUni())
        {
            _sprite.setTextureRect(animHandler.getAnims().at(animHandler.getAnimName()).framesUni.at(animHandler.getCurrentIndex()));

        }
        else
        {
            if (animHandler.isFacingRight())
            {
                _sprite.setTextureRect(animHandler.getAnims().at(animHandler.getAnimName()).framesRight.at(animHandler.getCurrentIndex()));

            }
            else
            {
                _sprite.setTextureRect(animHandler.getAnims().at(animHandler.getAnimName()).framesLeft.at(animHandler.getCurrentIndex()));
            }

        }
       

        window.draw(_sprite);
        
    }
}

void DrawableObj::setTexture(const sf::Texture& texture, bool resetRect) {
    _sprite.setTexture(texture, resetRect);
}

sf::Texture& DrawableObj::getTexture()
{
    return *const_cast<sf::Texture*>(&_sprite.getTexture());
}

void DrawableObj::setTexRect(const sf::IntRect& rect) {
    assert(_initialized);
        _sprite.setTextureRect(rect);
}

const sf::IntRect& DrawableObj::getTexRect() const {
    assert(_initialized);

    return _sprite.getTextureRect();
}

void DrawableObj::setFacingRight(bool cond_)
{
    assert(_initialized);

    animHandler.setFacingRight(cond_);
}

bool DrawableObj::isFacingRight() const
{
    assert(_initialized);

    return animHandler.isFacingRight();
}
void DrawableObj::setFrameDelay(float frameDelay_, std::string animName)
{
    assert(_initialized);

        animHandler.setFrameDelay(frameDelay_, animName);
}
void DrawableObj::setFrameOffsets(sf::Vector2i off_, std::string animName)
{
    assert(_initialized);

     animHandler.setFrameOffsets(off_, animHandler.getCurrentIndex(), animName);
}
sf::Vector2i DrawableObj::getFrameOffsets(std::string animName)
{
    assert(_initialized);

    return animHandler.getFrameOffsets(animHandler.getCurrentIndex(), animName, animHandler.isUni());
}
float DrawableObj::getFrameDelay(std::string animName)
{
    assert(_initialized);
    return animHandler.getFrameDelay(animName);
}
void DrawableObj::initialize(const std::string& filepath_, sf::Vector2f size_,  sf::Vector2f pos_, const sf::Texture& tex_, sf::Vector2f vel_)
{
    GObj::initialize(size_, pos_, vel_);
    if (&tex_ != &Cfg::textures.get((int)Cfg::Textures::Invariant))
        this->setTexture(tex_);
    _sprite.setTextureRect({ { 0,0 }, (sf::Vector2i)size_ });
    std::ifstream iFile;

    // should be a .anim file
    iFile.open("Assets/Animations/" + filepath_);

    if (!iFile.is_open() || !iFile.good())
    {
        std::cout << "DrawableObject::initialize() : File not loaded properly for Object ID " << this->getID() << std::endl;
        return;
    }
    else
    {
        // file loaded in correctly
        // STRUCTURE EXPECTED
        // number of animations || LOOP : || string name of animation || one texure offset value for animation x || (<- and the y) || one sizex for texRect || one sizey for texRect || number of frames in animation || startx || starty || pitch || ENDLOOP
        int numAnims;
        iFile >> numAnims;
       
        for (size_t i = 0; i < (size_t)numAnims; i++)
        {
            std::string animName, direction;
            int frameOffX, frameOffY;
            int frameSizeX, frameSizeY;
            int numFrames;
            int startX, startY;
            int pitch;
            iFile >> animName >> direction >> frameOffX >> frameOffY >> frameSizeX >> frameSizeY >> numFrames >> startX >> startY >> pitch;

            int rows = std::max((numFrames / pitch), 1);
            int cols = pitch;
            std::vector<sf::Vector2i> offsets_;
            offsets_.clear();
            offsets_.reserve(numFrames);
            for (int i = 0; i < numFrames; i++)
            {
                offsets_.push_back({ frameOffX, frameOffY });
            }

            std::vector<sf::IntRect> rects;
           
                rects = std::vector<sf::IntRect>{};
                rects.clear();
                rects.reserve(numFrames);
                for (size_t j = 0; j < (size_t)(rows); j++)
                {
                    for (size_t k = 0; k < numFrames; k++)
                    {

                        rects.emplace_back(sf::IntRect{ {startX + (int)k * (int)frameSizeX,startY + (int)j * (int)frameSizeY},{(int)frameSizeX,(int)frameSizeY} });
                    }
                }

           

                if (direction != "Uni")
                {
                        animHandler.addAnim(animName, rects, offsets_, { 0.13f }, true, true, "Right");
                        animHandler.addAnim(animName, rects, offsets_, { 0.13f }, true, false, "Left");
                }
                else
                {
                    animHandler.addAnim(animName, rects, offsets_, { 0.13f }, true, false, "Uni");
                }

         
                animHandler.changeAnim(animName);
            // one animation completed
        }

        _initialized = true;
        // all animations completed

        iFile.close();
    }
}
void DrawableObj::initializeAsTile(sf::IntRect rect_, sf::Vector2f pos_, const sf::Texture& tex_, const sf::Vector2i& offs_)
{
    
    if (&tex_ != &Cfg::textures.get((int)Cfg::Textures::Invariant))
        this->setTexture(tex_);

    this->setPos(pos_);
    std::vector<sf::Vector2i> offsets_;
    offsets_.clear();
    offsets_.push_back({ 0,0 });
    std::vector<sf::IntRect> rects;
    rects.clear();
    rects.push_back(rect_);
    animHandler.addAnim("Tile", rects, offsets_, 1000.f, true, "Uni");

    animHandler.changeAnim("Tile");

    _initialized = true;
}



//#include "DrawableObj.h"
//#include <iostream>
//#include <fstream>
//#include <GameObjects/Projectiles/Projectile.h>
//bool operator==(DrawableObj& lhs_, DrawableObj& rhs_)
//{
//	return lhs_.ID() == rhs_.ID();
//}
//
//
//void DrawableObj::initialize(const std::string& filepath_, sf::Vector2f size_, Cfg::Textures tex_, sf::Vector2f pos_, sf::Vector2f vel_)
//{
//	GObj::initialize(size_, pos_, vel_);
//	m_texture = tex_;
//
//	std::ifstream iFile;
//
//	// should be a .anim file
//	iFile.open("Assets/Animations/" + filepath_);
//
//	if (!iFile.is_open() || !iFile.good())
//	{
//		std::cout << "DrawableObject::initialize() : File not loaded properly for Object ID " << this->ID() << std::endl;
//		return;
//	}
//	else
//	{
//		// file loaded in correctly
//		// STRUCTURE EXPECTED
//		// number of animations || LOOP : || string name of animation || one texure offset value for animation x || (<- and the y) || one sizex for texRect || one sizey for texRect || number of frames in animation || startx || starty || pitch || ENDLOOP
//		int numAnims;
//		iFile >> numAnims;
//		
//		size_t currentNumAnims = m_texFramesRight.size();
//		for (size_t i = currentNumAnims; i < (size_t)numAnims + currentNumAnims; i++)
//		{
//			std::string animName, direction;
//			int frameOffX, frameOffY;
//			int frameSizeX, frameSizeY;
//			int numFrames;
//			int startX, startY;
//			int pitch;
//			iFile >> animName >> direction >> frameOffX >> frameOffY >> frameSizeX >> frameSizeY >> numFrames >> startX >> startY >> pitch;
//
//			int rows = std::max((numFrames / pitch), 1);
//			int cols = pitch;
//			
//			m_frameOffset[animName] = { (float)frameOffX, (float)frameOffY };
//			
//			if (direction == "Right")
//			{
//				m_texFramesRight[animName] = std::vector<sf::IntRect>{};
//				m_texFramesRight[animName].clear();
//				m_texFramesRight[animName].reserve(numFrames);
//				for (size_t j = 0; j < (size_t)(rows); j++)
//				{
//					for (size_t k = 0; k < numFrames; k++)
//					{
//
//						m_texFramesRight[animName].emplace_back(sf::IntRect{ {startX + (int)k * (int)frameSizeX,startY + (int)j * (int)frameSizeY},{(int)frameSizeX,(int)frameSizeY} });
//					}
//				}
//
//				if (m_anim == nullptr)
//				{
//					m_anim = &m_texFramesRight[animName];
//					m_animName = animName;
//				}
//			}
//			else if (direction == "Left")
//			{
//				m_texFramesLeft[animName] = std::vector<sf::IntRect>{};
//				m_texFramesLeft[animName].clear();
//				m_texFramesLeft[animName].reserve(numFrames);
//				for (size_t j = 0; j < (size_t)(rows); j++)
//				{
//					for (size_t k = 0; k < numFrames; k++)
//					{
//
//						m_texFramesLeft[animName].emplace_back(sf::IntRect{ {startX + (int)k * (int)frameSizeX,startY + (int)j * (int)frameSizeY},{(int)frameSizeX,(int)frameSizeY} });
//					}
//				}
//
//				if (m_anim == nullptr)
//				{
//					m_anim = &m_texFramesLeft[animName];
//					m_animName = animName;
//				}
//			}
//			else
//			{
//				m_texFramesUni[animName] = std::vector<sf::IntRect>{};
//				m_texFramesUni[animName].clear();
//				m_texFramesUni[animName].reserve(numFrames);
//				for (size_t j = 0; j < (size_t)(rows); j++)
//				{
//					for (size_t k = 0; k < numFrames; k++)
//					{
//
//						m_texFramesUni[animName].emplace_back(sf::IntRect{ {startX + (int)k * (int)frameSizeX,startY + (int)j * (int)frameSizeY},{(int)frameSizeX,(int)frameSizeY} });
//					}
//				}
//
//				if (m_anim == nullptr)
//				{
//					m_anim = &m_texFramesUni[animName];
//					m_animName = animName;
//				}
//			}
//
//			// one animation completed
//		}
//		// all animations completed
//
//		iFile.close();
//	}
//}
//
//void DrawableObj::initializeAsTile(sf::IntRect rect_, Cfg::Textures tex_, sf::Vector2f pos_)
//{
//	m_texture = tex_;
//	m_frameOffset["Tile"] = { 0.f,0.f };
//	m_texFramesUni["Tile"] = std::vector<sf::IntRect>{};
//	m_texFramesRight["Tile"] = std::vector<sf::IntRect>{};
//	m_texFramesLeft["Tile"] = std::vector<sf::IntRect>{};
//	m_texFramesUni["Tile"].clear();
//	m_currentFrame = 0;
//	m_animName = "Tile";
//	m_uniDirectional = true;
//
//	GObj::initialize((sf::Vector2f)rect_.size, pos_);
//	this->m_frameDelays["Tile"] = 0.f;
//	this->m_loopDelays["Tile"] = 0.f;
//	this->m_startDelays["Tile"] = 0.f;
//	this->m_texFramesUni["Tile"].push_back(rect_);
//	m_anim = &m_texFramesUni["Tile"];
//}
//
//DrawableObj::DrawableObj()
//	: GObj{}
//{
//	m_texFramesRight.clear();
//	m_frameOffset.clear();
//	m_startDelays.clear();
//	m_loopDelays.clear();
//	m_frameDelays.clear();
//}
//
//DrawableObj::~DrawableObj()
//{
//
//}
//
//DrawableObj::DrawableObj(const DrawableObj& o)
//	: GObj{}
//{
//	m_texFramesUni.clear();
//	m_texFramesLeft.clear();
//	m_texFramesRight.clear();
//	m_frameOffset.clear();
//	m_startDelays.clear();
//	m_loopDelays.clear();
//	m_frameDelays.clear();
//
//	if (o.m_animName == "Tile")
//	{
//		this->initializeAsTile(o.m_texFramesUni.at(o.m_animName).at(o.m_currentFrame), o.m_texture, o.GetPosition());
//		m_frameOffset["Tile"] = o.m_frameOffset.at("Tile");
//	}
//	else
//	{
//		GObj::initialize(o.GetSize(), o.GetPosition(), o.GetVelocity());
//		m_frameOffset[o.m_animName] = o.m_frameOffset.at(o.m_animName);
//
//	}
//}
//
//DrawableObj& DrawableObj::operator=(const DrawableObj& o)
//{
//
//	if (o.m_animName == "Tile")
//	{
//		this->initializeAsTile(o.m_texFramesUni.at(o.m_animName).at(o.m_currentFrame), o.m_texture, o.GetPosition());
//		m_frameOffset["Tile"] = o.m_frameOffset.at("Tile");
//
//	}
//	else
//	{
//		GObj::initialize(o.GetSize(), o.GetPosition(), o.GetVelocity());
//		m_frameOffset[o.m_animName] = o.m_frameOffset.at(o.m_animName);
//
//	}
//	return *this;
//}
//
//void DrawableObj::update(float dt_)
//{
//	// process input
//
//
//	// update direction and m_anim 
//	if (!m_uniDirectional)
//	{
//		//may switch
//		if (m_facingRight)
//		{
//			if (m_anim != &m_texFramesRight[m_animName])
//				m_anim = &m_texFramesRight[m_animName];
//		}
//		else
//		{
//			if (m_anim != &m_texFramesLeft[m_animName])
//				m_anim = &m_texFramesLeft[m_animName];
//		}
//	}
//	else
//	{
//		if (m_anim != &m_texFramesUni[m_animName])
//			m_anim = &m_texFramesUni[m_animName];
//
//	}
//
//	// if animated, animate here
//	GObj::tick(dt_);
//}
//
//void DrawableObj::render(sf::RenderWindow& wnd_)
//{
//	sf::Sprite spr(Cfg::textures.get((int)m_texture));
//	auto pos = GetPosition();
//	auto& offset = m_frameOffset[m_animName];
//	spr.setPosition({ pos.x - offset.x, pos.y - offset.y });
//	if (m_uniDirectional)
//	{
//		spr.setTextureRect(m_texFramesUni[m_animName].at(m_currentFrame));
//	}
//	else
//	{
//		if (m_facingRight)
//		{
//			spr.setTextureRect(m_texFramesRight[m_animName].at(m_currentFrame));
//		}
//		else
//		{
//			spr.setTextureRect(m_texFramesLeft[m_animName].at(m_currentFrame));
//		}
//	}
//	wnd_.draw(spr);
//}
//
//void DrawableObj::ChangeAnim(const std::string& animName)
//{
//	if (this->m_facingRight && !this->m_uniDirectional) {
//		if (m_texFramesRight.find(animName) == m_texFramesRight.end())
//		{
//			std::cout << "Unable to find animation : " << animName << " in the texFrames of Object ID " << this->ID() << std::endl;
//			return;
//		}
//		m_anim = &m_texFramesRight[animName];
//		
//	}
//	else if (!this->m_facingRight && !this->m_uniDirectional) {
//		if (m_texFramesLeft.find(animName) == m_texFramesLeft.end())
//		{
//			std::cout << "Unable to find animation : " << animName << " in the texFrames of Object ID " << this->ID() << std::endl;
//			return;
//		}
//		m_anim = &m_texFramesLeft[animName];
//	}
//	else
//	{
//		if (m_texFramesUni.find(animName) == m_texFramesUni.end())
//		{
//			std::cout << "Unable to find animation : " << animName << " in the texFrames of Object ID " << this->ID() << std::endl;
//			return;
//		}
//		m_anim = &m_texFramesUni[animName];
//	}
//	m_currentFrame = 0;
//	m_animName = animName;
//	if (m_animName == "Idle")
//	{
//		m_looping = true;
//		m_loopWaits = true;
//	}
//	else if (m_animName == "Moving")
//	{
//		m_looping = true;
//		m_loopWaits = false;
//	}
//	else if (m_animName == "StartedMoving")
//	{
//		m_looping = false;
//		m_loopWaits = false;
//	}
//}
//
//void DrawableObj::animate()
//{
//	if (this->m_playing)
//	{
//		if (m_currentFrame == m_anim->size() - 1)
//		{
//			if (this->m_looping)
//			{
//				m_currentFrame = 0;
//			}
//		}
//		else {
//			m_currentFrame++;
//
//			if (m_currentFrame > m_anim->size() - 1)
//			{
//				if (m_looping)
//				{
//					m_currentFrame = 0;
//				}
//				else
//				{
//					m_currentFrame = m_anim->size() - 1;
//				}
//			}
//
//		}
//	}
//}
//
//void DrawableObj::SetSize(const sf::Vector2f& size_)
//{
//	getPositionRef() = size_;
//}
//
//void DrawableObj::AdjustPosition(const sf::Vector2f& amt_)
//{
//	getPositionRef() += amt_;
//}
//
//void DrawableObj::SetPosition(const sf::Vector2f& pos_)
//{
//	getPositionRef() = pos_;
//}
//
//void DrawableObj::AdjustVelocity(const sf::Vector2f& amt_)
//{
//	getVelocityRef() += amt_;
//}
//
//void DrawableObj::SetVelocity(const sf::Vector2f& vel_)
//{
//	getVelocityRef() = vel_;
//}
//
//sf::Vector2f DrawableObj::getTexRectSize()
//{
//	if (m_animName == "None") 
//	{
//		std::cout << "Tried to get a texRectSize from m_texFramesRight without any anims added, nor frames to get the size of!  obj id " << this->ID() << std::endl;
//		return sf::Vector2f(0, 0); 
//	}
//	return (sf::Vector2f)m_anim->at(m_currentFrame).size;
//}
//
//Cfg::Textures DrawableObj::getTextureID()
//{
//	return m_texture;
//}
//
//sf::Vector2f DrawableObj::getTexRectPos()
//{
//	if (m_anim == nullptr) { return sf::Vector2f(0, 0); }
//	return (sf::Vector2f)m_anim->at(m_currentFrame).position;
//}
//
//void DrawableObj::setFrameOffset(std::string animName_, sf::Vector2f offset_)
//{
//	m_frameOffset[animName_] = offset_;
//}
//
//sf::Vector2f DrawableObj::getFrameOffset()
//{
//	return m_frameOffset[m_animName];
//}

