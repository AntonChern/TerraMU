#pragma once
#include "Creature.h"

class Monster: public Creature {
protected:
	class State {
	protected:
		Monster* monster;
	public:
		State(Monster* monster) : monster(monster) {};

		virtual void execute();
		virtual void checkAttitudeToPlayer();
	};

	class Angry: public State {
	public:
		Angry(Monster* monster) : State(monster) {};

		void execute();
		void checkAttitudeToPlayer();
	};

	class Pacific: public State {
	public:
		Pacific(Monster* monster) : State(monster) {};

		void execute();
		void checkAttitudeToPlayer();
	};

	vec2 target;
	State* state;
	float visibilityRadius;
	float movingProbability;
	int movingPeriod;
	int time;
	bool isAnimated;
public:
	Monster(Entity* avatar, float speed, bool isAnimated, float visibilityRadius, float movingProbability, int movingPeriod) :
		Creature(avatar, speed), isAnimated(isAnimated), visibilityRadius(visibilityRadius), movingProbability(movingProbability), movingPeriod(movingPeriod)
	{ this->state = new Pacific(this); if (isAnimated) { avatar->getAnimation()->play(); } time = movingPeriod; };

	void goToAttack();
	void update(float deltaTime);
	void hookUpdate();
	void hookStartAnimation();
	void hookStopAnimation();

	vec2 getTarget() { return this->target; };
	float getVisibilityRadius() { return this->visibilityRadius; };
	float getMovingProbability() { return this->movingProbability; };
	int getMovingPeriod() { return this->movingPeriod; };
	int getTime() { return this->time; };
	void incTime() { this->time++; };
	void nullTime() { this->time = 0; };
	bool seesPlayerIn(float radius);
};

