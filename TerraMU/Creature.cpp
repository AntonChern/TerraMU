#include "Creature.h"

void Creature::hookGo(float coordX, float coordY) {
	return;
}

void Creature::hookUpdate() {
	return;
}

void Creature::hookChangeCamera(vec3 step) {
	return;
}

void Creature::hookStartAnimation() {
	return;
}

void Creature::hookStopAnimation() {
	return;
}

void Creature::go(float coordX, float coordY) {
	hookStartAnimation();
	initialPosition = vec3(avatar->getPosition().x, avatar->getPosition().y - avatar->getScale().y / 2, 0);

	vec2 origin = Converter::fromOpenGLToMap(vec2(avatar->getPosition().x, avatar->getPosition().y - avatar->getScale().y / 2));
	way = WayHandler::buildWay(origin.x, origin.y, coordX, coordY, GameController::getMap()->getReachMap(), GameController::getMap()->getColumns(), GameController::getMap()->getRows());

	hookGo(coordX, coordY);
}

void Creature::update(float deltaTime) {
	hookUpdate();

	if (way && !way->empty()) {
		vec2 flatLocalWay = way->front();
		if (flatLocalWay == vec2(0.0f, 0.0f)) {
			way->pop();
			return;
		}
		flatLocalWay = vec2(flatLocalWay.x * GameController::getMap()->getScale().x / GameController::getMap()->getColumns(), -flatLocalWay.y * GameController::getMap()->getScale().y / GameController::getMap()->getRows());
		vec3 localWay = vec3(flatLocalWay.x, flatLocalWay.y, 0);
		vec4 expandedStep = scale(mat4(1.0f), vec3(speed * deltaTime, speed * deltaTime, 1.0f)) * normalize(vec4(localWay.x, localWay.y, localWay.z, 0));
		vec3 step = vec3(expandedStep.x, expandedStep.y, expandedStep.z);

		vec3 rest = (initialPosition + localWay) - vec3(avatar->getPosition().x, avatar->getPosition().y - avatar->getScale().y / 2, 0);

		if (length(step) > length(rest)) {
			way->pop();
			initialPosition += localWay;
			this->update((float)length(step - rest) / speed);
			step = rest;
		}


		int index = Converter::fromOpenGLToMap(vec2(avatar->getPosition().y)).y;
		avatar->increasePosition(step.x, step.y, 0);
		avatar->setPosition(avatar->getPosition().x, avatar->getPosition().y, index * 0.001f + 0.0015f);
		hookChangeCamera(step);

		if (step.y < -abs(step.x)) {
			avatar->getAnimation()->setPosition(0.0f);
		}
		if (step.x <= -abs(step.y)) {
			avatar->getAnimation()->setPosition(0.25f);
		}
		if (step.x >= abs(step.y)) {
			avatar->getAnimation()->setPosition(0.5f);
		}
		if (step.y > abs(step.x)) {
			avatar->getAnimation()->setPosition(0.75f);
		}
	}
	else {
		hookStopAnimation();
	}
}

void Creature::nullWay() {
	if (way) {
		delete way;
		way = nullptr;
	}
}