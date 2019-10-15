#pragma once
#include "Entity.h"
#include "Loader.h"
#include <iostream>
using namespace std;

class EntityBuilder {
private:
	static list<Entity *> *entities;

public:
	static void prepare();
	static void cleanUp();
	static Entity *createEntity(Loader *loader, char const texturePath[],
		float positions[], int positionsCount, int indices[], int indicesCount, float textureCoords[], int textureCoordsCount,
		vec3 position, float rotationX, float rotationY, float rotationZ, float scale);
};