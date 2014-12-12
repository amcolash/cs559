#pragma once

#include "../GrObject.H"
#include "../DrawingState.H"

struct Part {
public:
  float x, y, z;
  float vX, vY, vZ;
  float size, age;
  Color c;
  bool active;
  int maxAge;
};

class Particle : public GrObject {
public:
  Particle(float x, float y, float z, float scale);
  int num;
  float scale;
  std::vector<Part> particleList;
  int shader;
  bool triedShader = false;
  void initList(int oldNum, int newNum);
  void initParticle(Part *p);
  virtual void draw(DrawingState*);
};

float randFloat(float min, float max);
int randInt(int min, int max);