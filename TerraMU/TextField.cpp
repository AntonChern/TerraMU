#include "TextField.h"

TextField::TextField(int length, vec3 position, float rotationX, float rotationY, float rotationZ, vec3 scale) :
	GuiItem(false, position, rotationX, rotationY, rotationZ, scale), length(length) {
	for (int i = 0; i < length; i++) {
		GuiElement* gui = GuiElementFactory::createGuiElement("text_field.png",
			vec3(position.x + scale.x * ((float)(1 + 2 * i) / length - 1) / 2, position.y, position.z),
			rotationX, rotationY, rotationZ, vec3(scale.x / length, scale.y, scale.z));

		vec2 textureTranslate(0.0f);

		if (i == 0) {
			textureTranslate = vec2(0.0f, textureTranslate.y);
		}
		else if (i == length - 1) {
			textureTranslate = vec2(2.0f / 3.0f, textureTranslate.y);
		}
		else {
			textureTranslate = vec2(1.0f / 3.0f, textureTranslate.y);
		}

		gui->setTextureMatrix(
			Maths::createTextureMatrix(textureTranslate, vec2(1.0f / 3.0f, 1.0f)));

		icons.push_back(gui);
	}
}

void TextField::prepareForGettingIcons() {
	int i = 0;
	for (GuiElement* icon : icons) {
		icon->setPosition(position.x + scale.x * ((float)(1 + 2 * i) / length - 1) / 2, position.y, position.z);
		icon->setRotationX(rotationX);
		icon->setRotationY(rotationY);
		icon->setRotationZ(rotationZ);
		icon->setScale(vec3(scale.x / length, scale.y, scale.z));
		i++;
	}
}

//list<GuiElement*> TextField::getIcons() {
//	list<GuiElement*> guis;
//	/*int i = 0;
//	for (GuiElement* icon : icons) {
//		icon->setPosition(position.x + scale.x * ((float)(1 + 2 * i) / length - 1) / 2, position.y, position.z);
//		icon->setRotationX(rotationX);
//		icon->setRotationY(rotationY);
//		icon->setRotationZ(rotationZ);
//		icon->setScale(vec3(scale.x / length, scale.y, scale.z));
//		i++;
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