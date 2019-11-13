#pragma once
#include <iostream>
#include <list>
#include "GuiElement.h"
#include "GuiItem.h"
#include "Entity.h"
#include "GuiElementFactory.h"
#include "Slot.h"
using namespace std;

class SlotArray : public GuiItem {
private:
	int columns;
	int rows;

public:
	SlotArray(int columns, int rows, vec3 position, float rotationX, float rotationY, float rotationZ, vec3 scale);

	SlotArray(int columns, int rows, vec3 position, float rotationX, float rotationY, float rotationZ, float scale) :
		SlotArray(columns, rows, position, rotationX, rotationY, rotationZ, vec3(scale)) {};

	//list<GuiElement*> getIcons() override;
	//void prepareForGettingIcons() override;

};