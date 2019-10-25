#pragma once
#include "TexturedModel.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
using namespace glm;

class Entity {
private:
	TexturedModel *model;
	mat3 textureMatrix;

	vec3 position;
	float rotationX;
	float rotationY;
	float rotationZ;
	vec3 scale;

public:
	Entity(TexturedModel *model, vec3 position, float rotationX, float rotationY, float rotationZ, vec3 scale) :
		position(position), rotationX(rotationX), rotationY(rotationY), rotationZ(rotationZ), scale(scale),
		model(model), textureMatrix(mat3(1.0f)) {};

	TexturedModel *getTexturedModel() { return model; };

	void setTextureMatrix(mat3 matrix) { textureMatrix = matrix; };
	mat3 getTextureMatrix() { return textureMatrix; };

	vec3 getPosition() { return position; };
	float getRotationX() { return rotationX; };
	float getRotationY() { return rotationY; };
	float getRotationZ() { return rotationZ; };
	vec3 getScale() { return scale; };

	void setPosition(float x, float y, float z) { position = vec3(x, y, z); };
	void setPosition(vec3 position) { this->position = position; };
	void setScale(vec3 s) { scale = s; };
	void setScale(float s) { scale = vec3(s); };
	void setScale(float xScale, float yScale, float zScale) { scale = vec3(xScale, yScale, zScale); };
	void setRotationX(float r) { rotationX = r; };
	void setRotationY(float r) { rotationY = r; };
	void setRotationZ(float r) { rotationZ = r; };

	void increasePosition(float dx, float dy, float dz) { position += vec3(dx, dy, dz); };
	void increasePosition(vec3 dv) { position += dv; };
	void increaseScale(vec3 ds) { scale += ds; };
	void increaseScale(float ds) { scale += vec3(ds); };
	void increaseScale(float dxScale, float dyScale, float dzScale) { scale += vec3(dxScale, dyScale, dzScale); };
	void increaseRotationX(float dr) { rotationX += dr; };
	void increaseRotationY(float dr) { rotationY += dr; };
	void increaseRotationZ(float dr) { rotationZ += dr; };

};