#include "Player.h"

void Player::hookGo(float coordX, float coordY) {
	destination->getAnimation()->reset();
	destination->getAnimation()->play();

	vec2 whither = Converter::fromMapToOpenGL(vec2(coordX, coordY));
	destination->setPosition(whither.x, whither.y, destination->getPosition().z);
}

void Player::hookUpdate() {
	destination->getAnimation()->stop();
}