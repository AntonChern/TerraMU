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

class GuiItemBuilder {
private:
	static constexpr float aspect = (float)Display::getWidth() / (float)Display::getHeight();

public:
	static GuiItem* buildBars();
	static GuiItem* buildInventory();
	//GuiItem* buildChest();
	//GuiItem* buildPoints();
	//GuiItem* buildBars();

};
