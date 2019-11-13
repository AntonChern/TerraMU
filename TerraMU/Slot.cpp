#include "Slot.h"

Slot::Slot(vec3 position, float rotationX, float rotationY, float rotationZ, vec3 scale) :
	GuiItem(false, position, rotationX, rotationY, rotationZ, scale), isPlaced(false) {
	icon = GuiElementFactory::createGuiElement("slot.png", position, rotationX, rotationY, rotationZ, scale);
	iconPlaced = GuiElementFactory::createGuiElement("slot_placed.png", position, rotationX, rotationY, rotationZ, scale);
	icons.push_back(icon);
	icons.push_back(iconPlaced);
}

void Slot::prepareForGettingIcons() {
	icons.remove(iconPlaced);
	if (isPlaced) {
		icons.push_back(iconPlaced);
	}

	/*for (GuiElement* icon : icons) {
		icon->setPosition(position);
		icon->setRotationX(rotationX);
		icon->setRotationY(rotationY);
		icon->setRotationZ(rotationZ);
		icon->setScale(scale);
	}*/
}

//list<GuiElement*> Slot::getIcons() {
//	list<GuiElement*> icons;
//
//	/*icon->setPosition(position);
//	icon->setRotationX(rotationX);
//	icon->setRotationY(rotationY);
//	icon->setRotationZ(rotationZ);
//	icon->setScale(scale);*/
//
//	icons.push_back(icon);
//
//	if (isPlaced) {
//		/*iconPlaced->setPosition(position);
//		iconPlaced->setRotationX(rotationX);
//		iconPlaced->setRotationY(rotationY);
//		iconPlaced->setRotationZ(rotationZ);
//		iconPlaced->setScale(scale);*/
//
//		icons.push_back(iconPlaced);
//	}
//
//	for (GuiElement* icon : GuiItem::getIcons()) {
//		icons.push_back(icon);
//	}
//
//	return icons;
//}

void Slot::placed(float x, float y) {
	GuiItem::placed(x, y);

	isPlaced = true;
}

void Slot::unplaced(float x, float y) {
	GuiItem::unplaced(x, y);

	isPlaced = false;
}