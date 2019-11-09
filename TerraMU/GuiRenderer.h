#pragma once
#include <iostream>
#include <list>
#include "Loader.h"
#include "GuiShader.h"
#include "GuiElement.h"
#include "RawModel.h"
#include "EntityFactory.h"
#include "Maths.h"
using namespace std;

class GuiRenderer {
private:
	GuiShader* shader;
	RawModel* quad;

public:
	GuiRenderer();
	~GuiRenderer();

	void cleanUp();
	void render(list<GuiElement*> guis);
};