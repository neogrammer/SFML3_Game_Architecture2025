#pragma once
#include "GameObject.h"
#include <handlers/AnimMgr.h>
class AnimObject : public GameObject
{
public:
	AnimMgr animMgr{};
public:
	using GameObject::GameObject;

	virtual ~AnimObject() override final {}

	std::string loadInFile(std::string animFile_);
};