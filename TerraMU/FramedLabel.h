#pragma once
#include "Label.h"
#include "Picture.h"

class FramedLabel : public Label {
protected:
	virtual void prepareForGettingIcons();

public:
	FramedLabel(string text, vec3 position, float rotationX, float rotationY, float rotationZ, float scaleY);

	//virtual void setText(char const text[]);

};