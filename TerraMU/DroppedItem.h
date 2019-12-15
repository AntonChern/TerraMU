#pragma once
#define GLM_FORCE_RADIANS
class Entity;
class FramedLabel;
#include "Moveable.h"
#include <string>
using namespace std;

class DroppedItem : public Moveable {
private:
	Entity* model;
	FramedLabel* title;
	static constexpr float scaleCoeff = 0.17f;

public:
	DroppedItem(string texturePath, string title, vec3 position, float rotationX, float rotationY, float rotationZ, vec3 scale);
	DroppedItem(string texturePath, string title, vec3 position, float rotationX, float rotationY, float rotationZ, float scale) :
		DroppedItem(texturePath, title, position, rotationX, rotationY, rotationZ, vec3(scale)) {};
	~DroppedItem();

	Entity* getEntity() { return model; };
	FramedLabel* getTitle() { return title; };

	void update();

	void setPosition(vec3 position);
	void setPosition(float x, float y, float z) { setPosition(vec3(x, y, z)); };
	void setScale(vec3 s);
	void setScale(float s) { setScale(vec3(s)); };
	void setScale(float xScale, float yScale, float zScale) { setScale(vec3(xScale, yScale, zScale)); };
	void setRotationX(float r);
	void setRotationY(float r);
	void setRotationZ(float r);

};