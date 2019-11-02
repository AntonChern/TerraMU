#pragma once
#include "Animation.h"

class AnimationDirect : public Animation {
public:
	AnimationDirect(float numberOfTimes, int period, vec2 position, vec2 scale, float offset) :
		Animation(numberOfTimes, period, position, scale, offset) {};

	mat3 next();
};