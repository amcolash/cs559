#include "../GrObject.H"
#include "../DrawingState.H"

class Sun : public GrObject {
public:
  Sun(float tx, float ty, float tz);
  virtual void draw(DrawingState*);
};

class Moon : public GrObject {
public:
  Moon();
  virtual void draw(DrawingState*);
};