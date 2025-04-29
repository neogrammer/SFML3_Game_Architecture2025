#include "Script.h"

#include <core/states/StateBase.h>
#include <handlers/GStateMgr.h>

Script::Script(Enemy* owner_)
	: owner{owner_}
{
}

Script::~Script()
{
}
