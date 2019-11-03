#include "Converter.h"
#include <iostream>

vec2 Converter::fromOpenGLToMap(vec2 vector) {
	return vec2(map->getColumns() * ((float)vector.x / (float)map->getScale().x + 0.5f),
		map->getRows() * (0.5f - (float)vector.y / (float)map->getScale().y));
}

vec2 Converter::fromMapToOpenGL(vec2 vector) {
	return fromDisplayToOpenGL(fromMapToDisplay(vector));
}

vec2 Converter::fromMapToDisplay(vec2 vector) {
	return vec2((float)(Display::getHeight() * (((float)vector.x / (float)map->getColumns() - 0.5f) * map->getScale().x - camera->getPosition().x) + Display::getWidth()) / (float)2,
		(float)(Display::getHeight()* (camera->getPosition().y + 1 - (0.5f - (float)vector.y / (float)map->getRows()) * map->getScale().y)) / (float)2);
}

vec2 Converter::fromDisplayToMap(vec2 vector) {
	return fromOpenGLToMap(fromDisplayToOpenGL(vector));
}

vec2 Converter::fromOpenGLToDisplay(vec2 vector) {
	return fromMapToDisplay(fromOpenGLToMap(vector));
}

vec2 Converter::fromDisplayToOpenGL(vec2 vector) {
	return vec2(camera->getPosition().x + (float)(2 * vector.x - Display::getWidth()) / (float)Display::getHeight(),
		camera->getPosition().y + 1 - (float)(2 * vector.y) / (float)Display::getHeight());
}