#pragma once
#include <iostream>
#include <list>
#include "GuiItem.h"

class TextField : public GuiItem {
private:
	int length;

	void prepareForGettingIcons() override;

public:
	TextField(int length, vec3 position, float rotationX, float rotationY, float rotationZ, vec3 scale);

	TextField(int length, vec3 position, float rotationX, float rotationY, float rotationZ, float scale) :
		TextField(length, position, rotationX, rotationY, rotationZ, vec3(scale)) {};

	//list<GuiElement*> getIcons() override;
};