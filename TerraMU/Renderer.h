#pragma once
#include "TexturedModel.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
using namespace glm;

class Renderer {
private:

public:
	void prepare();
	void render(TexturedModel *texturedModel, mat4 transform);
};