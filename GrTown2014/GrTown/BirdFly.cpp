#include "BirdFly.h"
#include <glm/glm.hpp>
#include "GrTown_PCH.H"
#include "MMatrix.H"

BirdFly::BirdFly(GrObject* bird, glm::vec3 direction) :
Behavior(bird), direct(direction)
{
	
}
void BirdFly::setMatrix(){
	float x, y, z, dx, dy, dz;

}