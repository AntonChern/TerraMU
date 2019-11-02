#include "AnimationPendulum.h"

mat3 AnimationPendulum::next() {
	mat3 textureMatrix(1.0f);
	if (time <= period * numberOfTimes / scale.x) {
		if (time % period == 0) {
			if (currPosition.x + currOffset >= 1.0f || currPosition.x + currOffset < 0.0f) {
				currOffset *= -1;
			}
			currPosition.x += currOffset;
		}
		time++;
	}
	else {
		stop();
	}
	textureMatrix = translate(textureMatrix, currPosition);
	textureMatrix = glm::scale(textureMatrix, scale);
	return textureMatrix;
}