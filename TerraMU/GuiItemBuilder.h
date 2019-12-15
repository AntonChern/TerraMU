#pragma once
#define GLM_FORCE_RADIANS
#include "Camera.h"
class GuiItem;

class GuiItemBuilder {
private:
	static constexpr float aspect = Camera::getWidth() / Camera::getHeight()/*(float)Display::getWidth() / (float)Display::getHeight()*/;

public:
	static GuiItem* buildBars();
	static GuiItem* buildInventory();
	//static GuiItem* buildChest();
	static GuiItem* buildPoints();
	//static GuiItem* buildBars();

};
