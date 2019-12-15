#pragma once
#include "Action.h"

class GoAction : public Action {
private:

public:
	GoAction(float x, float y) : Action(x, y) {};
	GoAction() : GoAction(0.0f, 0.0f) {};

	void execute();
	void unexecute() {};

};