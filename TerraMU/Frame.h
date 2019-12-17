#pragma once
#include <iostream>
#include <list>
#include "GuiElement.h"
#include "GuiItem.h"
#include "Entity.h"
#include "GuiElementFactory.h"
#include "Maths.h"
using namespace std;

class Frame : public GuiItem {
private:
	int columns;
	int rows;

	void prepareForGettingIcons() override;

public:
	Frame(int columns, int rows, vec3 position, float rotationX, float rotationY, float rotationZ, vec3 scale);

	Frame(int columns, int rows, vec3 position, float rotationX, float rotationY, float rotationZ, float scale) :
		Frame(columns, rows, position, rotationX, rotationY, rotationZ, vec3(scale)) {};

};