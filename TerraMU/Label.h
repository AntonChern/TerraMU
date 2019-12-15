#pragma once
#include <iostream>
#include <list>
#include "GuiItem.h"
#include <string>
#include <glm/glm.hpp>
using namespace glm;

class Label : public GuiItem {
protected:
	string text;

	virtual void prepareForGettingIcons();

public:
	Label(string text, vec3 position, float rotationX, float rotationY, float rotationZ, float scaleY);

	void setText(string text) { setText(text.c_str()); };
	virtual void setText(char const text[]) { this->text = text; };
	string getText() { return text; };

	//list<GuiElement*> getIcons() override;
};