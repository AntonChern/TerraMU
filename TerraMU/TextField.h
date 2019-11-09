#pragma once
#include <iostream>
#include <list>
#include "GuiElement.h"
#include "GuiItem.h"
#include "GuiElementFactory.h"
#include "Maths.h"
using namespace std;

class TextField : public GuiItem {
private:
	list<GuiElement*> icons;

	int length;

public:
	TextField(int length, vec3 position, float rotationX, float rotationY, float rotationZ, vec3 scale);

	TextField(int length, vec3 position, float rotationX, float rotationY, float rotationZ, float scale) :
		TextField(length, position, rotationX, rotationY, rotationZ, vec3(scale)) {};

	list<GuiElement*> getIcons() override;
};