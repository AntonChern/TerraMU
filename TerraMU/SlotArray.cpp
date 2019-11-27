#include "SlotArray.h"

SlotArray::SlotArray(int columns, int rows, vec3 position, float rotationX, float rotationY, float rotationZ, vec3 scale) :
	GuiItem(false, position, rotationX, rotationY, rotationZ, scale), columns(columns), rows(rows) {
	for (int j = 0; j < rows; j++) {
		for (int i = 0; i < columns; i++) {
			vec3 currPosition = vec3(position.x + scale.x * ((float)(2 * i + 1) / columns - 1) / 2,
				position.y + scale.y * (1 - (float)(2 * j + 1) / rows) / 2, position.z);

			addChild({ new Slot(currPosition, rotationX, rotationY, rotationZ, vec3(scale.x / columns, scale.y / rows, scale.z)) });
		}
	}
}

void SlotArray::prepareForGettingIcons() {
	int i = 0;
	int j = 0;
	for (GuiItem* child : getChildren()) {
		child->setPosition(position.x + scale.x * ((float)(2 * i + 1) / columns - 1) / 2,
			position.y + scale.y * (1 - (float)(2 * j + 1) / rows) / 2, position.z);
		child->setRotationX(rotationX);
		child->setRotationY(rotationY);
		child->setRotationZ(rotationZ);
		child->setScale(vec3(scale.x / columns, scale.y / rows, scale.z));
		i++;
		if (i == columns) {
			i = 0;
			j++;
		}
	}
}

//list<GuiElement*> SlotArray::getIcons() {
//	list<GuiElement*> icons;
//
//	/*int i = 0;
//	int j = 0;
//	for (GuiItem* child : getChildren()) {
//		child->setPosition(position.x + scale.x * ((float)(2 * i + 1) / columns - 1) / 2,
//			position.y + scale.y * (1 - (float)(2 * j + 1) / rows) / 2, position.z);
//		child->setRotationX(rotationX);
//		child->setRotationY(rotationY);
//		child->setRotationZ(rotationZ);
//		child->setScale(vec3(scale.x / columns, scale.y / rows, scale.z));
//		i++;
//		if (i == columns) {
//			i = 0;
//			j++;
//		}
//	}*/
//
//	for (GuiElement* icon : GuiItem::getIcons()) {
//		icons.push_back(icon);
//	}
//
//	return icons;
//}