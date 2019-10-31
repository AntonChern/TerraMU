#pragma once
#include "Entity.h"
#include "TexturedModel.h"

class EntityInstance : public Entity {
private:
	TexturedModel* model;
	mat3 textureMatrix;

public:
	EntityInstance(TexturedModel* model, vec3 position, float rotationX, float rotationY, float rotationZ, vec3 scale) :
		Entity(position, rotationX, rotationY, rotationZ, scale), model(model), textureMatrix(mat3(1.0f)) {};

	TexturedModel* getTexturedModel() { return model; };

	void setTextureMatrix(mat3 matrix) { textureMatrix = matrix; };
	mat3 getTextureMatrix() { return textureMatrix; };

};