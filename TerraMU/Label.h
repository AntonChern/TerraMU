#pragma once
#include <iostream>
#include <list>
#include "GuiElement.h"
#include "GuiItem.h"
#include "GuiElementFactory.h"
#include "Display.h"
#include "Maths.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/matrix_transform_2d.hpp>
#include <glm/gtc/type_ptr.hpp>
using namespace glm;
using namespace std;

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