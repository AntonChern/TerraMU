#include "AnimationDirect.h"

mat3 AnimationDirect::next() {
	float deltaTime = glfwGetTime() - initialTime;
	initialTime += deltaTime;
	if (numberOfTimes > 0) {
		if (time >= period) {
			time = 0.0f;
			currPosition.x += currOffset;
			if (currPosition.x >= 1.0f) {
				numberOfTimes -= 1.0f;
				currPosition.x -= 1.0f;
			}
		}
		time += deltaTime;
	}
	else {
		stop();
	}
	return Maths::createTextureMatrix(currPosition, scale);
}