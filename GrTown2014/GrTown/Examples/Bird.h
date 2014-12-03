#pragma once

#include "../GrObject.H"
#include "../DrawingState.H"
#include <glm/glm.hpp>

class Bird : public GrObject {
public:
	Bird(float x, float y, float z, float r, float g, float b);
	Color color;
	virtual void draw(DrawingState*);
};