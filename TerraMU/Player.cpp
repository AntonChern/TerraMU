#include "Player.h"
#include "Converter.h"
#include "Camera.h"
#include "GameController.h"
#include "Animation.h"

void Player::hookGo(float coordX, float coordY) {
	destination->getAnimation()->reset();
	destination->getAnimation()->play();

	vec2 whither = Converter::fromMapToOpenGL(vec2(coordX, coordY));
	destination->setPosition(whither.x, whither.y, destination->getPosition().z);
}

void Player::hookChangeCamera(vec2 step) {
	GameController::getCamera()->increasePosition(step.x, step.y, 0);
}

void Player::hookUpdate() {
	if (!way || way->empty()) {
		destination->getAnimation()->stop();
	}
}

void Player::hookStopAnimation() {
	avatar->getAnimation()->stop();
	avatar->getAnimation()->reset();
}