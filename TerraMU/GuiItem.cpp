#include "GuiItem.h"

GuiItem::~GuiItem() {
	for (GuiItem* child : children) {
		delete child;
	}
	GuiElementFactory::cleanGuis(icons);
}

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

	prepareForGettingIcons();

	for (GuiElement* icon : this->icons) {
		icons.push_back(icon);
	}

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

void GuiItem::setPosition(vec3 position) {
	vec3 delta = position - this->position;
	for (GuiItem* child : children) {
		child->increasePosition(delta);
	}
	this->position = position;
}

void GuiItem::setScale(vec3 s) {
	vec3 delta = s - scale;
	for (GuiItem* child : children) {
		child->increaseScale(delta);
	}
	scale = s;
}

void GuiItem::setRotationX(float r) {
	float delta = r - rotationX;
	for (GuiItem* child : children) {
		child->increaseRotationX(delta);
	}
	rotationX = r;
}

void GuiItem::setRotationY(float r) {
	float delta = r - rotationY;
	for (GuiItem* child : children) {
		child->increaseRotationY(delta);
	}
	rotationY = r;
}

void GuiItem::setRotationZ(float r) {
	float delta = r - rotationZ;
	for (GuiItem* child : children) {
		child->increaseRotationZ(delta);
	}
	rotationZ = r;
}