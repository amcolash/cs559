#include "GrObject.H"
#include "Behavior.H"
#include "GrObject.H"
#include <glm/glm.hpp>

class BirdFly : public Behavior
{
public:
	BirdFly(GrObject* bird, glm::vec3 direction);
	glm::vec3 direct;
	void setMatrix();

};