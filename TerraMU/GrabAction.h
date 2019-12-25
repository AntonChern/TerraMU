#pragma once
#include "Action.h"
class Item;

class GrabAction : public Action {
private:
	Item* target;

public:
	GrabAction(Item* target) : target(target) {};

	void execute();
	void unexecute() {};

	void setItem(Item* item) { target = item; };
	Item* getGrabbedItem();

};