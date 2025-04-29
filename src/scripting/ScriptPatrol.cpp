#include "ScriptPatrol.h"

#include <core/states/StateBase.h>
#include <handlers/GStateMgr.h>

ScriptPatrol::ScriptPatrol(Enemy* owner_)
	: Script{owner_}
{
}

ScriptPatrol::~ScriptPatrol()
{
}

void ScriptPatrol::update(float dt_, GameState* state_)
{
}
