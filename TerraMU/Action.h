#pragma once
#include "GameController.h"

class Action {
protected:
	//GameController receiver;

public:
	virtual void execute() {};
	virtual void unexecute() {};

};