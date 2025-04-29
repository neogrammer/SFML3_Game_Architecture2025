#ifndef SCRIPT_H__
#define SCRIPT_H__

class GameState;
class Enemy;
class Script
{
public:
	Script(Enemy* owner_);
	~Script();

	Enemy* owner;

	virtual void update(float dt_, GameState* state_) = 0;
};

#endif