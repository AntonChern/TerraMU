#pragma once
#include "Action.h"

class OpenChestAction : public Action {
public:
	void execute();
	void unexecute();
};