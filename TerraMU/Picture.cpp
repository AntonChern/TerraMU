#include "Picture.h"

Picture::Picture(const char filePath[], vec3 position, float rotationX, float rotationY, float rotationZ, vec3 scale) :
	GuiItem(false, position, rotationX, rotationY, rotationZ, scale) {
	icon = GuiElementFactory::createGuiElement(filePath, position, rotationX, rotationY, rotationZ, scale);
	icons.push_back(icon);
}

//void Picture::prepareForGettingIcons() {
//	icon->setPosition(position);
//	icon->setRotationX(rotationX);
//	icon->setRotationY(rotationY);
//	icon->setRotationZ(rotationZ);
//	icon->setScale(scale);
//}

//list<GuiElement*> Picture::getIcons() {
//	list<GuiElement*> icons;
//	/*icon->setPosition(position);
//	icon->setRotationX(rotationX);
//	icon->setRotationY(rotationY);
//	icon->setRotationZ(rotationZ);
//	icon->setScale(scale);*/
//
//	for (GuiElement* icon : GuiItem::getIcons()) {
//		icons.push_back(icon);
//	}
//
//	icons.push_back(icon);
//
//	return icons;
//}