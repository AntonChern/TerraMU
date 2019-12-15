#pragma once
#include "GuiItem.h"

class TextFieldWithButton : public GuiItem {
private:
	int length;

	void prepareForGettingIcons() override;

public:
	TextFieldWithButton(int length, vec3 position, float rotationX, float rotationY, float rotationZ, vec3 scale);

	TextFieldWithButton(int length, vec3 position, float rotationX, float rotationY, float rotationZ, float scale) :
		TextFieldWithButton(length, position, rotationX, rotationY, rotationZ, vec3(scale)) {};

};