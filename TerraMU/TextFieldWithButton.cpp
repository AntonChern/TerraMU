#include "TextFieldWithButton.h"

TextFieldWithButton::TextFieldWithButton(int length, vec3 position, float rotationX, float rotationY, float rotationZ, vec3 scale) :
	GuiItem(position, rotationX, rotationY, rotationZ, scale), length(length) {
	position.x -= 11.0f * scale.x / (24 * length + 22);
	scale.x *= (float)(24 * length) / (24 * length + 22);
	for (int i = 0; i < length; i++) {
		GuiElement* gui = GuiElementFactory::createGuiElement("text_field_with_button.png",
			vec3(position.x + scale.x * ((float)(1 + 2 * i) / length - 1) / 2, position.y, position.z),
			rotationX, rotationY, rotationZ, vec3(scale.x / length, scale.y, scale.z));

		vec2 textureTranslate(0.0f);

		if (i == 0) {
			textureTranslate = vec2(0.0f, textureTranslate.y);
		}
		else if (i == length - 1) {
			textureTranslate = vec2(48.0f / 94.0f, textureTranslate.y);
		}
		else {
			textureTranslate = vec2(24.0f / 94.0f, textureTranslate.y);
		}

		gui->setTextureMatrix(
			Maths::createTextureMatrix(textureTranslate, vec2(24.0f / 94.0f, 1.0f)));

		icons.push_back(gui);
	}
	position = this->position;
	scale = this->scale;

	GuiElement* ring = GuiElementFactory::createGuiElement("text_field_with_button.png",
		vec3(position.x + scale.x * 6.0f * length / (12 * length + 11), position.y, position.z),
		rotationX, rotationY, rotationZ,
		vec3(scale.x * 22.0f / (22 + 24 * length), scale.y, scale.z));
	ring->setTextureMatrix(Maths::createTextureMatrix(vec2(72.0f / 94.0f, 0.0f), vec2(22.0f / 94.0f, 1.0f)));
	icons.push_back(ring);

	GuiItem* button = new RoundButton(true,
		vec3(position.x + scale.x * (12.0f * length - 1.0f) / (24 * length + 22), position.y, position.z),
		rotationX, rotationY, rotationZ, vec3(14.0f * scale.x / (22 + 24 * length), 14.0f / 24.0f * scale.y, 1.0f));

	addChild(button);
}

void TextFieldWithButton::prepareForGettingIcons() {
	vec3 bufPosition = vec3(position.x - 11.0f * scale.x / (24 * length + 22), position.y, position.z);
	vec3 bufScale = vec3(scale.x * (float)(24 * length) / (24 * length + 22), scale.y, scale.z);
	list<GuiElement*>::iterator it = icons.begin();
	for (int i = 0; i != length; it++, i++) {
		GuiElement* gui = *it;
		gui->setPosition(bufPosition.x + bufScale.x * ((float)(1 + 2 * i) / length - 1) / 2, bufPosition.y, bufPosition.z);
		gui->setRotationX(rotationX);
		gui->setRotationY(rotationY);
		gui->setRotationZ(rotationZ);
		gui->setScale(bufScale.x / length, bufScale.y, bufScale.z);
	}
	GuiElement* ring = *it;
	ring->setPosition(position.x + scale.x * 6.0f * length / (12 * length + 11), position.y, position.z);
	ring->setRotationX(rotationX);
	ring->setRotationY(rotationY);
	ring->setRotationZ(rotationZ);
	ring->setScale(scale.x * 22.0f / (22 + 24 * length), scale.y, scale.z);
}