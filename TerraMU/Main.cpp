#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <SOIL.h>
#include <iostream>
#include "StaticShader.h"
#include "StreamShader.h"
#include "Display.h"
#include "Renderer.h"
#include "Loader.h"
#include "ModelTexture.h"
#include "TexturedModel.h"
#include "Camera.h"
//#include "KeyboardController.h"
#include "Entity.h"
#include "EntityBuilder.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
using namespace std;
using namespace glm;

vec2 mousePosition;

static void cursorPositionCallback(GLFWwindow *window, double xPos, double yPos) {
	mousePosition = vec2((float)xPos, (float)yPos);
}

static void keyCallback(GLFWwindow *window, int key, int scancode, int action, int mode) {
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
}

void initializeGLFW();
void initializeGLEW();

list<Entity *> *EntityBuilder::entities = new list<Entity *>();

int main() {
	initializeGLFW();
	Display *display = new Display();
	initializeGLEW();

	Loader *loader = new Loader();
	StreamShader *shader = new StreamShader();
	Renderer *renderer = new Renderer(shader);

	//glfwSetInputMode(display->getWindow(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);

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

	Entity* map = EntityBuilder::createEntity(loader, "map.png", positions, 12, indices, 6, textureCoords, 8,
		vec3(0.0f, 0.0f, -2.0f), 0.0f, 0.0f, 0.0f, 20.0f);

	Entity *player = EntityBuilder::createEntity(loader, "Player.png", positions, 12, indices, 6, textureCoords, 8,
		vec3(0.0f, 0.0f, -2.0f), 0.0f, 0.0f, 0.0f, 0.2f);

	Camera *camera = new Camera();

	//KeyboardController *controller = new KeyboardController(camera, display);

	//glfwSetCursorPosCallback(display->getWindow(), cursorPositionCallback);
	glfwSetKeyCallback(display->getWindow(), keyCallback);

	while (!display->isCloseRequested())
	{
		//entity->increaseRotationY(50.0f);
		//entity->increasePosition(0.0f, 0.0f, -0.01f);
		//controller->process();
	
		renderer->prepare();

		vec4 direction(0.0f);
		if (glfwGetKey(display->getWindow(), GLFW_KEY_UP) == GLFW_PRESS) {
			direction += vec4(0.0f, -1.0f, 0.0f, 0.0f);
		}
		if (glfwGetKey(display->getWindow(), GLFW_KEY_DOWN) == GLFW_PRESS) {
			direction += vec4(0.0f, 1.0f, 0.0f, 0.0f);
		}
		if (glfwGetKey(display->getWindow(), GLFW_KEY_LEFT) == GLFW_PRESS) {
			direction += vec4(1.0f, 0.0f, 0.0f, 0.0f);
		}
		if (glfwGetKey(display->getWindow(), GLFW_KEY_RIGHT) == GLFW_PRESS) {
			direction += vec4(-1.0f, 0.0f, 0.0f, 0.0f);
		}

		if (direction != vec4(0.0f)) {
			direction = normalize(direction);
		}

		vec4 move = scale(mat4(1.0f), vec3(0.01f)) * direction;
		map->increasePosition(move.x, move.y, move.z);

		shader->start();
		shader->loadViewMatrix(camera);
		renderer->render(map, shader);
		renderer->render(player, shader);
		glfwPollEvents();
		shader->stop();

		display->update();
	}

	shader->cleanUp();
	loader->cleanUp();
	delete shader;
	delete renderer;
	delete loader;

	EntityBuilder::cleanUp();

	delete camera;

	delete display;

	glfwTerminate();
	return 0;
}

void initializeGLFW() {
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
}

void initializeGLEW() {
	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK)
	{
		cout << "Failed to initialize GLEW" << endl;
		exit(-1);
	}
}