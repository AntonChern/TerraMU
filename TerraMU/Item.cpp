#include "Item.h"

Item::Item(string texturePath, string name) {
	dropped = new DroppedItem(texturePath, name, vec3(0.0f), 0.0f, 0.0f, 0.0f, GameController::WORLD_SCALE);
	picked = new PickedItem(texturePath);
}

Item::~Item() {
	delete dropped;
	delete picked;
}

void Item::interact() {
	cout << "ITEM INTERACT!" << endl;
}
