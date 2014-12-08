#include "../GrObject.H"
#include "../Behavior.H"
#include "../GrObject.H"
#include <glm/glm.hpp>

class BirdFly : public Behavior
{
public:
	BirdFly(GrObject* bird, bool last);
	glm::vec3 direct;
	void setMatrix();
	void Fly(GrObject* bird, bool last);
	void RotateToFace(GrObject* b, glm::vec3 objPos, glm::vec3 lookAt, glm::vec3 Up);
};