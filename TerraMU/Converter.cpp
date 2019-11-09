#include "Converter.h"
#include <iostream>

vec2 Converter::fromOpenGLToMap(vec2 vector) {
	return vec2(GameController::getMap()->getColumns() * ((float)vector.x / (float)GameController::getMap()->getScale().x + 0.5f),
		GameController::getMap()->getRows() * (0.5f - (float)vector.y / (float)GameController::getMap()->getScale().y));
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