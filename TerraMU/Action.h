#pragma once

class Action {
protected:
	float coordX;
	float coordY;

public:
	Action(float x, float y) : coordX(x), coordY(y) {};
	Action() : Action(0.0f, 0.0f) {};

	virtual void setPosition(float x, float y) { coordX = x; coordY = y; };

	virtual void execute() {};
	virtual void unexecute() {};

};