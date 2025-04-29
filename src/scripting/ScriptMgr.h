#ifndef SCRIPTMGR_H__
#define SCRIPTMGR_H__

class Enemy;
class GameState;
class ScriptMgr
{
public:
	ScriptMgr(Enemy* owner_);
	~ScriptMgr();

	Enemy* owner;

	void update(float dt_, GameState* state_);
};

#endif