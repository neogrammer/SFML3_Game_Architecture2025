#ifndef SIMPLEPLATFORM_H__
#define SIMPLEPLATFORM_H__
#include "GameObject.h"
#include <vector>
#include <SFML/Graphics/RenderWindow.hpp>
class  SimplePlatform : public GameObject
{
	int numObjectsAttached{ 0 };
	std::vector<GameObject*> attachedObjects{};

	bool movingUp{ false };
	bool movingDown{ false };

	float upDist{ 300.f };
	float downDist{ 30.f };
	float originalPosY{ GameObject::getPosition().y };

	float atTargetWaitElapsed{ 0.f };
	float atTargetWait{ 3.f };
	bool atTarget{ false };
public:
	using GameObject::GameObject;
	~SimplePlatform() override final;

	std::vector<GameObject*>& getAttachedObjects();
	GameObject* getAttached(int index);
	GameObject* getFirstAttached();
	GameObject* getLastAttached();
	bool isObjectAttached(GameObject* obj_);
	void attach(GameObject* obj_);
	void detach(GameObject* obj_);
	void detach(int index);
	void detachAll();
	int getNumAttached();
	virtual void getHit(int power) override {};
	void update(float dt_);
	void finalize(float dt_, sf::RenderWindow& wnd_);

};

#endif