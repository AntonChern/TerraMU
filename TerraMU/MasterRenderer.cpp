#include <map>
#include "MasterRenderer.h"

list<Entity*> MasterRenderer::sortEntities(vec3 cameraPosition) {
	map<float, list<Entity*>> entitiesByDistance;
	for (Entity* entity : entities) {

		float distance = cameraPosition.z - entity->getPosition().z;

		list<Entity*> list;
		if (entitiesByDistance.count(distance) != 0) {
			list = entitiesByDistance[distance];
		}
		list.push_back(entity);
		entitiesByDistance[distance] = list;
	}

	list<Entity*> sortedEntities;
	for (std::map<float, list<Entity*>>::reverse_iterator it = entitiesByDistance.rbegin(); it != entitiesByDistance.rend(); it++) {
		for (Entity* entity : it->second) {
			sortedEntities.push_back(entity);
		}
	}

	return sortedEntities;
}

void MasterRenderer::processEntity(Entity* entity) {
	entities.push_back(entity);
}

void MasterRenderer::processEntities(list<Entity*> entities) {
	for (Entity* entity : entities) {
		processEntity(entity);
	}
}

void MasterRenderer::render(Camera* camera) {
	entities = sortEntities(camera->getPosition());
	renderer->prepare();
	shader->start();
	shader->loadViewMatrix(camera);
	renderer->render(entities);
	shader->stop();
	entities.clear();
}