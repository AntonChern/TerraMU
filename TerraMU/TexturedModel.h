#pragma once
#include "RawModel.h"
#include "ModelTexture.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
using namespace glm;

class TexturedModel {
private:
	RawModel *rawModel;
	ModelTexture *texture;

public:
	TexturedModel(RawModel *model, ModelTexture *texture) : rawModel(model), texture(texture) {};
	RawModel *getRawModel() { return rawModel; };
	ModelTexture *getTexture() { return texture; };

};

