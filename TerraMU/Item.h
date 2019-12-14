#pragma once
#include "DroppedItem.h"
#include "PickedItem.h"
#include "GameController.h"

class Item {
private:

protected:
	DroppedItem* dropped;
	PickedItem* picked;
	string name;

public:
	Item(string texturePath, string name);
	~Item();

	DroppedItem* getDropped() { return dropped; };
	PickedItem* getPicked() { return picked; };
	string getName() { return name; };

	void interact();

};