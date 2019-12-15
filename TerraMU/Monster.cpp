#include "Monster.h"
#include "Map.h"
#include "WayHandler.h"
#include "GameController.h"
#include "Converter.h"

bool Monster::seesPlayerIn(float radius) {
	vec3 playerPosition = GameController::getPlayer()->getAvatar()->getPosition();
	vec3 monsterPosition = avatar->getPosition();
	vec2 distance = vec2(playerPosition.x - monsterPosition.x, playerPosition.y - monsterPosition.y);
	return length(distance) <= radius;
}

void Monster::hookStopAnimation() {
	if (!isAnimated) {
		avatar->getAnimation()->stop();
		avatar->getAnimation()->reset();
	}
}

void Monster::goToAttack() {
	if (!isInMotion() && !isAnimated) {
		avatar->getAnimation()->play();
	}
	nullWay();

	target = Converter::fromOpenGLToMap(vec2(GameController::getPlayer()->getAvatar()->getPosition().x,
		GameController::getPlayer()->getAvatar()->getPosition().y - (float)GameController::getPlayer()->getAvatar()->getScale().y / (float)2));

	vec2 origin = Converter::fromOpenGLToMap(vec2(avatar->getPosition().x, avatar->getPosition().y - (float)avatar->getScale().y / (float)2));
	if (WayHandler::existsPath((float)visibilityRadius / (float)GameController::getMap()->getScale().x * GameController::getMap()->getColumns(), origin, target)) {
		Creature::go(target.x, target.y);
		shortenPath();
	} else {
		vec2 newTarget = WayHandler::getOptimalEnd((float)visibilityRadius / (float)GameController::getMap()->getScale().x * GameController::getMap()->getColumns(), origin, target);
		Creature::go(newTarget.x, newTarget.y);
	}
}

void Monster::update(float deltaTime) {
	delete state;
	if (this->seesPlayerIn(visibilityRadius)) {
		state = new Angry(this);
	}
	else {
		state = new Pacific(this);
	}

	state->execute();
	Creature::update(deltaTime);
}

void Monster::State::execute() {
	return;
}

void Monster::Pacific::execute() {
	if (monster->getTime() == monster->getMovingPeriod()) {
		monster->nullTime();
		float randValue = ((float)rand() / (RAND_MAX));
		if (randValue <= monster->getMovingProbability()) {

			float randX = ((float)rand() / (RAND_MAX) - 0.5f) * 2 * monster->getVisibilityRadius();
			float randY = ((float)rand() / (RAND_MAX) - 0.5f) * 2 * monster->getVisibilityRadius();

			vec3 expandedMonsterPosition = monster->getAvatar()->getPosition();
			vec2 monsterPosition = vec2(expandedMonsterPosition.x, expandedMonsterPosition.y - (float)monster->getAvatar()->getScale().y / 2);

			vec2 result = Converter::fromOpenGLToMap(monsterPosition + vec2(randX, randY));

			if ((result.x >= 0 && result.x < GameController::getMap()->getColumns()) && (result.y >= 0 && result.y < GameController::getMap()->getRows()) &&
				GameController::getMap()->getReachMap()[(int)result.x][(int)result.y] && GameController::getMap()->getMobMap()[(int)result.x][(int)result.y]) {

				if (!monster->isInMotion() && !monster->getIsAnimated()) {
					monster->getAvatar()->getAnimation()->play();
				}
				monster->go(result.x, result.y);
			}
		}
	}
	monster->incTime();
}

void Monster::Angry::execute() {
	vec2 playerPosition = Converter::fromOpenGLToMap(vec2(GameController::getPlayer()->getAvatar()->getPosition().x,
		GameController::getPlayer()->getAvatar()->getPosition().y - (float)GameController::getPlayer()->getAvatar()->getScale().y / 2));
	vec2 initial = Converter::fromOpenGLToMap(vec2(monster->getInitialPosition().x,
		monster->getInitialPosition().y - (float)monster->getAvatar()->getScale().y / 2));
	vec2 monsterPosition = Converter::fromOpenGLToMap(vec2(monster->getAvatar()->getPosition().x,
		monster->getAvatar()->getPosition().y - (float)monster->getAvatar()->getScale().y / 2));

	if (!(monster->getTarget() == playerPosition && WayHandler::isWalkable(monster->getWay(), monsterPosition, initial))) {
		monster->goToAttack();
	}
}

void Monster::shortenPath() {
	if (seesPlayerIn((float)GameController::getMap()->getScale().x / (float)GameController::getMap()->getColumns())) {
		nullWay();
	} else {
		float distance = 1.0f;
		vec2 final = way->back();
		float coef = 1.0f - (float)distance / (float)std::sqrt(final.x * final.x + final.y * final.y);
		way->back() *= coef;
	}
}