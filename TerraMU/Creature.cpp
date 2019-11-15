#include "GameController.h"
#include "Creature.h"

void Creature::hookGo(float coordX, float coordY) {
	return;
}

void Creature::hookUpdate() {
	return;
}

void Creature::hookChangeCamera(vec2 step) {
	return;
}

void Creature::hookStopAnimation() {
	return;
}

void Creature::go(float coordX, float coordY) {
	initialPosition = vec2(avatar->getPosition().x, avatar->getPosition().y - (float)avatar->getScale().y / (float)2);

	vec2 origin = Converter::fromOpenGLToMap(vec2(avatar->getPosition().x, avatar->getPosition().y - (float)avatar->getScale().y / (float)2));

	nullWay();
	way = WayHandler::buildWay((float)visibilityRadius / (float)GameController::getMap()->getScale().x * GameController::getMap()->getColumns(), origin, vec2(coordX, coordY));

	hookGo(coordX, coordY);
}

void Creature::update(float deltaTime) {
	hookUpdate();

	if (way && !way->empty()) {
		vec2 localWay = way->front();
		if (localWay == vec2(0.0f, 0.0f)) {
			way->pop_front();
			return;
		}
		localWay = vec2(localWay.x * GameController::getMap()->getScale().x / GameController::getMap()->getColumns(), -localWay.y * GameController::getMap()->getScale().y / GameController::getMap()->getRows());
		vec4 expandedStep = scale(mat4(1.0f), vec3(speed * deltaTime, speed * deltaTime, 1.0f)) * normalize(vec4(localWay.x, localWay.y, 0.0f, 0.0f));
		vec2 step = vec2(expandedStep.x, expandedStep.y);

		vec2 rest = (initialPosition + localWay) - vec2(avatar->getPosition().x, avatar->getPosition().y - avatar->getScale().y / 2);

		if (length(step) > length(rest)) {
			way->pop_front();
			initialPosition += localWay;
			this->update((float)length(step - rest) / speed);
			step = rest;
		}

		float index = Converter::fromOpenGLToMap(vec2(avatar->getPosition().y)).y;
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
	} else {
		hookStopAnimation();
	}

	GameController::getMap()->updateMobMap();
}

void Creature::nullWay() {
	if (way) {
		delete way;
		way = nullptr;
	}
}