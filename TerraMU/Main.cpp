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
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
using namespace std;
using namespace glm;

vec2 mousePosition;

static void cursorPositionCallback(GLFWwindow *window, double xPos, double yPos) {
	mousePosition = vec2((float)xPos, (float)yPos);
}

void initializeGLFW();
void initializeGLEW();

int main() {
	initializeGLFW();
	Display *display = new Display();
	initializeGLEW();
	glfwSetCursorPosCallback(display->getWindow(), cursorPositionCallback);

	Loader *loader = new Loader();
	Renderer *renderer = new Renderer();
	ShaderProgram *shader = new StreamShader();

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

	RawModel *rawModel = loader->loadToVao(positions, 12, indices, 6, textureCoords, 8);
	ModelTexture *texture = new ModelTexture(loader->loadTexture("Player.png"));
	TexturedModel *model = new TexturedModel(rawModel, texture);

	while (!display->isCloseRequested())
	{
		renderer->prepare();

		shader->start();
		mat4 transform(1.0f);
		transform = translate(transform, vec3((mousePosition.x - 640)/640, (360 - mousePosition.y)/360, 0.0));
		transform = rotate(transform, (GLfloat)glfwGetTime() * 50.0f, vec3(0.0f, 0.1f, 0.0f));
		renderer->render(model, transform);
		glfwPollEvents();
		shader->stop();

		display->update();
	}

	shader->cleanUp();
	loader->cleanUp();
	delete shader;
	delete renderer;
	delete loader;

	delete rawModel;
	delete texture;
	delete model;

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