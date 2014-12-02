#pragma once

#include "../GrObject.H"
#include "../DrawingState.H"

struct Part {
public:
  float x, y, z;
  float vX, vY, vZ;
  Color c;
  bool active;
  int age;

  Part(float initx, float inity, float initz, float initvX, float initvY, float initvZ) {
    x = initx;
    y = inity;
    z = initz;
    vX = initvX;
    vY = initvY;
    vZ = initvZ;

    c = Color(1.0, 1.0, 1.0);
    active = false;
    age = 0;
  }
};

class Particle : public GrObject {
public:
  Particle(float x, float y, float z, int num);
  int num;
  std::vector<Part> particleList;
  virtual void draw(DrawingState*);
};