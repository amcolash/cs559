#pragma once

#include "../GrObject.H"
#include "../DrawingState.H"
#include <glm/glm.hpp>

const int numParticles = 250;
const int divs = 48;

// Fountain
class Fountain : public GrObject {
public:
  Fountain(glm::vec3 scale);
};

class Ground : public GrObject {
public:
  Ground();
  virtual void draw(DrawingState*);
};

// Simple park put onto a block
class Park : public GrObject {
public:
  Park();
};
class Flag : public GrObject{
public:
	Flag(float x, float y, float z, float r, float g, float b);
	Color color;
	int shader;
	bool triedShader = false;
	virtual void draw(DrawingState*);
};