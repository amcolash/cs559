#pragma once

#include "../GrObject.H"
#include "../DrawingState.H"

struct Part {
public:
  float x, y, z;
  float vX, vY, vZ;
  float size;
  Color c;
  bool active;
  int age, maxAge;
};

class Particle : public GrObject {
public:
  Particle(float x, float y, float z, int num);
  int num;
  std::vector<Part> particleList;
  void init(Part *p);
  virtual void draw(DrawingState*);
};

float randFloat(float min, float max);
int randInt(int min, int max);