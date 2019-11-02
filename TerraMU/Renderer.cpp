#include "Renderer.h"
#include "Maths.h"
#include "Display.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <list>
using namespace std;

Renderer::Renderer(StreamShader *shader) : shader(shader) {
	createProjectionMatrix();
	shader->start();
	shader->loadProjectionMatrix(projection);
	shader->stop();
}

void Renderer::prepare() {
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_DEPTH_TEST);
	glClearColor(0.07843f, 0.07843f, 0.07843f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Renderer::render(list<Entity*> entities) {
	for (Entity* entity : entities) {
		TexturedModel* texturedModel = entity->getTexturedModel();
		RawModel *model = texturedModel->getRawModel();
		glBindVertexArray(model->getVaoID());
		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);

		shader->loadTransormMatrix(Maths::createTransformMatrix(entity->getPosition(),
			entity->getRotationX(), entity->getRotationY(), entity->getRotationZ(), entity->getScale()));

		shader->loadTextureMatrix(entity->getTextureMatrix());

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texturedModel->getTexture()->getID());
		glDrawElements(GL_TRIANGLES, model->getVertexCount(), GL_UNSIGNED_INT, 0);

		glDisable(GL_BLEND);

		glDisableVertexAttribArray(0);
		glDisableVertexAttribArray(1);
	
		glBindVertexArray(0);
	}
}

void Renderer::createProjectionMatrix() {
	float aspect = (float)Display::getWidth() / (float)Display::getHeight();
	projection = ortho(-1.0f * aspect, 1.0f * aspect, -1.0f, 1.0f, 0.0f, 100.0f);
	//projection = perspective(45.0f, (float)Display::getWidth() / Display::getHeight(), 0.1f, 100.0f);
}