#pragma once
#include "Entity.h"
#include "Loader.h"
#include <iostream>
#include <map>
using namespace std;

class EntityFactory {
private:
	static Loader* loader;

	static list<Entity*> entities;
	static map<string, TexturedModel*> models;
	static list<RawModel*> rawModels;
	//static list<Item*> items;

	static TexturedModel* createTexturedModel(char const texturePath[]);

public:
	static void setLoader(Loader* loader) { EntityFactory::loader = loader; };

	static void cleanUp();

	static void cleanEntities(list<Entity*> entities);
	//static void cleanItems(list<Item*> items);

	static Entity* createEntity(char const texturePath[], vec3 position, float rotationX, float rotationY, float rotationZ, vec3 scale);
	static Entity* createEntity(char const texturePath[], vec3 position, float rotationX, float rotationY, float rotationZ, float scale);

	static Entity* createEntity(char const texturePath[], Animation* animation,
		vec3 position, float rotationX, float rotationY, float rotationZ, vec3 scale);
	static Entity* createEntity(char const texturePath[], Animation* animation,
		vec3 position, float rotationX, float rotationY, float rotationZ, float scale);

	//static Entity* createEntity(TexturedModel* model, vec3 position, float rotationX, float rotationY, float rotationZ, vec3 scale);
	//static Entity* createEntity(TexturedModel* model, vec3 position, float rotationX, float rotationY, float rotationZ, float scale);

	//static Item* createItem(char const texturePath[], char const name[]);

	static RawModel* createRawModel();

};