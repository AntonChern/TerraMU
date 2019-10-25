#include "EntityBuilder.h"

list<Entity*>* EntityBuilder::entities = new list<Entity*>();
list<TexturedModel*>* EntityBuilder::models = new list<TexturedModel*>();

TexturedModel* EntityBuilder::createTexturedModel(Loader* loader, char const texturePath[]) {
	float positions[] = {
		-0.5f, 0.5f, 0.0f,
		-0.5f, -0.5f, 0.0f,
		0.5f, -0.5f, 0.0f,
		0.5f, 0.5f, 0.0f,
	};

	int indices[] = {
		2, 1, 0,
		3, 2, 0,
	};

	float textureCoords[] = {
		0.0f, 0.0f,
		0.0f, 1.0f,
		1.0f, 1.0f,
		1.0f, 0.0f,
	};

	RawModel* rawModel = loader->loadToVao(positions, 12, indices, 6, textureCoords, 8);
	ModelTexture* texture = new ModelTexture(loader->loadTexture(texturePath));
	TexturedModel* model = new TexturedModel(rawModel, texture);
	EntityBuilder::models->push_back(model);
	return model;
}

Entity* EntityBuilder::createEntity(Loader* loader, char const texturePath[],
	vec3 position, float rotationX, float rotationY, float rotationZ, vec3 scale) {

	Entity *entity = new Entity(EntityBuilder::createTexturedModel(loader, texturePath), position, rotationX, rotationY, rotationZ, scale);
	EntityBuilder::entities->push_back(entity);
	return entity;
}

Entity* EntityBuilder::createEntity(Loader* loader, char const texturePath[],
	vec3 position, float rotationX, float rotationY, float rotationZ, float scale) {

	return createEntity(loader, texturePath, position, rotationX, rotationY, rotationZ, vec3(scale));
}

void EntityBuilder::cleanUp() {
	for (TexturedModel* model : *EntityBuilder::models) {
		delete model->getRawModel();
		delete model->getTexture();
		delete model;
	}
	delete models;

	for (Entity *entity : *EntityBuilder::entities) {
		delete entity;
	}
	delete entities;
}