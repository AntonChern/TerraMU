#include "Renderer.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>

void Renderer::prepare() {
	glClearColor(0.07843f, 0.07843f, 0.07843f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
}

void Renderer::render(TexturedModel *texturedModel, mat4 transform) {
	RawModel *model = texturedModel->getRawModel();
	glBindVertexArray(model->getVaoID());
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);

	GLuint transformLoc = glGetUniformLocation(3, "transform");
	glUniformMatrix4fv(transformLoc, 1, GL_FALSE, value_ptr(transform));

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texturedModel->getTexture()->getID());
	glDrawElements(GL_TRIANGLES, model->getVertexCount(), GL_UNSIGNED_INT, 0);
	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	
	glBindVertexArray(0);
}