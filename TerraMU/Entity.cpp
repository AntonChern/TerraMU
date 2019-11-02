#include "Entity.h"

Entity::~Entity() {
	if (animation) {
	    delete animation;
	}
}

void Entity::setAnimation(Animation* animation) {
	if (animation) {
		delete animation;
	}
	this->animation = animation;
}