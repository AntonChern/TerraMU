#pragma once
#define GLM_FORCE_RADIANS
#include <iostream>
#include <list>
class GuiElement;
class GuiShader;
class RawModel;
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