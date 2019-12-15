#pragma once
#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
using namespace glm;

class Converter {
public:
	static vec2 fromOpenGLToMap(vec2 vector);
	static vec2 fromMapToOpenGL(vec2 vector);

	static vec2 fromMapToDisplay(vec2 vector);
	static vec2 fromDisplayToMap(vec2 vector);

	static vec2 fromOpenGLToDisplay(vec2 vector);
	static vec2 fromDisplayToOpenGL(vec2 vector);

	static vec2 fromDisplayToGui(vec2 vector);
	static vec2 fromGuiToDisplay(vec2 vector);

	static vec2 fromOpenGLToGui(vec2 vector);
	static vec2 fromGuiToOpenGL(vec2 vector);

	static vec2 fromMapToGui(vec2 vector);
	static vec2 fromGuiToMap(vec2 vector);

};

