#include "Label.h"

Label::Label(string text, vec3 position, float rotationX, float rotationY, float rotationZ, float scaleY) :
	GuiItem(false, position, rotationX, rotationY, rotationZ,
		vec3(scaleY* 28.0f / 32.0f * text.length() / (float)Display::getWidth() * (float)Display::getHeight(), scaleY, 1.0f)),
	text(text) {
	int length = text.length();
	for (int i = 0; i < length; i++) {
		char symbol = text.at(i);
		symbol -= ' ';
		GuiElement* gui = GuiElementFactory::createGuiElement("font.png",
			vec3(position.x + scale.x * ((float)(1 + 2 * i) / length - 1) / 2, position.y, position.z),
			rotationX, rotationY, rotationZ, vec3(scale.x / length, scale.y, scale.z));

		gui->setTextureMatrix(
			Maths::createTextureMatrix(vec2((float)(symbol % 16) / 16.0f, (float)(symbol / 16) / 6.0f), vec2(1.0f / 16.0f, 1.0f / 6.0f)));
		icons.push_back(gui);
	}
}

void Label::prepareForGettingIcons() {
	int length = text.length();
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

//list<GuiElement*> Label::getIcons() {
//	list<GuiElement*> guis;
//	/*int length = text.length();
//	int i = 0;
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