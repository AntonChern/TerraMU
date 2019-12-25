#pragma once
class Item;
#include "GrabAction.h"
#include "GuiItem.h"

class Slot : public GuiItem {
private:
	GuiElement* icon;
	GuiElement* iconPlaced;
	bool isPlaced;

	Item* item = nullptr;
	GrabAction* grab = new GrabAction(item);

	void prepareForGettingIcons() override;

public:
	Slot(vec3 position, float rotationX, float rotationY, float rotationZ, vec3 scale);

	Slot(vec3 position, float rotationX, float rotationY, float rotationZ, float scale) :
		Slot(position, rotationX, rotationY, rotationY, vec3(scale)) {};

	~Slot() { delete grab; };

	void placed(float x, float y) override;
	void unplaced(float x, float y) override;

	bool clicked(float x, float y);

	bool setItem(Item* item);
	Item* getItem() { return item; };
	bool isEmpty() { return !item; };

};