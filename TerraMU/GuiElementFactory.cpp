#include "GuiElementFactory.h"
#include "Loader.h"
#include "GuiElement.h"

GuiElement* GuiElementFactory::createGuiElement(char const texturePath[],
	vec3 position, float rotationX, float rotationY, float rotationZ, vec3 scale) {
	GuiElement* gui = new GuiElement(loader->loadTexture(texturePath), position, rotationX, rotationY, rotationZ, scale);
	guis.push_back(gui);
	return gui;
}

GuiElement* GuiElementFactory::createGuiElement(char const texturePath[],
	vec3 position, float rotationX, float rotationY, float rotationZ, float scale) {
	return createGuiElement(texturePath, position, rotationX, rotationY, rotationZ, vec3(scale));
}

void GuiElementFactory::cleanUp() {
	for (GuiElement* gui : guis) {
		delete gui;
	}
	guis.clear();
}

void GuiElementFactory::cleanGuis(list<GuiElement*> guis) {
	for (GuiElement* gui : guis) {
		int initSize = GuiElementFactory::guis.size();
		GuiElementFactory::guis.remove(gui);
		if (initSize != GuiElementFactory::guis.size()) {
			delete gui;
		}
	}
}