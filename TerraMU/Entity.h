#pragma once
#define GLM_FORCE_RADIANS
#include "Moveable.h"
class TexturedModel;
class Animation;

class Entity : public Moveable {
private:
	TexturedModel* model;
	Animation* animation;

public:
	Entity(TexturedModel* model, Animation* animation, vec3 position, float rotationX, float rotationY, float rotationZ, vec3 scale) :
		Moveable(position, rotationX, rotationY, rotationZ, scale), model(model), animation(animation) {};

	~Entity();

	TexturedModel* getTexturedModel() { return model; };

	Animation* getAnimation() { return animation; };
	void setAnimation(Animation* animation);

};