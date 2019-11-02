#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/matrix_transform_2d.hpp>
#include <glm/gtc/type_ptr.hpp>
using namespace glm;

class Animation {
protected:
	float numberOfTimes;
	int period;
	int time = 0;
	float initialOffset;
	float currOffset;
	vec2 initialPosition;
	vec2 currPosition;
	vec2 scale;

public:
	Animation(float numberOfTimes, int period, vec2 position, vec2 scale, float offset) :
		numberOfTimes(numberOfTimes), period(period), initialOffset(offset),
		initialPosition(position), scale(scale), currPosition(position), currOffset(0.0f) {};

	virtual mat3 next() = 0;

	void play();
	void stop();
	void reset();

	void increasePosition(float delta);

	void setPosition(float y) { initialPosition.y = y; currPosition.y = y; };

};