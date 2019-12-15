#include "Entity.h"
#include "Animation.h"

Entity::~Entity() {
	if (animation) {
	    delete animation;
	}
}

void Entity::setAnimation(Animation* animation) {
	if (this->animation) {
		delete this->animation;
	}
	this->animation = animation;
}