#include "StreamShader.h"
#include "Maths.h"
#include "Camera.h"

StreamShader::StreamShader() : ShaderProgram::ShaderProgram("StreamVertexShader.txt", "StreamFragmentShader.txt") {
	bindAttributes();
	getAllUniformLocations();
}

void StreamShader::bindAttributes() {
	ShaderProgram::bindAttribute(0, "position");
	ShaderProgram::bindAttribute(1, "textureCoords");
}

void StreamShader::getAllUniformLocations() {
	transformLocation = glGetUniformLocation(programID, "transform");
	projectionLocation = glGetUniformLocation(programID, "projection");
	viewLocation = glGetUniformLocation(programID, "view");
	textureLocation = glGetUniformLocation(programID, "texture");
}

void StreamShader::loadTransormMatrix(mat4 matrix) {
	loadMatrix(transformLocation, matrix);
}

void StreamShader::loadProjectionMatrix(mat4 matrix) {
	loadMatrix(projectionLocation, matrix);
}

void StreamShader::loadViewMatrix(Camera* camera) {
	//lookAt(position, aimCoord, upVector);
	loadMatrix(viewLocation, Maths::createViewMatrix(camera));
}

void StreamShader::loadTextureMatrix(mat3 matrix) {
	loadMatrix(textureLocation, matrix);
}