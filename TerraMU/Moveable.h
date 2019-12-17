#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
using namespace glm;

class Moveable {
protected:
	vec3 position;
	float rotationX;
	float rotationY;
	float rotationZ;
	vec3 scale;

public:
	Moveable(vec3 position, float rotationX, float rotationY, float rotationZ, vec3 scale) :
		position(position), rotationX(rotationX), rotationY(rotationY), rotationZ(rotationZ), scale(scale) {};

	Moveable(vec3 position, float rotationX, float rotationY, float rotationZ, float scale) :
		position(position), rotationX(rotationX), rotationY(rotationY), rotationZ(rotationZ), scale(vec3(scale)) {};

	virtual vec3 getPosition() { return position; };
	virtual float getRotationX() { return rotationX; };
	virtual float getRotationY() { return rotationY; };
	virtual float getRotationZ() { return rotationZ; };
	virtual vec3 getScale() { return scale; };

	virtual void setPosition(float x, float y, float z) { setPosition(vec3(x, y, z)); };
	virtual void setPosition(vec3 position) { this->position = position; };
	virtual void setScale(vec3 s) { scale = s; };
	virtual void setScale(float s) { setScale(vec3(s)); };
	virtual void setScale(float xScale, float yScale, float zScale) { setScale(vec3(xScale, yScale, zScale)); };
	virtual void setRotationX(float r) { rotationX = r; };
	virtual void setRotationY(float r) { rotationY = r; };
	virtual void setRotationZ(float r) { rotationZ = r; };

	virtual void increasePosition(float dx, float dy, float dz) { setPosition(getPosition() + vec3(dx, dy, dz)); };
	virtual void increasePosition(vec3 dv) { setPosition(getPosition() + dv); };
	virtual void increaseScale(vec3 ds) { setScale(getScale() + ds); };
	virtual void increaseScale(float ds) { setScale(getScale() + vec3(ds)); };
	virtual void increaseScale(float dxScale, float dyScale, float dzScale) { setScale(getScale() + vec3(dxScale, dyScale, dzScale)); };
	virtual void increaseRotationX(float dr) { setRotationX(getRotationX() + dr); };
	virtual void increaseRotationY(float dr) { setRotationY(getRotationY() + dr); };
	virtual void increaseRotationZ(float dr) { setRotationZ(getRotationZ() + dr); };

};