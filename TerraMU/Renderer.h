#pragma once
#include "Entity.h"
#include "StreamShader.h"

class Renderer {
private:
	mat4 projection;

	void createProjectionMatrix();

public:
	Renderer(StreamShader *shader);
	void prepare();
	void render(Entity *entity, StreamShader *shader);
};