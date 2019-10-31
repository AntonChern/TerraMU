#include "EntityBuilder.h"
#include "EntityInstance.h"
#include "EntityWrapper.h"

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

	Entity* entity = nullptr;

	for (map<string, Entity*>::iterator it = entities->begin(); it != entities->end(); it++) {
		if (it->first == texturePath) {
			entity = new EntityWrapper(it->second, position, rotationX, rotationY, rotationZ, scale);
			break;
		}
	}

	if (!entity) {
		entity = new EntityInstance(EntityBuilder::createTexturedModel(loader, texturePath), position, rotationX, rotationY, rotationZ, scale);
		entities->insert(std::pair<string, Entity*>(texturePath, entity));
	}

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

	for (map<string, Entity*>::iterator it = entities->begin(); it != entities->end(); it++) {
		delete it->second;
	}
	delete entities;

}