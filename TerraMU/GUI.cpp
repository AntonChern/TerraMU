#include "Gui.h"

Gui::Gui(GLFWwindow* window) {
	/*float aspect = (float)Display::getWidth() / (float)Display::getHeight();
	bars = GuiElementFactory::createGuiElement("bars.png", vec3(0.0f, aspect * 70.0f / 611.0f - 1.0f, 0.0f), 0.0f, 0.0f, 0.0f,
		vec3(2.0f, 2.0f * aspect * 70.0f / 611.0f, 1.0f));*/

	//cursor = GuiElementFactory::createGuiElement("Player.png", vec3(0.0f), 0.0f, 0.0f, 0.0f, vec3(0.01f/*0.4f*/ / Camera::getWidth() * 2, 0.01f/*0.4f*/, 1.0f));
	cursor = new Cursor(window, "cursor.png");

	inventory = GuiItemBuilder::buildInventory();
	bars = GuiItemBuilder::buildBars();
	bars->changeVisibility();
}

Gui::~Gui() {
	delete cursor;
	delete bars;
	delete inventory;
	//delete chest;
	//delete points;
}

list<GuiElement*> Gui::getGuiElements() {
	list<GuiElement*> guis;

	if (bars->getIsVisible()) {
		for (GuiElement* gui : bars->getIcons()) {
			guis.push_back(gui);
		}
	}

	if (inventory->getIsVisible()) {
		for (GuiElement* gui : inventory->getIcons()) {
			guis.push_back(gui);
		}
	}

	return guis;
}

//void Gui::reset() {
//	visibleGuis.clear();
//	visibleGuis.push_front(bars);
//}
//
//void Gui::changeVisibility(list<GuiElement*> guis) {
//	inventory->changeVisibility();
//}
//
//void Gui::changeInventoryVisibility() {
//	inventory->changeVisibility();
//}
//
//void Gui::changeChestVisibility() {
//	//add inventory
//	chest->changeVisibility();
//}
//
//void Gui::changePointsVisibility() {
//	points->changeVisibility();
//}