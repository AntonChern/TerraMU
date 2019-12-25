#include "Slot.h"
#include "GuiElement.h"
#include "GuiElementFactory.h"
#include "PickedItem.h"
#include "Item.h"
#include "Picture.h"

Slot::Slot(vec3 position, float rotationX, float rotationY, float rotationZ, vec3 scale) :
	GuiItem(position, rotationX, rotationY, rotationZ, scale), isPlaced(false) {
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

	for (GuiElement* icon : icons) {
		icon->setPosition(position);
		icon->setRotationX(rotationX);
		icon->setRotationY(rotationY);
		icon->setRotationZ(rotationZ);
		icon->setScale(scale);
	}
}

bool Slot::setItem(Item* item) {
	this->item = item;

	if (!item) {
		return false;
	}

	Picture* picture = item->getPicked()->getIcon();

	//set picture coords and scale
	picture->setPosition(position);
	picture->setScale(scale);
	picture->setRotationX(rotationX);
	picture->setRotationY(rotationY);
	picture->setRotationZ(rotationZ);

	addChild(picture);
	return true;
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

bool Slot::clicked(float x, float y) {
	if (GuiItem::clicked(x, y)) {
		grab->setItem(item);
		grab->execute();
		item = grab->getGrabbedItem();
		return true;
	}
	return false;
}