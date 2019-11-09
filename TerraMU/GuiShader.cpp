#include "GuiShader.h"

GuiShader::GuiShader() : ShaderProgram("guiVertexShader.txt", "guiFragmentShader.txt") {
	bindAttributes();
	getAllUniformLocations();
}

void GuiShader::bindAttributes() {
	ShaderProgram::bindAttribute(0, "position");
	ShaderProgram::bindAttribute(1, "textureCoords");
}

void GuiShader::getAllUniformLocations() {
	transformLocation = glGetUniformLocation(programID, "transform");
	textureLocation = glGetUniformLocation(programID, "texture");
}

void GuiShader::loadTransormMatrix(mat4 matrix) {
	loadMatrix(transformLocation, matrix);
}

void GuiShader::loadTextureMatrix(mat3 matrix) {
	loadMatrix(textureLocation, matrix);
}