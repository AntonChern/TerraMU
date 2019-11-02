#pragma once
#include <iostream>
#include <list>
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
};