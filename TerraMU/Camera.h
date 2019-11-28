#pragma once
#include "Display.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
using namespace glm;

class Camera {
private:
	//static float const width = 2.0f * (float)Display::getWidth() / (float)Display::getHeight();
	//static float const height = 2.0f;

	vec3 position;
	float roll;
	float yaw;
	float pitch;

public:
	Camera() : position(vec3(0.0f, 0.0f, 0.0f)), roll(0.0f), yaw(0.0f), pitch(0.0f) {};

	static constexpr float getWidth() { return 2.0f * (float)Display::getWidth() / (float)Display::getHeight(); };
	static constexpr float getHeight() { return 2.0f; };

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

};