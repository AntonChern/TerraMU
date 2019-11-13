#pragma once
#include <iostream>
#include <list>
#include "Moveable.h"
#include "GuiElement.h"
#include "GuiElementFactory.h"
#include "GuiItem.h"
#include "Display.h"
#include "GuiItemBuilder.h"
#include "Cursor.h"
using namespace std;

class Gui {
private:
	GuiItem* bars;
	GuiItem* inventory;
	GuiItem* chest;
	GuiItem* points;

	Cursor* cursor;

	//void changeVisibility(list<GuiElement*> guis);

public:
	Gui(GLFWwindow* window);
	~Gui();

	list<GuiElement*> getGuiElements();

	/*void changeInventoryVisibility();
	void changeChestVisibility();
	void changePointsVisibility();
	void reset();*/

	GuiItem* getInventory() { return inventory; };
	//GuiItem* getChest() { return chest; };
	GuiItem* getPoints() { return points; };
	GuiItem* getBars() { return bars; };

	Cursor* getCursor() { return cursor; };

	void interact(float x, float y);

};