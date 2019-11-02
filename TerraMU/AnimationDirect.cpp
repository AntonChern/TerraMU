#include "AnimationDirect.h"

mat3 AnimationDirect::next() {
	mat3 textureMatrix(1.0f);
	if (time <= period * numberOfTimes / length(scale)) {
		if (time % period == 0) {
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