#pragma once
#include "Entity.h"
#include "Loader.h"
#include <iostream>
#include <map>
using namespace std;

class EntityBuilder {
private:
	static list<TexturedModel*>* models;
	static map<string, Entity*>* entities;

	static TexturedModel* createTexturedModel(Loader* loader, char const texturePath[]);

public:
	static void cleanUp();
	static Entity *createEntity(Loader *loader, char const texturePath[], vec3 position,
		float rotationX, float rotationY, float rotationZ, vec3 scale);
	static Entity* createEntity(Loader* loader, char const texturePath[], vec3 position,
		float rotationX, float rotationY, float rotationZ, float scale);
};