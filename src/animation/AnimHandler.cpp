
// ===== AnimHandler.cpp =====
#include "AnimHandler.h"
#include <assert.h>
#include <GameObjects/StandardEnemy/StandardEnemy.h>

AnimHandler::AnimHandler()
    : _currentAnim(""), _currIndex(0), _frameElapsed(0.f), _nullFrame(), _nullOffset(0, 0), _facingRight{ true }
{

}

void AnimHandler::changeAnim(const std::string& animName)
{
    if (_currentAnim != animName && _animations.count(animName))
    {
        _currentAnim = animName;
        _currIndex = 0;
        _frameElapsed = 0.f;
    }
}




void AnimHandler::update(float dt)
{
    if (_currentAnim.empty() || !_animations.count(_currentAnim))
    {
        return;
    }

    Animation& anim = _animations[_currentAnim];

    _frameElapsed += dt;

    if (_frameElapsed >= anim.frameDelay) 
    {
        _frameElapsed = 0.f;
        _currIndex++;

        if (anim.uniDir)
        {
            if (_currIndex >= anim.framesUni.size())
            {
                if (anim.loop)
                    _currIndex = 0;
                else
                    _currIndex = anim.framesUni.size() - 1;
            }
        }
        else if (_facingRight)
        {
                if (_currIndex >= anim.framesRight.size())
                {
                    if (anim.loop)
                        _currIndex = 0;
                    else
                        _currIndex = anim.framesRight.size() - 1;
                }
        }
        else
        {
            if (_currIndex >= anim.framesLeft.size())
            {
                if (anim.loop)
                    _currIndex = 0;
                else
                    _currIndex = anim.framesLeft.size() - 1;
            }
        }
    }
}

bool AnimHandler::isLooping(const std::string& animName)
{
    return _animations.at(animName).loop; 
}

const sf::IntRect& AnimHandler::getCurrFRect() const
{
    if (_currentAnim == "") { return _nullFrame; }

    if (_currentAnim.empty() || !_animations.count(_currentAnim)) return _nullFrame;
    const Animation& anim = _animations.at(_currentAnim);
    if (anim.uniDir)
    {
        return anim.framesUni[_currIndex];

    }
    else if (_facingRight)
    {
        return anim.framesRight[_currIndex];

    }
    else
    {
        return anim.framesLeft[_currIndex];

    }
}

const sf::Vector2i& AnimHandler::getCurrTexOff() const {
    if (_currentAnim == "")
    {
        if (_animations.find("Tile") == _animations.end())
        {
            // not a tile
            const Animation& anim = _animations.at("Idle");
            return anim.textureOffsets[_currIndex];
        }
        else
        {
            const Animation& anim = _animations.at("Tile");
            return anim.textureOffsets[_currIndex];
        }
    }
    else
    {

        const Animation& anim = _animations.at(_currentAnim);
        return anim.textureOffsets[_currIndex];
    }
}

void AnimHandler::setFacingRight(bool cond_)
{
    _facingRight = cond_;
}

bool AnimHandler::isFacingRight() const
{
    return _facingRight; 
}

bool AnimHandler::isCurrUniDir()
{
    if (_currentAnim == "") { return false; }
    return _animations.at(_currentAnim).uniDir;
}

void AnimHandler::setFrameOffsets( sf::Vector2i off_, int index, std::string animName)
{
    if (_animations.find(animName) == _animations.end())
    {
        _animations[animName] = Animation{};
        _animations[animName].textureOffsets = { off_ };
        return; 
    
    }
    if (animName == "Current")
    {
        if (index == -1)
            _animations.at(_currentAnim).textureOffsets.at(_currIndex) = off_;
        else
            _animations.at(_currentAnim).textureOffsets.at(index) = off_;

    }
    else
    {
        if (index == -1)
            _animations.at(animName).textureOffsets.at(_currIndex) = off_;
        else
            _animations.at(animName).textureOffsets.at(index) = off_;
    }
   
}

sf::Vector2i AnimHandler::getFrameOffsets(int index, std::string animName, bool uniDirectional)
{
    if (animName == "Current")
    {
        if (index == -1)
        {
            if (uniDirectional)
                return _animations.at(_currentAnim).framesUni.at(_currIndex).position;
            else
            {
                if (_animations.at(_currentAnim).framesLeft.size() <= 0 || _animations.at(_currentAnim).framesRight.size() <= 0) { return { 0,0 }; }
                return _animations.at(_currentAnim).framesRight.at(_currIndex).position;
            }

        }
        else
        {
            if (uniDirectional)
                return _animations.at(_currentAnim).framesUni.at(index).position;
            else
            {
                if (_animations.at(_currentAnim).framesLeft.size() <= 0 || _animations.at(_currentAnim).framesRight.size() <= 0) { return { 0,0 }; }
                return _animations.at(_currentAnim).framesRight.at(index).position;
            }
        }
           
    }
    else
    {
        if (index == -1)
        {
            if (uniDirectional)
                return _animations.at(animName).framesUni.at(_currIndex).position;
            else
            {
                if (_animations.at(animName).framesLeft.size() <= 0 || _animations.at(animName).framesRight.size() <= 0) { return { 0,0 }; }
                return _animations.at(animName).framesRight.at(_currIndex).position;
            }

        }
        else
        {
            if (uniDirectional)
                return _animations.at(animName).framesUni.at(index).position;
            else
            {
                if (_animations.at(animName).framesLeft.size() <= 0 || _animations.at(animName).framesRight.size() <= 0) { return { 0,0 }; }
                return _animations.at(animName).framesRight.at(index).position;
            }
        }
    }
}

sf::Vector2i AnimHandler::getTexOffset(const std::string& animName)
{
    if (animName == "Current")
        return this->_animations.at(_currentAnim).textureOffsets[_currIndex];
    else
        return this->_animations.at(animName).textureOffsets[_currIndex];
}

void AnimHandler::resizeFrames(const std::string& animName_, const std::string& dir_, int size_)
{
    if (_animations.find(animName_) == _animations.end())
        return;

    if (dir_ == "Uni")
    {
        _animations[animName_].framesUni.resize(size_);

    }
    else if (dir_ == "Right")
    {
        _animations[animName_].framesRight.resize(size_);

    }
    else if (dir_ == "Left")
    {
        _animations[animName_].framesLeft.resize(size_);

    }
    else
    {
        assert(7 > 8);
    }

}

void AnimHandler::addAnim(const std::string& name,std::vector<sf::IntRect>& frames,std::vector<sf::Vector2i>& offsets,float frameDelay, bool loop, bool facingRight_, std::string dir_) {
    


    if (frames.size() != offsets.size()) return;
    
    if (_animations.find(name) == _animations.end())
    {
        bool dirUni;
        if (dir_ == "Uni")
            dirUni = true;
        else
            dirUni = false;
        _animations[name] = Animation{ frames, offsets, frameDelay, loop, facingRight_, dirUni };
        _uniDirectional = true;
    }
    else
    {
        if (dir_ == "Uni")
        {
            _animations.at(name).framesUni = frames;
            _uniDirectional = true;
        }
        else if (dir_ == "Right")
        {
            _animations.at(name).framesRight = frames;
                _uniDirectional = false;

        }
        else if (dir_ == "Left")
        {
            _animations.at(name).framesLeft = frames;
            _uniDirectional = false;

        }
        else
        {
            assert(5 > 6);
        }
    }

  
}

AnimHandler::Animation& AnimHandler::getAnimation(std::string animName_)
{
    return _animations.at(animName_);
}
sf::IntRect AnimHandler::getLeftFrame(int index)
{
    if (index == -1)
    {
        return _animations.at(_currentAnim).framesLeft.at(_currIndex);
    }
    return _animations.at(_currentAnim).framesLeft.at(index);
}
sf::IntRect AnimHandler::getRightFrame(int index)
{
    if (index == -1)
    {
        return _animations.at(_currentAnim).framesRight.at(_currIndex);
    }
    return _animations.at(_currentAnim).framesRight.at(index);
}
sf::IntRect AnimHandler::getUniFrame(int index)
{
    if (index == -1)
    {
        return _animations.at(_currentAnim).framesUni.at(_currIndex);
    }
    return _animations.at(_currentAnim).framesUni.at(index);
}
int AnimHandler::getCurrentIndex()
{
    return (int)_currIndex;
}

void AnimHandler::setCurrentIndex(int index)
{
    _currIndex = index;
}
size_t AnimHandler::getNumAnims()
{
    if (_animations.empty())
        return 0;
    return _animations.size();
}
std::vector<std::string> AnimHandler::getAnimNames(const std::string& dir_)
{
    std::vector<std::string> animNames;
    animNames.clear();
    animNames.reserve(_animations.size());
    for (auto name : _animations)
    {
        animNames.emplace_back(name.first);
    }
    return animNames;
}
void AnimHandler::setFrameDelay(float frameDelay_, std::string animName)
{
    if (animName == "Current")
    {
        _animations.at(_currentAnim).frameDelay = frameDelay_;

    }
    else
    {
        _animations.at(animName).frameDelay = frameDelay_;
    }
}
float AnimHandler::getFrameDelay(std::string animName)
{
    if (animName == "Current")
    {
        return _animations.at(_currentAnim).frameDelay;
    }
    else
    {
        return _animations.at(animName).frameDelay;
    }

}
std::string AnimHandler::getAnimName() const
{
    return _currentAnim;
}


 const std::vector<sf::IntRect>& AnimHandler::getFrames(std::string dir_, std::string anim_) const
{
     
    if (anim_ == "Current")
    {
        if (dir_ == "Uni")
        {
            return this->_animations.at(_currentAnim).framesUni;
        }
        else if (dir_ == "Left")
        {
            return this->_animations.at(_currentAnim).framesLeft;
        }
        else if (dir_ == "Right")
        {
            return this->_animations.at(_currentAnim).framesRight;
        }
        else
        {
            assert(1 > 2);
        }
    }
    else
    {
        if (dir_ == "Uni")
        {
            return this->_animations.at(anim_).framesUni;
        }
        else if (dir_ == "Left")
        {
            return this->_animations.at(anim_).framesLeft;
        }
        else if (dir_ == "Right")
        {
            return this->_animations.at(anim_).framesRight;
        }
        else
        {
            assert(3 > 4);
        }
    }
    return this->_animations.at(anim_).framesUni;
}

 void AnimHandler::setFrame(const sf::IntRect& rect_,const std::string& animName_, int index, const std::string& dir_)
 {
     if (_animations.find(animName_) != _animations.end())
     {
         if (dir_ == "Uni")
         {
             if (index < _animations.at(animName_).framesUni.size() && index >= 0)
                 _animations.at(animName_).framesUni[index] = rect_;
         }
         else if (dir_ == "Right")
         {
             if (index < _animations.at(animName_).framesRight.size() && index >= 0)
                 _animations.at(animName_).framesRight[index] = rect_;

         }
         else if (dir_ == "Left")
         {
             if (index < _animations.at(animName_).framesLeft.size() && index >= 0)
                 _animations.at(animName_).framesLeft[index] = rect_;

         }
         else
         {
             assert(10 > 11);
         }
     }
 }

 void AnimHandler::setLooping(const std::string& animName, bool cond_)
 {
     this->_animations.at(animName).loop = cond_;
 }

 void AnimHandler::setUniDir(bool cond_)
 {
    this->_uniDirectional = cond_;
 }

 std::unordered_map<std::string, AnimHandler::Animation>& AnimHandler::getAnims()
 {
     return _animations;
 }
