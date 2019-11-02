#pragma once
#include <iostream>
#include <list>
#include "Renderer.h"
#include "StreamShader.h"
using namespace std;

class MasterRenderer {
private:
	StreamShader* shader;
	Renderer* renderer;

	list<Entity*> entities;

	list<Entity*> sortEntities(vec3 cameraPosition);

public:
	MasterRenderer() : shader(new StreamShader()), renderer(new Renderer(shader)) {};

	void processEntity(Entity* entity);
	void processEntities(list<Entity*> entities);
	void render(Camera* camera);
	void cleanUp() { shader->cleanUp(); };
};