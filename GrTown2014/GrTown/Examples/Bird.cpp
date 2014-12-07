#include "Bird.h"
#include "Utilities/Texture.H"
#include <glm/gtc/matrix_transform.hpp>
#include <math.h>
#include <glm/glm.hpp>


Bird::Bird(float x, float y, float z, float r, float g, float b)
	: color(r, g, b), count(count)
{
	count = 0;
	transMatrix(transform, x, y, z);
	for (int i = 0; i < 3; i++){
		rotations.push_back(0);
	}
}

void Bird::draw(DrawingState* state){
	glPushMatrix();
	glBegin(GL_QUADS);
	glVertex3f(0, 0, 100);
	glPushMatrix();
	//glRotated(-45, 0, 1, 0);
	glPushMatrix();
	glScaled(1, 1, 1.5);
	glColor4fv(&color.r);
	GLUquadricObj *quadric = gluNewQuadric();

	//Draw beak
	gluCylinder(quadric, .2, 0, 1, 20, 20);
	gluQuadricDrawStyle(quadric, GLU_FILL);

	//Draw head
	gluSphere(quadric, 0.5, 36, 18);
	gluDeleteQuadric(quadric);
	quadric = gluNewQuadric();
	glTranslated(0, 0, -1.1);

	//Draw body
	gluSphere(quadric, .7, 20, 20);
	glPopMatrix();


	glPushMatrix();

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


	//Draw left wing
	glPushMatrix();

	glRotated(10*sin(count*state->speedup), 0, 0, 1);
	glTranslated(.2, 0, -2.7);
	
	glBegin(GL_TRIANGLE_FAN);

	glVertex3f(0, 0, 1);
	glVertex3f(0, 0, 2);
	glVertex3f(2, 0, 2);
	glVertex3f(1, 0, 1);
	glVertex3f(0, 0, .5);
	glVertex3f(.5, 0, 1);
	glVertex3f(.5, -.05, 1);
	glVertex3f(0, -.05, .5);
	glVertex3f(1, -.05, 1);
	glVertex3f(2, -.05, 2);
	glVertex3f(0, -.05, 2);
	glVertex3f(0, -.05, 1);
	glEnd();

	glBegin(GL_QUADS);
	glVertex3f(0, 0, 2);
	glVertex3f(0, -.05, 2);
	glVertex3f(2, -.05, 2);
	glVertex3f(2, 0, 2);
	glVertex3f(2, 0, 2);
	glVertex3f(2, -0.05, 2);
	glVertex3f(1, -0.05, 1);
	glVertex3f(1, 0, 1);
	glVertex3f(1, 0, 1);
	glVertex3f(1, -.05, 1);
	glVertex3f(0, -.05, 1);
	glVertex3f(0, 0, 1);
	glEnd();
	
	glPopMatrix();


	//Draw right wing
	glPushMatrix();

	glRotated(-10 * sin(count*state->speedup), 0, 0, 1);
	glTranslated(.2, 0, -2.7);
	glBegin(GL_TRIANGLE_FAN);
	glVertex3f(-.3, -.05, 1);
	glVertex3f(-.3, -.05, 2);
	glVertex3f(-2.3, -.05, 2);
	glVertex3f(-1.3, -.05, 1);
	glVertex3f(-.3, -.05, .5);
	glVertex3f(-.8, -.05, 1);
	glVertex3f(-.8, 0, 1);
	glVertex3f(-.3, 0, .5);
	glVertex3f(-1.3, 0, 1);
	glVertex3f(-2.3, 0, 2);
	glVertex3f(-.3, 0, 2);
	glVertex3f(-.3, 0, 1);
	glEnd();
	glBegin(GL_QUADS);
	glVertex3f(-2.3, 0, 2);
	glVertex3f(-2.3, -.05, 2);
	glVertex3f(-.3, -.05, 2);
	glVertex3f(-.3, 0, 2);
	glVertex3f(-1.3, 0, 1);
	glVertex3f(-1.3, -.05, 1);
	glVertex3f(-2.3, -.05, 2);
	glVertex3f(-2.3, 0, 2);
	glVertex3f(-.3, 0, 1);
	glVertex3f(-.3, -.05, 1);
	glVertex3f(-1.3, -.05, 1);
	glVertex3f(-1.3, 0, 1);
	glEnd();
	glPopMatrix();
	glPopMatrix();
	glPopMatrix();

	//Increment rotation of wing
	count += .4;
}