#include "EntityBuilder.h"

Entity* EntityBuilder::createEntity(Loader* loader, char const texturePath[],
	float positions[], int positionsCount, int indices[], int indicesCount, float textureCoords[], int textureCoordsCount,
	vec3 position, float rotationX, float rotationY, float rotationZ, float scale) {

	RawModel* rawModel = loader->loadToVao(positions, positionsCount, indices, indicesCount, textureCoords, textureCoordsCount);
	ModelTexture* texture = new ModelTexture(loader->loadTexture(texturePath));
	TexturedModel* model = new TexturedModel(rawModel, texture);
	Entity *entity = new Entity(model, position, rotationX, rotationY, rotationZ, scale);
	EntityBuilder::entities->push_back(entity);
	return entity;
}

void EntityBuilder::prepare() {
	//EntityBuilder::entities = new list<Entity *>();
}

void EntityBuilder::cleanUp() {
	for (Entity *entity : *EntityBuilder::entities) {
		delete entity->getTexturedModel()->getRawModel();
		delete entity->getTexturedModel()->getTexture();
		delete entity->getTexturedModel();
		delete entity;
	}
	delete entities;
}