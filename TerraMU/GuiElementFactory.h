#pragma once
#include "Loader.h"
#include "GuiElement.h"

class GuiElementFactory {
private:
	static Loader* loader;

	static list<GuiElement*> guis;

public:
	static void setLoader(Loader* loader) { GuiElementFactory::loader = loader; };

	static GuiElement* createGuiElement(char const texturePath[], vec3 position, float rotationX, float rotationY, float rotationZ, vec3 scale);
	static GuiElement* createGuiElement(char const texturePath[], vec3 position, float rotationX, float rotationY, float rotationZ, float scale);

	static void cleanUp();
	static void cleanGuis(list<GuiElement*> guis);
};