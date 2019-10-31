#pragma once
#include "Moveable.h"
#include "TexturedModel.h"

class Entity : public Moveable {
public:
	Entity(vec3 position, float rotationX, float rotationY, float rotationZ, vec3 scale) :
		Moveable(position, rotationX, rotationY, rotationZ, scale) {};

	virtual TexturedModel *getTexturedModel() = 0;

	virtual void setTextureMatrix(mat3 matrix) = 0;
	virtual mat3 getTextureMatrix() = 0;

};