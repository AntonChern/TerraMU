#include "EntityFactory.h"
#include "ModelTexture.h"
#include "TexturedModel.h"
#include "AnimationDirect.h"
#include "Entity.h"
#include "RawModel.h"

TexturedModel* EntityFactory::createTexturedModel(char const texturePath[]) {
	RawModel* rawModel = createRawModel();
	ModelTexture* texture = new ModelTexture(loader->loadTexture(texturePath));
	TexturedModel* model = new TexturedModel(rawModel, texture);
	models.insert(std::pair<string, TexturedModel*>(texturePath, model));
	return model;
}

Entity* EntityFactory::createEntity(char const texturePath[], vec3 position, float rotationX, float rotationY, float rotationZ, vec3 scale) {
	return createEntity(texturePath, new AnimationDirect(0.0f, 1, vec2(0.0f), vec2(1.0f), 0.0f),
		position, rotationX, rotationY, rotationZ, scale);
}

Entity* EntityFactory::createEntity(char const texturePath[], vec3 position, float rotationX, float rotationY, float rotationZ, float scale) {
	return createEntity(texturePath, position, rotationX, rotationY, rotationZ, vec3(scale));
}

Entity* EntityFactory::createEntity(char const texturePath[], Animation* animation,
	vec3 position, float rotationX, float rotationY, float rotationZ, vec3 scale) {
	if (models.count(texturePath) == 0) {
		EntityFactory::createTexturedModel(texturePath);
	}
	TexturedModel* model = models.at(texturePath);

	Entity* entity = new Entity(model, animation, position, rotationX, rotationY, rotationZ, scale);
	entities.push_back(entity);

	return entity;
}

Entity* EntityFactory::createEntity(char const texturePath[], Animation* animation,
	vec3 position, float rotationX, float rotationY, float rotationZ, float scale) {
	return createEntity(texturePath, animation, position, rotationX, rotationY, rotationZ, vec3(scale));
}

void EntityFactory::cleanEntities(list<Entity*> entities) {
	for (Entity* entity : entities) {
		int initSize = EntityFactory::entities.size();
		EntityFactory::entities.remove(entity);
		if (initSize != EntityFactory::entities.size()) {
			delete entity;
		}
	}
}

void EntityFactory::cleanUp() {
	for (RawModel* model : rawModels) {
		delete model;
	}
	rawModels.clear();

	for (map<string, TexturedModel*>::iterator it = models.begin(); it != models.end(); it++) {
		TexturedModel* currModel = it->second;
		delete currModel->getTexture();
		delete currModel;
	}
	models.clear();

	for (Entity* entity : EntityFactory::entities) {
		delete entity;
	}
	entities.clear();

	/*for (Item* item : items) {
		delete item;
	}
	items.clear();*/
}

RawModel* EntityFactory::createRawModel() {
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
	rawModels.push_back(rawModel);
	return rawModel;
}

/*Item* EntityFactory::createItem(char const texturePath[], char const name[]) {
	TexturedModel* model = createTexturedModel(texturePath);
	Item* item = new Item(model, name);
	items.push_back(item);
	return item;
}*/

//void EntityFactory::cleanItems(list<Item*> items) {
//	for (Item* item : items) {
//		int initSize = EntityFactory::items.size();
//		EntityFactory::items.remove(item);
//		if (initSize != EntityFactory::items.size()) {
//			delete item;
//		}
//	}
//}

/*Entity* EntityFactory::createEntity(TexturedModel* model, vec3 position, float rotationX, float rotationY, float rotationZ, vec3 scale) {
	Entity* entity = new Entity(model, new AnimationDirect(0.0f, 1, vec2(0.0f), vec2(1.0f), 0.0f),
		position, rotationX, rotationY, rotationZ, scale);
	entities.push_back(entity);

	return entity;
}*/

/*Entity* EntityFactory::createEntity(TexturedModel* model, vec3 position, float rotationX, float rotationY, float rotationZ, float scale) {
	return createEntity(model, position, rotationX, rotationY, rotationZ, vec3(scale));
}*/