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
	mat3 textureMatrix;

public:
	TexturedModel(RawModel *model, ModelTexture *texture) : rawModel(model), texture(texture), textureMatrix(mat3(1.0f)) {};
	RawModel *getRawModel() { return rawModel; };
	ModelTexture *getTexture() { return texture; };

	void setTextureMatrix(mat3 matrix) { textureMatrix = matrix; };
	mat3 getTextureMatrix() { return textureMatrix; };

};

