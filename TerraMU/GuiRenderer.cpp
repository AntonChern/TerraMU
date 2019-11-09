#include "GuiRenderer.h"

GuiRenderer::GuiRenderer() : shader(new GuiShader()) {
	quad = EntityFactory::createRawModel();
}

GuiRenderer::~GuiRenderer() {
	delete shader;
}

void GuiRenderer::render(list<GuiElement*> guis) {
	shader->start();
	glBindVertexArray(quad->getVaoID());
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glDisable(GL_DEPTH_TEST);
	for (GuiElement* gui : guis) {

		shader->loadTransormMatrix(Maths::createTransformMatrix(gui->getPosition(),
			gui->getRotationX(), gui->getRotationY(), gui->getRotationZ(), gui->getScale()));

		shader->loadTextureMatrix(gui->getTextureMatrix());

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, gui->getTextureID());
		glDrawElements(GL_TRIANGLES, quad->getVertexCount(), GL_UNSIGNED_INT, 0);

	}
	glEnable(GL_DEPTH_TEST);
	glDisable(GL_BLEND);

	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);

	glBindVertexArray(0);
	shader->stop();
}

void GuiRenderer::cleanUp() {
	shader->cleanUp();
}