#pragma once
#define GLM_FORCE_RADIANS
class Item;
#include "Action.h"

class PickUpItemAction : public Action {
private:
	Item* item;

public:
	PickUpItemAction(Item* item) : item(item) {};

	void execute();
	void unexecute() {};

};