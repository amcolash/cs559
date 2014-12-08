#pragma once

#include "../GrObject.H"
#include "../DrawingState.H"

const int numParticles = 250;
const int divs = 48;

// Fountain
class Fountain : public GrObject {
public:
  Fountain();
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