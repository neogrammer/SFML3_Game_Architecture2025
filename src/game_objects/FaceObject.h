#pragma once
#include "GameObject.h"
class FaceObject : public GameObject
{
public:
	using GameObject::GameObject;

	virtual ~FaceObject() override final {}
};