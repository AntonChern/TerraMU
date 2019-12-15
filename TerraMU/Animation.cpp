#include "Animation.h"
#include <GLFW/glfw3.h>

Animation::Animation(float numberOfTimes, float period, vec2 position, vec2 scale, float offset) :
	numberOfTimes(numberOfTimes), period(period), initialOffset(offset),
	initialPosition(position), scale(scale), currPosition(position), currOffset(0.0f), initialTime((float)glfwGetTime()) {

}

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