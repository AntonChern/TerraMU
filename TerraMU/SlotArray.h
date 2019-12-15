#pragma once
#include <list>
#include "GuiItem.h"

class SlotArray : public GuiItem {
private:
	int columns;
	int rows;

	void prepareForGettingIcons() override;

public:
	SlotArray(int columns, int rows, vec3 position, float rotationX, float rotationY, float rotationZ, vec3 scale);

	SlotArray(int columns, int rows, vec3 position, float rotationX, float rotationY, float rotationZ, float scale) :
		SlotArray(columns, rows, position, rotationX, rotationY, rotationZ, vec3(scale)) {};

	//list<GuiElement*> getIcons() override;

};