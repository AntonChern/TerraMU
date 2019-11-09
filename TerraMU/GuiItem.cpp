#include "GuiItem.h"

void GuiItem::changeVisibility() {
	isVisible = !isVisible;
	for (GuiItem* child : children) {
		child->changeVisibility();
	}
}

void GuiItem::addChildren(list<GuiItem*> children) {
	for (GuiItem* item : children) {
		addChild(item);
	}
}

void GuiItem::removeChildren(list<GuiItem*> children) {
	for (GuiItem* item : children) {
		removeChild(item);
	}
}

list<GuiElement*> GuiItem::getIcons() {
	list<GuiElement*> icons;

	for (GuiItem* child : children) {
		for (GuiElement* gui : child->getIcons()) {
			icons.push_back(gui);
		}
	}

	return icons;
}

void GuiItem::placed(float x, float y) {
	for (GuiItem* child : getChildren()) {
		if (abs(x - child->getPosition().x) < child->getScale().x / 2 && abs(y - child->getPosition().y) < child->getScale().y / 2) {
			child->placed(x, y);
			return;
		}
	}
}

void GuiItem::unplaced(float x, float y) {
	for (GuiItem* child : getChildren()) {
		if (abs(x - child->getPosition().x) < child->getScale().x / 2 && abs(y - child->getPosition().y) < child->getScale().y / 2) {
			child->unplaced(x, y);
			return;
		}
	}
}