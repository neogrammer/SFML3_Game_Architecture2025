#pragma once
#include "GameObject.h"
#include <handlers/AnimMgr.h>
class FaceObject : public GameObject
{
public:
	AnimMgr animMgr{};
public:
	using GameObject::GameObject;

	virtual ~FaceObject() override final {}
};