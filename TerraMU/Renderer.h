#pragma once
#include <iostream>
#include <list>
#include <map>
#include "Entity.h"
#include "StreamShader.h"
using namespace std;

class Renderer {
private:
	StreamShader* shader;

	mat4 projection;

	void createProjectionMatrix();

public:
	Renderer(StreamShader *shader);
	void prepare();
	void render(list<Entity*> entities);
	void render(map<float, list<Entity*>> entities);
};