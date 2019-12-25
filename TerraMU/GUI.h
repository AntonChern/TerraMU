#pragma once
#define GLM_FORCE_RADIANS
#include <iostream>
#include <list>
class Cursor;
class GuiItem;
class GuiElement;
struct GLFWwindow;
class Item;
using namespace std;

class Gui {
private:
	GuiItem* bars;
	GuiItem* inventory;
	GuiItem* chest;
	GuiItem* points;

	list<GuiItem*> visiblePanels;

	Cursor* cursor;

	Item* grabbedItem = nullptr;

public:
	Gui(GLFWwindow* window);
	~Gui();

	void setGrabbedItem(Item* grabbed) { grabbedItem = grabbed; };
	Item* getGrabbedItem() { return grabbedItem; };

	list<GuiElement*> getGuiElements();
	list<GuiItem*>* getVisiblePanels() { return &visiblePanels; };

	GuiItem* getInventory() { return inventory; };
	//GuiItem* getChest() { return chest; };
	GuiItem* getPoints() { return points; };
	GuiItem* getBars() { return bars; };

	Cursor* getCursor() { return cursor; };

	void placed(float x, float y);
	void unplaced(float x, float y);

	bool clicked(float x, float y);
	void unclicked(float x, float y);

};