#pragma once
class Item;
#include "GuiItem.h"

class Slot : public GuiItem {
private:
	GuiElement* icon;
	GuiElement* iconPlaced;
	bool isPlaced;

	Item* item = nullptr;

	void prepareForGettingIcons() override;

public:
	Slot(vec3 position, float rotationX, float rotationY, float rotationZ, vec3 scale);

	Slot(vec3 position, float rotationX, float rotationY, float rotationZ, float scale) :
		Slot(position, rotationX, rotationY, rotationY, vec3(scale)) {};

	void placed(float x, float y) override;
	void unplaced(float x, float y) override;

	bool setItem(Item* item);
	Item* getItem() { return item; };
	bool isEmpty() { return !item; };

};