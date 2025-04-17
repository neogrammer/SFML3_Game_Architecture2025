#pragma once
#include "GameObject.h"
#include <handlers/AnimMgr.h>
class AnimObject : public GameObject
{
public:
	AnimMgr animMgr{};
public:
	using GameObject::GameObject;
<<<<<<< HEAD

	virtual ~AnimObject() override {}
	virtual void handleInput() override {}
	virtual void executeScript() override {}
	virtual void setTexRect(sf::IntRect tRect_);
	virtual void update(float dt_) override = 0;
	virtual void finalize(float dt_) override = 0;
=======
	virtual ~AnimObject() override;

>>>>>>> 715163d0180834600f23e60846ea0b9689190064
	std::string loadInFile(std::string animFile_);
};