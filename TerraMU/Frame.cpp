#include "Frame.h"

Frame::Frame(int columns, int rows, vec3 position, float rotationX, float rotationY, float rotationZ, vec3 scale) :
	GuiItem(false, position, rotationX, rotationY, rotationZ, scale), columns(columns), rows(rows) {
	for (int j = 0; j < rows; j++) {
		for (int i = 0; i < columns; i++) {
			vec3 currPosition = vec3(position.x + scale.x * ((float)(2 * i + 1) / columns - 1) / 2,
				position.y + scale.y * (1 - (float)(2 * j + 1) / rows) / 2, position.z);
			vec3 currScale = vec3(scale.x / columns, scale.y / rows, scale.z);
			vec2 textureTranslate(0.0f);
			if (i == 0) {
				if (j == 0) {

				}
				else if (j == rows - 1) {
					textureTranslate = vec2(0.0f, 2.0f / 3.0f);
				}
				else {
					textureTranslate = vec2(0.0f, 1.0f / 3.0f);
				}
			}
			else if (i == columns - 1) {
				if (j == 0) {
					textureTranslate = vec2(2.0f / 3.0f, 0.0f);
				}
				else if (j == rows - 1) {
					textureTranslate = vec2(2.0f / 3.0f, 2.0f / 3.0f);
				}
				else {
					textureTranslate = vec2(2.0f / 3.0f, 1.0f / 3.0f);
				}
			}
			else {
				if (j == 0) {
					textureTranslate = vec2(1.0f / 3.0f, 0.0f);
				}
				else if (j == rows - 1) {
					textureTranslate = vec2(1.0f / 3.0f, 2.0f / 3.0f);
				}
				else {
					textureTranslate = vec2(1.0f / 3.0f, 1.0f / 3.0f);
				}
			}

			GuiElement* gui = GuiElementFactory::createGuiElement("frame.png",
				currPosition, rotationX, rotationY, rotationZ, currScale);
			gui->setTextureMatrix(Maths::createTextureMatrix(textureTranslate, vec2(1.0f / 3.0f)));

			icons.push_back(gui);
		}
	}
}

//void Frame::prepareForGettingIcons() {
//	int i = 0;
//	int j = 0;
//	for (GuiElement* icon : icons) {
//		icon->setPosition(position.x + scale.x * ((float)(2 * i + 1) / columns - 1) / 2,
//			position.y + scale.y * (1 - (float)(2 * j + 1) / rows) / 2, position.z);
//		icon->setRotationX(rotationX);
//		icon->setRotationY(rotationY);
//		icon->setRotationZ(rotationZ);
//		icon->setScale(vec3(scale.x / columns, scale.y / rows, scale.z));
//		i++;
//		if (i == columns) {
//			i = 0;
//			j++;
//		}
//	}
//}

//list<GuiElement*> Frame::getIcons() {
//	list<GuiElement*> guis;
//	/*int i = 0;
//	int j = 0;
//	for (GuiElement* icon : icons) {
//		icon->setPosition(position.x + scale.x * ((float)(2 * i + 1) / columns - 1) / 2,
//			position.y + scale.y * (1 - (float)(2 * j + 1) / rows) / 2, position.z);
//		icon->setRotationX(rotationX);
//		icon->setRotationY(rotationY);
//		icon->setRotationZ(rotationZ);
//		icon->setScale(vec3(scale.x / columns, scale.y / rows, scale.z));
//		i++;
//		if (i == columns) {
//			i = 0;
//			j++;
//		}
//	}*/
//
//	for (GuiElement* icon : icons) {
//		guis.push_back(icon);
//	}
//
//	for (GuiElement* icon : GuiItem::getIcons()) {
//		guis.push_back(icon);
//	}
//
//	return guis;
//}