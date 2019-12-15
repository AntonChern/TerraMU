#pragma once
#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
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
	Animation(float numberOfTimes, float period, vec2 position, vec2 scale, float offset);

	virtual mat3 next() = 0;

	void play();
	void stop();
	void reset();

	void increasePosition(float delta);

	void setPosition(float y) { initialPosition.y = y; currPosition.y = y; };

};