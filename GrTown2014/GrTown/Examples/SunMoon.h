#include "../GrObject.H"
#include "../DrawingState.H"


class Sun : public GrObject {
public:
  Sun();
  virtual void draw(DrawingState*);
};

class Moon : public GrObject {
public:
  Moon();
  virtual void draw(DrawingState*);
};