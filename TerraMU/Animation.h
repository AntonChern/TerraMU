#pragma once
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/matrix_transform_2d.hpp>
#include <glm/gtc/type_ptr.hpp>
using namespace glm;

class Animation {
protected:
	float initialTime;
	float numberOfTimes;
	float period;
	float time = 0.0f;
	float initialOffset;
	float currOffset;
	vec2 initialPosition;
	vec2 currPosition;
	vec2 scale;

public:
	Animation(float numberOfTimes, float period, vec2 position, vec2 scale, float offset) :
		numberOfTimes(numberOfTimes), period(period), initialOffset(offset),
		initialPosition(position), scale(scale), currPosition(position), currOffset(0.0f), initialTime(glfwGetTime()) {};

	virtual mat3 next() = 0;

	void play();
	void stop();
	void reset();

	void increasePosition(float delta);

	void setPosition(float y) { initialPosition.y = y; currPosition.y = y; };

};