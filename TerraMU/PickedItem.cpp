#include "PickedItem.h"

PickedItem::PickedItem(string texturePath) {
	icon = new Picture(texturePath.c_str(), vec3(0.0f), 0.0f, 0.0f, 0.0f, 1.0f);
}

PickedItem::~PickedItem() {
	delete icon;
}