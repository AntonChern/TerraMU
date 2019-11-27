#pragma once
#include <iostream>
#include <list>
#include "GuiElement.h"
#include "GuiElementFactory.h"
using namespace std;

class GuiItem : public Moveable {
protected:
	list<GuiItem*> children;
	list<GuiElement*> icons;

	bool isVisible;

	virtual void prepareForGettingIcons() {};

public:
	GuiItem(bool isVisible, vec3 position, float rotationX, float rotationY, float rotationZ, vec3 scale) :
		Moveable(position, rotationX, rotationY, rotationZ, scale), isVisible(isVisible), children({}), icons({}) {};

	GuiItem(bool isVisible, vec3 position, float rotationX, float rotationY, float rotationZ, float scale) :
		GuiItem(isVisible, position, rotationX, rotationY, rotationZ, vec3(scale)) {};

	~GuiItem();

	void changeVisibility();

	void addChild(GuiItem* child) { children.push_back(child); };
	void addChildren(list<GuiItem*> children);

	void removeChild(GuiItem* child) { children.remove(child); };
	void removeChildren(list<GuiItem*> children);

	list<GuiItem*> getChildren() { return children; };

	list<GuiElement*> getIcons();

	virtual void placed(float x, float y);
	virtual void unplaced(float x, float y);

	bool getIsVisible() { return isVisible; };

	virtual void setPosition(vec3 position);
	virtual void setPosition(float x, float y, float z) { setPosition(vec3(x, y, z)); };
	virtual void setScale(vec3 s);
	virtual void setScale(float s) { setScale(vec3(s)); };
	virtual void setScale(float xScale, float yScale, float zScale) { setScale(vec3(xScale, yScale, zScale)); };
	virtual void setRotationX(float r);
	virtual void setRotationY(float r);
	virtual void setRotationZ(float r);

};