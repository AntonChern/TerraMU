#pragma once
#include "GameController.h"

class Action {
protected:
	float coordX;
	float coordY;

public:

	virtual void setPosition(float x, float y) { coordX = x; coordY = y; };

	virtual void execute() {};
	virtual void unexecute() {};

};