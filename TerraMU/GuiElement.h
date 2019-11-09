#pragma once
#include "Moveable.h"

class GuiElement : public Moveable {
private:
	int textureID;
	mat3 texture;

public:
	GuiElement(int textureID, vec3 position, float rotationX, float rotationY, float rotationZ, vec3 scale) :
		Moveable(position, rotationX, rotationY, rotationZ, scale), textureID(textureID), texture(mat3(1.0f)) {};
	GuiElement(int textureID, vec3 position, float rotationX, float rotationY, float rotationZ, float scale) :
		Moveable(position, rotationX, rotationY, rotationZ, scale), textureID(textureID), texture(mat3(1.0f)) {};

	int getTextureID() { return textureID; };

	mat3 getTextureMatrix() { return texture; };
	void setTextureMatrix(mat3 matrix) { texture = matrix; };

};