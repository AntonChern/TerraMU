#pragma once
#include "RawModel.h"
#include "ModelTexture.h"

class TexturedModel {
private:
	RawModel *rawModel;
	ModelTexture *texture;
public:
	TexturedModel(RawModel *model, ModelTexture *texture) : rawModel(model), texture(texture) {};
	RawModel *getRawModel() { return rawModel; };
	ModelTexture *getTexture() { return texture; };
};

