#pragma once
#include "Camera.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
using namespace glm;

class Maths {
public:
	static mat4 createTransformMatrix(vec3 position, float rotX, float rotY, float rotZ, vec3 scal);
	static mat4 createViewMatrix(Camera *camera);
};