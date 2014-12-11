#include "../GrObject.H"
#include "../DrawingState.H"
#include <glm/glm.hpp>
#include <vector>


class Bird : public GrObject {
public:
	Bird(float x, float y, float z, float r, float g, float b, int ID);
	Color color;
	float count;
	int ID;
	bool triedShader = false;
	int shader;
	virtual void draw(DrawingState*);
};