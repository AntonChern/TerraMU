#pragma once
#define GLM_FORCE_RADIANS
class GameController;
#include "Animation.h"
#include "Creature.h"

class Monster : public Creature {
protected:
	class State {
	protected:
		Monster* monster;
	public:
		State(Monster* monster) : monster(monster) {};
		virtual void execute();
	};

	class Angry : public State {
	public:
		Angry(Monster* monster) : State(monster) {};
		void execute();
	};

	class Pacific : public State {
	public:
		Pacific(Monster* monster) : State(monster) {};
		void execute();
	};

	vec2 target;
	State* state;
	float movingProbability;
	int movingPeriod;
	int time;
	bool isAnimated;

	int maxHealth;
public:
	Monster(Entity* avatar, float speed, float visibilityRadius, int maxHealth, bool isAnimated, float movingProbability, int movingPeriod) :
		Creature(avatar, speed, visibilityRadius), maxHealth(maxHealth), isAnimated(isAnimated), movingProbability(movingProbability), movingPeriod(movingPeriod)
	{ this->state = new Pacific(this); if (isAnimated) { avatar->getAnimation()->play(); } time = movingPeriod; health = maxHealth; };

	void goToAttack();
	void update(float deltaTime);
	void hookStopAnimation();

	bool getIsAnimated() { return this->isAnimated; };
	vec2 getTarget() { return this->target; };
	float getVisibilityRadius() { return Creature::visibilityRadius; };
	float getMovingProbability() { return this->movingProbability; };
	int getMovingPeriod() { return this->movingPeriod; };
	int getTime() { return this->time; };
	void incTime() { this->time++; };
	void nullTime() { this->time = 0; };
	bool seesPlayerIn(float radius);
	list<vec2>* getWay() { return Creature::way; };
	//void shortenPath();

	void hit();
	void interact(float x, float y);
};

