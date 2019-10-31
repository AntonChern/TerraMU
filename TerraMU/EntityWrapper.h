#pragma once
#include "Entity.h"
#include "EntityInstance.h"

class EntityWrapper : public Entity {
private:
	Entity* instance;

public:
	EntityWrapper(Entity* instance, vec3 position, float rotationX, float rotationY, float rotationZ, vec3 scale) :
		Entity(position, rotationX, rotationY, rotationZ, scale), instance(instance) {};

	TexturedModel* getTexturedModel() { return instance->getTexturedModel(); };

	void setTextureMatrix(mat3 matrix) { instance->setTextureMatrix(matrix); };
	mat3 getTextureMatrix() { return instance->getTextureMatrix(); };

	/*vec3 getPosition() { return instance->getPosition(); };
	float getRotationX() { return instance->getRotationX(); };
	float getRotationY() { return instance->getRotationY(); };
	float getRotationZ() { return instance->getRotationZ(); };
	vec3 getScale() { return instance->getScale(); };

	void setPosition(float x, float y, float z) { instance->setPosition(x, y, z); };
	void setPosition(vec3 position) { instance->setPosition(position); };
	void setScale(vec3 s) { instance->setScale(s); };
	void setScale(float s) { instance->setScale(s); };
	void setScale(float xScale, float yScale, float zScale) { instance->setScale(xScale, yScale, zScale); };
	void setRotationX(float r) { instance->setRotationX(r); };
	void setRotationY(float r) { instance->setRotationY(r); };
	void setRotationZ(float r) { instance->setRotationZ(r); };

	void increasePosition(float dx, float dy, float dz) { instance->increasePosition(dx, dy, dz); };
	void increasePosition(vec3 dv) { instance->increasePosition(dv); };
	void increaseScale(vec3 ds) { scale += ds; };
	void increaseScale(float ds) { scale += vec3(ds); };
	void increaseScale(float dxScale, float dyScale, float dzScale) { scale += vec3(dxScale, dyScale, dzScale); };
	void increaseRotationX(float dr) { rotationX += dr; };
	void increaseRotationY(float dr) { rotationY += dr; };
	void increaseRotationZ(float dr) { rotationZ += dr; };*/

};