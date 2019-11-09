#pragma once
#include "ShaderProgram.h"

class GuiShader : public ShaderProgram {
private:
	int transformLocation;
	int textureLocation;

public:
	//using ShaderProgram::ShaderProgram;
	GuiShader();
	void loadTransormMatrix(mat4 matrix);
	void loadTextureMatrix(mat3 matrix);

protected:
	void bindAttributes() override;
	void getAllUniformLocations() override;
};