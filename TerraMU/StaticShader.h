#pragma once
#include "ShaderProgram.h"

class StaticShader : public ShaderProgram {
public:
	StaticShader() : ShaderProgram::ShaderProgram("StaticVertexShader.txt", "StaticFragmentShader.txt") {};

protected:
	void bindAttributes() override;
};