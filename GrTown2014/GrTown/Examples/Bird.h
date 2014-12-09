#include "../GrObject.H"
#include "../DrawingState.H"
#include <glm/glm.hpp>
#include <vector>


class Bird : public GrObject {
public:
	Bird(float x, float y, float z, float r, float g, float b);
	Color color;
	float count;
	float speed;
	virtual void draw(DrawingState*);
	std::vector<float> rotations;
	DrawingState* ds;
	float getSpeed();
};