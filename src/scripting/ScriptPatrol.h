#ifndef SCRIPTPATROL_H__
#define SCRIPTPATROL_H__

#include "Script.h"

class ScriptPatrol : public Script
{
public:
	ScriptPatrol(Enemy* owner_);
	~ScriptPatrol();

	void update(float dt_, GameState* state_);

};

#endif