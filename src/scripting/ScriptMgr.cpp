#include "ScriptMgr.h"

#include <core/states/StateBase.h>

ScriptMgr::ScriptMgr(Enemy* owner_)
	: owner{owner_}
{
}

ScriptMgr::~ScriptMgr()
{
}

void ScriptMgr::update(float dt_, GameState* state_)
{
	
}
