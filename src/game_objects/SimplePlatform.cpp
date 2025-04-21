#include "SimplePlatform.h"
#include <err/ErrorMacros.h>
#include "Player.h"
SimplePlatform::~SimplePlatform()
{
}

std::vector<GameObject*>& SimplePlatform::getAttachedObjects()
{
	return  attachedObjects;
}

GameObject* SimplePlatform::getAttached(int index_)
{
	if (index_ >= attachedObjects.size())
	{
		return nullptr;
		//throw CidError{ __LINE__, __FILE__, "You are trying to grab an index from the attached objects on a simple platform that does not exist, returning nullptr" };
	}
	return attachedObjects[index_];
}

GameObject* SimplePlatform::getFirstAttached()
{
	if (attachedObjects.empty()) {
		return nullptr;
	}
	return attachedObjects[0];
}

GameObject* SimplePlatform::getLastAttached()
{
	
	if (attachedObjects.empty()) {
		return nullptr;
	}
	return attachedObjects[attachedObjects.size() - 1];
}

bool SimplePlatform::isObjectAttached(GameObject* obj_)
{
	for (auto* o : attachedObjects)
	{
		if (o == obj_)
		{
			return true;
		}
	}
	return false;
}

void SimplePlatform::attach(GameObject* obj_)
{
	bool found = false;
	for (auto* o : attachedObjects)
	{
		if (obj_ == o)
		{
			// already in vector, break out
			found = true;
			break;
		}
	}
	if (found) { return; }

	attachedObjects.push_back(obj_);
}

void SimplePlatform::detach(GameObject* obj_)
{
	
	for (std::vector<GameObject*>::iterator it = attachedObjects.begin(); it != attachedObjects.end(); it++)
	{
		if (*it == obj_)
		{
			//  dont call this, i think, *it = nullptr;
			attachedObjects.erase(it);
			return;
		}
	}
}

void SimplePlatform::detach(int index_)
{
	if (index_ >= attachedObjects.size())
	{
		return;
	}
	std::vector<GameObject*>::iterator itt = attachedObjects.begin();
	for (int i = 0; i < index_ && itt != attachedObjects.end(); i++, itt++)
	{
		
	}
	attachedObjects.erase(itt);
}

void SimplePlatform::detachAll()
{
	attachedObjects.clear();
}

int SimplePlatform::getNumAttached()
{
	return (int)attachedObjects.size();
}

void SimplePlatform::update(float dt_)
{
	if (!atTarget)
	{
		if (movingUp)
		{
			if (originalPosY - getPosition().y > originalPosY - (originalPosY - upDist))
			{
				setPosition({ getPosition().x, originalPosY - upDist });
				velocity.y = 0.f;
				atTarget = true;
				atTargetWaitElapsed = 0.f;
			}
		}
		
		if (movingDown)
		{
			if (getPosition().y - originalPosY > downDist)
			{
				setPosition({ getPosition().x, originalPosY + downDist });
				velocity.y = 0.f;
				atTarget = true;
				atTargetWaitElapsed = 0.f;
			}
		}

		if (!movingUp && !movingDown)
		{
			movingUp = true;
			velocity.y = -100.f;
		}
	}
	else
	{
		atTargetWaitElapsed += dt_;
		if (atTargetWaitElapsed >= atTargetWait)
		{
			atTarget = false;
			if (movingUp)
			{
				movingUp = false;
				movingDown = true;
				velocity.y = 100.f;

				if (!attachedObjects.empty())
				{
				auto* p =	dynamic_cast<Player*>(attachedObjects[0]);

				}
			}
			else
			{
				movingUp = true;
				movingDown = false;
				velocity.y = -100.f;
			}
			atTargetWaitElapsed = 0.f;
		}

	}
}

void SimplePlatform::finalize(float dt_, sf::RenderWindow& wnd_)
{
	// finalize before finalizing the player so they can take this movement in account, so platforms finalize first


	for (auto* o : attachedObjects)
	{
		if (o->getVelocity().y > 0.f)
		{
			o->setVelocity({ o->getVelocity().x,0.f });
			o->setVelocity({ o->getVelocity().x + velocity.x, o->getVelocity().y + velocity.y });
		}
		if (o->getVelocity().y < 0.f)
		{
			if (velocity.y < 0.f)
			{
				// if platform is moving up as well as the player, then if the velocity is less than the amount the platform is, then set the players velocity to zero so they will ride along the speed of the platform
				// otherwise do not update the players velocity at all
				if (std::fabsf(o->getVelocity().y) <= std::fabsf(velocity.y))
				{
					o->setVelocity({ o->getVelocity().x, 0.f });
					o->setVelocity({ o->getVelocity().x + velocity.x, o->getVelocity().y + velocity.y });

				}
				else
				{
					detach(o);
					continue;
				}

			}
			else
			{
				detach(o);
				continue;
			}
		}
	}

	move(velocity * dt_);
}
