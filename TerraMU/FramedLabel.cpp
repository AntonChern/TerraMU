#include "FramedLabel.h"
#include "GuiElement.h"
#include "GuiElementFactory.h"
#include "Display.h"
#include "Maths.h"

FramedLabel::FramedLabel(string text, vec3 position, float rotationX, float rotationY, float rotationZ, float scaleY) : 
	Label(text, position, rotationX, rotationY, rotationZ, scaleY) {

	int rows = 3;
	int columns = 3 * 28 * text.length() / 32;

	vec3 bufScale = scale + vec3(scale.x / text.length(), 2.0f * scale.y / rows, 0.0f);

	for (int i = 0; i < columns; i++) {
		for (int j = 0; j < rows; j++) {
			GuiElement* icon = GuiElementFactory::createGuiElement("label_frame.png", vec3(position.x + bufScale.x * ((float)(0.5f + i) / columns - 0.5f),
				position.y + bufScale.y * ((float)(0.5f + j) / rows - 0.5f), position.z), rotationX, rotationY, rotationZ,
				vec3(bufScale.x / columns, bufScale.y / rows, bufScale.z));

			vec2 textureTranslate(0.0f);

			if (i == 0) {
				if (j == 0) {
					textureTranslate = vec2(0.0f, 2.0f / 3.0f);
				}
				else if (j == rows - 1) {

				}
				else {
					textureTranslate = vec2(0.0f, 1.0f / 3.0f);
				}
			}
			else if (i == columns - 1) {
				if (j == 0) {
					textureTranslate = vec2(2.0f / 3.0f, 2.0f / 3.0f);
				}
				else if (j == rows - 1) {
					textureTranslate = vec2(2.0f / 3.0f, 0.0f);
				}
				else {
					textureTranslate = vec2(2.0f / 3.0f, 1.0f / 3.0f);
				}
			}
			else {
				if (j == 0) {
					textureTranslate = vec2(1.0f / 3.0f, 2.0f / 3.0f);
				}
				else if (j == rows - 1) {
					textureTranslate = vec2(1.0f / 3.0f, 0.0f);
				}
				else {
					textureTranslate = vec2(1.0f / 3.0f, 1.0f / 3.0f);
				}
			}

			icon->setTextureMatrix(Maths::createTextureMatrix(textureTranslate, vec2(1.0f / 3.0f)));

			icons.push_front(icon);
		}
	}
}

void FramedLabel::prepareForGettingIcons() {
	int length = text.length();
	std::list<GuiElement*>::iterator it = icons.begin();

	int rows = 3;
	int columns = 3 * 28 * length / 32;

	vec3 bufScale = scale + vec3(scale.x / text.length(), 2.0f * scale.y / rows, 0.0f);

	for (int i = columns - 1; i >= 0; i--) {
		for (int j = rows - 1; j >= 0; j--, it++) {
			GuiElement* icon = *it;
			icon->setPosition(vec3(position.x + bufScale.x * ((float)(0.5f + i) / columns - 0.5f),
				position.y + bufScale.y * ((float)(0.5f + j) / rows - 0.5f), position.z));
			icon->setScale(vec3(bufScale.x / columns, bufScale.y / rows, bufScale.z));
			icon->setRotationX(rotationX);
			icon->setRotationY(rotationY);
			icon->setRotationZ(rotationZ);
		}
	}

	for (int i = 0; it != icons.end(); it++, i++) {
		GuiElement* icon = *it;
		icon->setPosition(position.x + scale.x * ((float)(1 + 2 * i) / length - 1) / 2, position.y, position.z);
		icon->setRotationX(rotationX);
		icon->setRotationY(rotationY);
		icon->setRotationZ(rotationZ);
		icon->setScale(vec3(scale.x / length, scale.y, scale.z));
	}
}