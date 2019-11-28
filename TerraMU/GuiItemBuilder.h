#pragma once
#include "GuiElementFactory.h"
#include "GuiItem.h"
#include "Display.h"
#include "Camera.h"
#include "Frame.h"
#include "SlotArray.h"
#include "Slot.h"
#include "TextField.h"
#include "Label.h"
#include "Picture.h"
#include "TextFieldWithButton.h"

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
