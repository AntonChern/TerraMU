#pragma once
#include <iostream>
#include <list>
#include "Moveable.h"
#include "GuiElement.h"
#include "GuiElementFactory.h"
#include "GuiItem.h"
#include "Display.h"
#include "GuiItemBuilder.h"
using namespace std;

class Gui : public Moveable {
private:
	GuiItem* bars;
	GuiItem* inventory;
	//GuiItem* chest;
	GuiItem* points;

	GuiElement* cursor;

	//void changeVisibility(list<GuiElement*> guis);

public:
	Gui();

	list<GuiElement*> getGuiElements();

	/*void changeInventoryVisibility();
	void changeChestVisibility();
	void changePointsVisibility();
	void reset();*/

	GuiItem* getInventory() { return inventory; };
	//GuiItem* getChest() { return chest; };
	GuiItem* getPoints() { return points; };
	GuiItem* getBars() { return bars; };

	GuiElement* getCursor() { return cursor; };

	void interact(float x, float y);

};