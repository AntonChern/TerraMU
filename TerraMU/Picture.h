#pragma once
#include "GuiElement.h"
#include "GuiItem.h"
#include "GuiElementFactory.h"

class Picture : public GuiItem {
private:
	GuiElement* icon;

	void prepareForGettingIcons() override;

public:
	Picture(const char filePath[], vec3 position, float rotationX, float rotationY, float rotationZ, vec3 scale);

	Picture(const char filePath[], vec3 position, float rotationX, float rotationY, float rotationZ, float scale) :
		Picture(filePath, position, rotationX, rotationY, rotationY, vec3(scale)) {};

	//list<GuiElement*> getIcons() override;

};