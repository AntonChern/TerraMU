#pragma once
#include <iostream>
#include <list>
#include "GuiElement.h"
#include "GuiItem.h"
#include "Entity.h"
#include "GuiElementFactory.h"
using namespace std;
//#include <iostream>
//#include <list>
//#include "GuiElement.h"
//#include "GuiItem.h"
//#include "GuiElementFactory.h"
#include "Maths.h"
//#include <glm/glm.hpp>
//#include <glm/gtc/matrix_transform.hpp>
//#include <glm/gtx/matrix_transform_2d.hpp>
//#include <glm/gtc/type_ptr.hpp>
//using namespace std;
//using namespace glm;

class Frame : public GuiItem {
private:
	list<GuiElement*> icons;

	int columns;
	int rows;

public:
	Frame(int columns, int rows, vec3 position, float rotationX, float rotationY, float rotationZ, vec3 scale);

	Frame(int columns, int rows, vec3 position, float rotationX, float rotationY, float rotationZ, float scale) :
		Frame(columns, rows, position, rotationX, rotationY, rotationZ, vec3(scale)) {};

	list<GuiElement*> getIcons() override;

};