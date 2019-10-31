#pragma once
#include "GUI.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
using namespace glm;

class Camera {
private:
	//GUI* gui;

	vec3 position;
	float roll;
	float yaw;
	float pitch;

public:
	Camera(/*GUI* gui*/);

	//GUI* getGUI() { return gui; };

	vec3 getPosition() { return position; };
	float getRoll() { return roll; };
	float getYaw() { return yaw; };
	float getPitch() { return pitch; };

	void setPosition(float x, float y, float z) { position = vec3(x, y, z); };
	void setPosition(vec3 position) { this->position = position; };
	void setRoll(float r) { roll = r; };
	void setYaw(float r) { yaw = r; };
	void setPitch(float r) { pitch = r; };

	void increasePosition(float dx, float dy, float dz) { position += vec3(dx, dy, dz); };
	void increasePosition(vec3 dv) { position += dv; };
	void increaseRoll(float dr) { roll += dr; };
	void increaseYaw(float dr) { yaw += dr; };
	void increasePitch(float dr) { pitch += dr; };

	/*void setPosition(float x, float y, float z) { position = vec3(x, y, z); gui->setPosition(position); };
	void setPosition(vec3 position) { this->position = position; gui->setPosition(position); };
	void setRoll(float r) { roll = r; gui->setRotationZ(r); };
	void setYaw(float r) { yaw = r; gui->setRotationY(r); };
	void setPitch(float r) { pitch = r; gui->setRotationX(r); };

	void increasePosition(float dx, float dy, float dz) { position += vec3(dx, dy, dz); gui->increasePosition(vec3(dx, dy, dz)); };
	void increasePosition(vec3 dv) { position += dv; gui->increasePosition(dv); };
	void increaseRoll(float dr) { roll += dr; gui->increaseRotationZ(dr); };
	void increaseYaw(float dr) { yaw += dr; gui->increaseRotationY(dr); };
	void increasePitch(float dr) { pitch += dr; gui->increaseRotationX(dr); };*/
};