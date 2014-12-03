#include "Bird.h"
#include "Utilities/Texture.H"
#include <glm/gtc/matrix_transform.hpp>

Bird::Bird(float x, float y, float z, float r, float g, float b)
	: color(r, g, b)
{
	transMatrix(transform, x, y, z);
}
void Bird::draw(DrawingState*){
	glPushMatrix();
	glScaled(1, 1, 1.5);
	glColor4fv(&color.r);
	GLUquadricObj *quadric = gluNewQuadric();
	gluCylinder(quadric, .4, .00000, 1, 100, 100);
	gluQuadricDrawStyle(quadric, GLU_FILL);
	gluSphere(quadric, 0.5, 36, 18);
	gluDeleteQuadric(quadric);
	glPopMatrix();
}