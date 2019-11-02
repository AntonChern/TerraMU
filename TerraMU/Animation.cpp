#include "Animation.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/matrix_transform_2d.hpp>
#include <glm/gtc/type_ptr.hpp>
using namespace glm;

void Animation::play() {
	currOffset = initialOffset;
}

void Animation::stop() {
	currOffset = 0.0f;
}

void Animation::reset() {
	currPosition = initialPosition;
}

void Animation::increasePosition(float delta) {
	initialPosition.y += delta;
	currPosition.y += delta;
	if (initialPosition.y <= 0.0f) {
		initialPosition.y += 1.0f;
		currPosition.y += 1.0f;
	}
	if (initialPosition.y >= 1.0f) {
		initialPosition.y -= 1.0f;
		currPosition.y -= 1.0f;
	}
}