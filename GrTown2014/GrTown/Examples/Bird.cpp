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
	gluCylinder(quadric, .2, 0, 1, 20, 20);
	gluQuadricDrawStyle(quadric, GLU_FILL);
	gluSphere(quadric, 0.5, 36, 18);
	gluDeleteQuadric(quadric);
	quadric = gluNewQuadric();
	glTranslated(0, 0, -1.1);
	gluSphere(quadric, .7, 20, 20);
	glPopMatrix();
	glPushMatrix();
	//glScaled(1, 1, 1.5);
	glTranslated(0, 0, -3);
	quadric = gluNewQuadric();
	gluCylinder(quadric, .05, .05, 1, 20, 20);
	glRotated(20, 0, 1, 1);
	glTranslated(-.2, 0, 0);
	gluCylinder(quadric, 0.05, .05, 1, 20, 20);
	glTranslated(.2, 0, 0);
	glRotated(-40, 0, 1, 1);
	glTranslated(.2, 0, 0);
	gluCylinder(quadric, 0.05, 0.05, 1, 10, 10);
	glPopMatrix();
	glPushMatrix();

	glPopMatrix();
}