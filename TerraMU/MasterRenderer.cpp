#include <map>
#include "MasterRenderer.h"

map<float, list<Entity*>> MasterRenderer::getEntitiesByDistance(vec3 cameraPosition) {
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

	return entitiesByDistance;
}

void MasterRenderer::sortEntities(vec3 cameraPosition) {
	map<float, list<Entity*>> entitiesByDistance = getEntitiesByDistance(cameraPosition);

	entities.clear();
	for (std::map<float, list<Entity*>>::reverse_iterator it = entitiesByDistance.rbegin(); it != entitiesByDistance.rend(); it++) {
		for (Entity* entity : it->second) {
			entities.push_back(entity);
		}
	}
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
	sortEntities(camera->getPosition());
	renderer->prepare();
	shader->start();
	shader->loadViewMatrix(camera);
	renderer->render(getEntitiesByDistance(camera->getPosition()));
	shader->stop();
	entities.clear();
}