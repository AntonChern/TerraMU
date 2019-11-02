#pragma once
#include "Moveable.h"
#include "TexturedModel.h"

class Entity : public Moveable {
private:
	TexturedModel* model;
	mat3 textureMatrix;

public:
	Entity(TexturedModel* model, vec3 position, float rotationX, float rotationY, float rotationZ, vec3 scale) :
		Moveable(position, rotationX, rotationY, rotationZ, scale), model(model), textureMatrix(mat3(1.0f)) {};

	TexturedModel* getTexturedModel() { return model; };

	void setTextureMatrix(mat3 matrix) { textureMatrix = matrix; };
	mat3 getTextureMatrix() { return textureMatrix; };

};