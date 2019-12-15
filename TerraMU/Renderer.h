#pragma once
#define GLM_FORCE_RADIANS
#include <iostream>
#include <list>
#include <map>
class Entity;
class StreamShader;
#include <glm/glm.hpp>
using namespace glm;
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