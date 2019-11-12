#include "AnimationPendulum.h"

mat3 AnimationPendulum::next() {
	float deltaTime = glfwGetTime() - initialTime;
	initialTime += deltaTime;
	if (numberOfTimes > 0) {
		if (time >= period) {
			if (currPosition.x + currOffset >= 1.0f || currPosition.x + currOffset < 0.0f) {
				numberOfTimes -= 1.0f;
				currOffset *= -1;
			}
			time = 0.0f;
			currPosition.x += currOffset;
		}
		time += deltaTime;
	}
	else {
		stop();
	}
	return Maths::createTextureMatrix(currPosition, scale);
}