#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/matrix_transform_2d.hpp>
#include "GameController.h"
#include "Display.h"
using namespace glm;

class Converter
{
private:
	static Map* map;
	static Camera* camera;
public:
	static void setMap(Map* map) { Converter::map = map; };
	static void setCamera(Camera* camera) { Converter::camera = camera; };

	static vec2 fromOpenGLToMap(vec2 vector);
	static vec2 fromMapToOpenGL(vec2 vector);

	static vec2 fromMapToDisplay(vec2 vector);
	static vec2 fromDisplayToMap(vec2 vector);

	static vec2 fromOpenGLToDisplay(vec2 vector);
	static vec2 fromDisplayToOpenGL(vec2 vector);
};

