#include "StaticShader.h"

void StaticShader::bindAttributes() {
	ShaderProgram::bindAttribute(0, "position");
	ShaderProgram::bindAttribute(1, "textureCoords");
}

void StaticShader::getAllUniformLocations() {

}