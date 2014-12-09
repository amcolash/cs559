#include "GrObject.H"
#include "DrawingState.H"
#include <glm/glm.hpp>
#include <vector>


class Flag : public GrObject {
public:
	Flag(float x, float y, float z, float r, float g, float b);
	Color color;
	int shader;
	bool triedShader = false;
	virtual void draw(DrawingState*);
};