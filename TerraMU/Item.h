#pragma once
#define GLM_FORCE_RADIANS
class DroppedItem;
class PickedItem;
#include <string>
using namespace std;

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