#pragma once
#include "TexturedModel.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
using namespace glm;

class Entity {
private:
	TexturedModel *model;
	vec3 position;
	float rotationX;
	float rotationY;
	float rotationZ;
	float scale;
public:
	Entity(TexturedModel *model, vec3 position, float rotationX, float rotationY, float rotationZ, float scale) : 
		model(model), position(position), scale(scale), rotationX(rotationX), rotationY(rotationY), rotationZ(rotationZ) {};

	TexturedModel *getTexturedModel() { return model; };
	vec3 getPosition() { return position; };
	float getRotationX() { return rotationX; };
	float getRotationY() { return rotationY; };
	float getRotationZ() { return rotationZ; };
	float getScale() { return scale; };

	void setPosition(float x, float y, float z) { position = vec3(x, y, z); };
	void setPosition(vec3 position) { this->position = position; };
	void setScale(float s) { scale = s; };
	void setRotationX(float r) { rotationX = r; };
	void setRotationY(float r) { rotationY = r; };
	void setRotationZ(float r) { rotationZ = r; };

	void increasePosition(float dx, float dy, float dz) { position += vec3(dx, dy, dz); };
	void increasePosition(vec3 dv) { position += dv; };
	void increaseScale(float ds) { scale += ds; };
	void increaseRotationX(float dr) { rotationX += dr; };
	void increaseRotationY(float dr) { rotationY += dr; };
	void increaseRotationZ(float dr) { rotationZ += dr; };
};