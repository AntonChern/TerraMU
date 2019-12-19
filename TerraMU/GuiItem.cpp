#include "GuiItem.h"
#include "GuiElementFactory.h"

GuiItem::~GuiItem() {
	while (!children.empty()) {
		GuiItem* gui = children.front();
		children.pop_front();
		delete gui;
	}
	list<GuiElement*> buff = {};
	while (!icons.empty()) {
		GuiElement* icon = icons.front();
		children.pop_front();
		buff.push_back(icon);
	}
	GuiElementFactory::cleanGuis(buff);
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
	list<GuiElement*> resIcons;

	prepareForGettingIcons();

	for (GuiElement* icon : this->icons) {
		resIcons.push_back(icon);
	}

	for (GuiItem* child : children) {
		for (GuiElement* gui : child->getIcons()) {
			resIcons.push_back(gui);
		}
	}

	return resIcons;
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

bool GuiItem::clicked(float x, float y) {
	for (GuiItem* child : getChildren()) {
		if (abs(x - child->getPosition().x) < child->getScale().x / 2 && abs(y - child->getPosition().y) < child->getScale().y / 2) {
			if (child->clicked(x, y)) {
				return true;
			}
		}
	}
	if (abs(x - this->getPosition().x) < this->getScale().x / 2 && abs(y - this->getPosition().y) < this->getScale().y / 2) {
		return true;
	}
	return false;
}

void GuiItem::unclicked(float x, float y) {
	for (GuiItem* child : getChildren()) {
		if (abs(x - child->getPosition().x) < child->getScale().x / 2 && abs(y - child->getPosition().y) < child->getScale().y / 2) {
			child->unclicked(x, y);
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