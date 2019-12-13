#include "Converter.h"
#include "GameController.h"
#include "Display.h"
#include <iostream>

vec2 Converter::fromOpenGLToMap(vec2 vector) {
	return vec2(GameController::getMap()->getColumns() *
		(((float)vector.x - GameController::getMap()->getPosition().x) / (float)GameController::getMap()->getScale().x + 0.5f),
		GameController::getMap()->getRows() *
		(0.5f - ((float)vector.y - GameController::getMap()->getPosition().y) / (float)GameController::getMap()->getScale().y));
}

vec2 Converter::fromMapToOpenGL(vec2 vector) {
	return vec2((float)((float)vector.x / (float)GameController::getMap()->getColumns() - 0.5f) * GameController::getMap()->getScale().x,
		(float)(0.5f - (float)vector.y / (float)GameController::getMap()->getRows()) * GameController::getMap()->getScale().y);
}

vec2 Converter::fromMapToDisplay(vec2 vector) {
	return vec2((float)(Display::getHeight() * (((float)vector.x / (float)GameController::getMap()->getColumns() - 0.5f) * GameController::getMap()->getScale().x - GameController::getCamera()->getPosition().x) + Display::getWidth()) / (float)2,
		(float)(Display::getHeight()* (GameController::getCamera()->getPosition().y + 1 - (0.5f - (float)vector.y / (float)GameController::getMap()->getRows()) * GameController::getMap()->getScale().y)) / (float)2);
}

vec2 Converter::fromDisplayToMap(vec2 vector) {
	return fromOpenGLToMap(fromDisplayToOpenGL(vector));
}

vec2 Converter::fromOpenGLToDisplay(vec2 vector) {
	return fromMapToDisplay(fromOpenGLToMap(vector));
}

vec2 Converter::fromDisplayToOpenGL(vec2 vector) {
	return vec2(GameController::getCamera()->getPosition().x + (float)(2 * vector.x - Display::getWidth()) / (float)Display::getHeight(),
		GameController::getCamera()->getPosition().y + 1 - (float)(2 * vector.y) / (float)Display::getHeight());
}

vec2 Converter::fromDisplayToGui(vec2 vector) {
	return vec2(2 * vector.x / Display::getWidth() - 1, 1 - 2 * vector.y / Display::getHeight());
}

vec2 Converter::fromGuiToDisplay(vec2 vector) {
	return vec2(Display::getWidth() * (vector.x + 1.0f) / 2, Display::getHeight() * (1.0f - vector.y) / 2);
}

vec2 Converter::fromOpenGLToGui(vec2 vector) {
	return fromDisplayToGui(fromOpenGLToDisplay(vector));
}

vec2 Converter::fromGuiToOpenGL(vec2 vector) {
	return fromDisplayToOpenGL(fromGuiToDisplay(vector));
}

vec2 Converter::fromMapToGui(vec2 vector) {
	return fromOpenGLToGui(fromMapToOpenGL(vector));
}

vec2 Converter::fromGuiToMap(vec2 vector) {
	return fromOpenGLToMap(fromGuiToOpenGL(vector));
}