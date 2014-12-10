#include "../GrObject.H"
#include "../Behavior.H"
#include "../GrObject.H"
#include <glm/glm.hpp>

class BirdFly : public Behavior
{
public:
	BirdFly(GrObject* bird, int count, float _u);
	glm::vec3 direct;
	void setMatrix();
	float u;
	void Fly(GrObject* bird, int count);
	void RotateToFace(GrObject* b, glm::vec3 objPos, glm::vec3 lookAt, glm::vec3 Up);
	//virtual void simulateUntil(unsigned long until);
	unsigned long advanceU(unsigned long time);


};