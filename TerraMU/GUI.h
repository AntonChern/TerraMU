#pragma once
#define GLM_FORCE_RADIANS
#include <iostream>
#include <list>
class Cursor;
class GuiItem;
class GuiElement;
struct GLFWwindow;
using namespace std;

class Gui {
private:
	GuiItem* bars;
	GuiItem* inventory;
	GuiItem* chest;
	GuiItem* points;

	list<GuiItem*> visiblePanels;

	Cursor* cursor;

	//void changeVisibility(list<GuiElement*> guis);

public:
	Gui(GLFWwindow* window);
	~Gui();

	list<GuiElement*> getGuiElements();
	list<GuiItem*>* getVisiblePanels() { return &visiblePanels; };

	/*void changeInventoryVisibility();
	void changeChestVisibility();
	void changePointsVisibility();
	void reset();*/

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