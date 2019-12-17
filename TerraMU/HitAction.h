#pragma once
#include "Action.h"

class HitAction : public Action {
private:
	Creature* target;
public:
	HitAction(Creature* target) : target(target) {};

	void execute();
	void unexecute() {};

};