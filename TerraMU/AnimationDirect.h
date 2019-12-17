#pragma once
#include "Animation.h"
class Maths;

class AnimationDirect : public Animation {
public:
	AnimationDirect(float numberOfTimes, float period, vec2 position, vec2 scale, float offset) :
		Animation(numberOfTimes, period, position, scale, offset) {};

	mat3 next();
};