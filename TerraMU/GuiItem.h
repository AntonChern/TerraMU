#pragma once
#include <iostream>
#include <list>
#include "GuiElement.h"
using namespace std;

class GuiItem : public Moveable {
protected:
	list<GuiItem*> children;

	bool isVisible;

public:
	GuiItem(bool isVisible, vec3 position, float rotationX, float rotationY, float rotationZ, vec3 scale) :
		Moveable(position, rotationX, rotationY, rotationZ, scale), isVisible(isVisible), children({}) {};

	GuiItem(bool isVisible, vec3 position, float rotationX, float rotationY, float rotationZ, float scale) :
		GuiItem(isVisible, position, rotationX, rotationY, rotationZ, vec3(scale)) {};

	void changeVisibility();

	void addChild(GuiItem* child) { children.push_back(child); };
	void addChildren(list<GuiItem*> children);

	void removeChild(GuiItem* child) { children.remove(child); };
	void removeChildren(list<GuiItem*> children);

	list<GuiItem*> getChildren() { return children; };

	virtual list<GuiElement*> getIcons();

	virtual void placed(float x, float y);
	virtual void unplaced(float x, float y);

	bool getIsVisible() { return isVisible; };

};