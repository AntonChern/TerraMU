#pragma once
#include "Animation.h"

class AnimationPendulum : public Animation {
public:
	AnimationPendulum(float numberOfTimes, int period, vec2 position, vec2 scale, float offset) :
		Animation(numberOfTimes, period, position, scale, offset) {};

	mat3 next();
};