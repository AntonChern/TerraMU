#include "Monster.h"

bool Monster::seesPlayerIn(float radius) {
	vec3 playerPosition = GameController::getPlayer()->getAvatar()->getPosition();
	vec3 monsterPosition = avatar->getPosition();
	vec2 distance = vec2(playerPosition.x - monsterPosition.x, playerPosition.y - monsterPosition.y);
	return length(distance) <= radius;
}

void Monster::hookStartAnimation() {
	if (!isAnimated) {
		avatar->getAnimation()->play();
	}
}

void Monster::hookStopAnimation() {
	if (!isAnimated) {
		avatar->getAnimation()->stop();
		avatar->getAnimation()->reset();
	}
}

void Monster::goToAttack() {
	target = Converter::fromOpenGLToMap(vec2(GameController::getPlayer()->getAvatar()->getPosition().x,
		GameController::getPlayer()->getAvatar()->getPosition().y - (float)GameController::getPlayer()->getAvatar()->getScale().y / 2));
	Creature::go(target.x, target.y);
}

void Monster::hookUpdate() {
	state->checkAttitudeToPlayer();
}

void Monster::update(float deltaTime) {
	delete state;
	if (this->seesPlayerIn(visibilityRadius)) {
		state = new Angry(this);
	} else {
		state = new Pacific(this);
	}

	state->execute();
	Creature::update(deltaTime);
}

void Monster::State::checkAttitudeToPlayer() {
	return;
}

void Monster::State::execute() {
	return;
}

void Monster::Pacific::checkAttitudeToPlayer() {
	return;
}

void Monster::Pacific::execute() {
	if (monster->getTime() == monster->getMovingPeriod() * 10) {
		monster->nullTime();
		float randValue = ((float)rand() / (RAND_MAX));
		if (randValue <= monster->getMovingProbability()) {

			float randX = ((float)rand() / (RAND_MAX)-0.5f) * monster->getVisibilityRadius();
			float randY = ((float)rand() / (RAND_MAX)-0.5f) * monster->getVisibilityRadius();

			vec3 expandedMonsterPosition = monster->getAvatar()->getPosition();
			vec2 monsterPosition = vec2(expandedMonsterPosition.x, expandedMonsterPosition.y - (float)monster->getAvatar()->getScale().y / 2);

			vec2 result = Converter::fromOpenGLToMap(monsterPosition + vec2(randX, randY));

			GameController::getMap()->interact(result.x, result.y);
		}
	}
	monster->incTime();
}

void Monster::Angry::checkAttitudeToPlayer() {
	if (monster->seesPlayerIn((float)GameController::getMap()->getScale().x / GameController::getMap()->getColumns())) {
		monster->nullWay();
	}
}

void Monster::Angry::execute() {
	vec2 playerPosition = Converter::fromOpenGLToMap(vec2(GameController::getPlayer()->getAvatar()->getPosition().x,
		GameController::getPlayer()->getAvatar()->getPosition().y - (float)GameController::getPlayer()->getAvatar()->getScale().y / 2));
	if (monster->getTarget() != playerPosition) {
		monster->goToAttack();
	}
}