#pragma once
#include "GuiItem.h"
#include "GuiElementFactory.h"
#include "Maths.h"

class RoundButton : public GuiItem {
private:
	GuiElement* icon;
	bool isEnable;

	void prepareForGettingIcons() override;

public:
	RoundButton(bool isEnable, vec3 position, float rotationX, float rotationY, float rotationZ, vec3 scale);

	RoundButton(bool isEnable, vec3 position, float rotationX, float rotationY, float rotationZ, float scale) :
		RoundButton(isEnable, position, rotationX, rotationY, rotationY, vec3(scale)) {};

	void placed(float x, float y) override;
	void unplaced(float x, float y) override;

	bool clicked(float x, float y) override;
	void unclicked(float x, float y) override;

};