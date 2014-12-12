// Adam Sperling
// The implementation of the a6_GL_window
// All OpenGL stuff is in here

#include "a6_GL_window.h"
#include <FL/glu.H>
#include <FL/glut.H>
#include <glm\glm.hpp>
#include <vector>


a6_GL_window::a6_GL_window(int x, int y, int w, int h, const char * name) : Fl_Gl_Window(x, y, w, h, name) {
	firstDraw = true;
	displayListHandle = -1; 
	mode(FL_RGB | FL_DOUBLE | FL_STENCIL | FL_ALPHA);
}

void a6_GL_window::rotate_x(int theta) {
	this->angle_x = theta;
}

void a6_GL_window::rotate_y(int theta) {
	this->angle_y = theta;
}

void a6_GL_window::rotate_z(int theta) {
	this->angle_z = theta;
}

void a6_GL_window::setDrawTri() {
	lightsOff();
	draw_tri = true;
	draw_cu = false;
	draw_duck = false;
	draw_balloon = false;
}

void a6_GL_window::setDrawCube() {
	lightsOff();
	draw_tri = false;
	draw_cu = true;
	draw_duck = false;
	draw_balloon = false;
}

void a6_GL_window::setDrawDuck() {
	lightsOn();
	draw_tri = false;
	draw_cu = false;
	draw_duck = true;
	draw_balloon = false;
}

void a6_GL_window::setDrawBalloon() {
	lightsOn();
	draw_tri = false;
	draw_cu = false;
	draw_duck = false;
	draw_balloon = true;
}


void a6_GL_window::initGL() {
	glEnable(GL_DEPTH_TEST);
	glClearColor(0, 0, 0, 0);
}

void a6_GL_window::initTransforms() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	// does this function look familiar?
	gluPerspective(45, w() / h(), 1, 10); // comment this line and uncomment the next line. what happens?
	//glOrtho(-2, 2, -2, 2, 1, 10);
	glViewport(0, 0, w(), h());
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslated(0, 0, -5);
}


void a6_GL_window::draw() {
	if (firstDraw) {
		initGL();
		firstDraw = false;
		draw_tri = true;
		draw_cu = false;
	}

	initTransforms();
	rotate(angle_x, angle_y, angle_z);

	if (draw_tri) {
		drawTriangle();
	}
	else if (draw_cu) {
		drawCube();
		drawTriangle();
		drawDuck();
		drawBalloon();
	}
	else if (draw_duck) {
		drawDuck();
	}
	else if (draw_balloon) {
		drawBalloon();
	}
	
}

void a6_GL_window::rotate(int x, int y, int z) {
	glRotated(x, 1, 0, 0);
	glRotated(y, 0, 1, 0);
	glRotated(z, 0, 0, 1);
}

void a6_GL_window::drawTriangle() {


	glBegin(GL_TRIANGLES);
	glColor3d(255, 0, 0);
	glVertex2d(-1, -1);
	glColor3d(0, 255, 0);
	glVertex2d(1, -1);
	glColor3d(0, 0, 255);
	glVertex2d(0, 1);
	glEnd();
}

void a6_GL_window::drawCube() {



	glBegin(GL_QUADS);
	// front
	glColor3f(1, 0, 0);
	glVertex3f(-1, 1, 1);
	glVertex3f(-1, -1, 1);
	glVertex3f(1, -1, 1);
	glVertex3f(1, 1, 1);

	// back
	glColor3f(0, 1, 0);
	glVertex3f(-1, 1, -1);
	glVertex3f(1, 1, -1);
	glVertex3f(1, -1, -1);
	glVertex3f(-1, -1, -1);

	// top
	glColor3f(0, 0, 1);
	glVertex3f(-1, 1, -1);
	glVertex3f(-1, 1, 1);
	glVertex3f(1, 1, 1);
	glVertex3f(1, 1, -1);

	// bottom
	glColor3f(1, 1, 0);
	glVertex3f(-1, -1, -1);
	glVertex3f(1, -1, -1);
	glVertex3f(1, -1, 1);
	glVertex3f(-1, -1, 1);

	// left
	glColor3f(0, 1, 1);
	glVertex3f(-1, 1, -1);
	glVertex3f(-1, -1, -1);
	glVertex3f(-1, -1, 1);
	glVertex3f(-1, 1, 1);

	// right
	glColor3f(1, 0, 1);
	glVertex3f(1, 1, 1);
	glVertex3f(1, -1, 1);
	glVertex3f(1, -1, -1);
	glVertex3f(1, 1, -1);
	glEnd();
}


//The duck and balloon are both from my own 559 project (fall 2012)
// The duck is drawn using a GL Display List
static GLUquadric * q = gluNewQuadric();
void a6_GL_window::drawDuck() {

	//set up material parameters
	//numbers from http://devernay.free.fr/cours/opengl/materials.html
	//
	//yellow plastic
	GLfloat material_ambient[] = { 0.0f, 0.0f, 0.0f, 1.0f };
	GLfloat material_diffuse[] = { .5f, .5f, 0.0f, 1.0f };
	GLfloat material_specular[] = { .6f, .6f, .5f, 1.0f };
	GLfloat material_shininess[] = { .25f * 128.0f };

	//yellow rubber
	//GLfloat material_ambient[] = {.05, .05, 0, 1};
	//GLfloat material_diffuse[] = { .5, .5, .4, 1 };
	//GLfloat material_specular[] = { .7, .7, .04, 1 };
	//GLfloat material_shininess[] = { .078125 * 128 };
	glMaterialfv(GL_FRONT, GL_AMBIENT, material_ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, material_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, material_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, material_shininess);

	//set the color of the body here, but not the eyes or beak
	glColor3d(1, 1, 0);
	if (this->displayListHandle == GLuint(-1)) {
		this->displayListHandle = glGenLists(1);
		glNewList(this->displayListHandle, GL_COMPILE);

		glPushMatrix();
		if (q) {
			// draw the body

			glPushMatrix();
			glScaled(1, .7, 1.2);

			gluSphere(q, 1, 100, 100);
			glPopMatrix();

			// draw the head
			glPushMatrix();
			glScaled(.4, .4, .4);
			glTranslated(0, 1.8, 2.2);
			gluSphere(q, 1, 100, 100);
			glPopMatrix();

			// draw the wings
			glPushMatrix();
			glScaled(.3, .4, .75);
			glTranslated(2.9, 0, 0);
			gluSphere(q, 1, 100, 100);
			glPopMatrix();

			glPushMatrix();
			glScaled(.3, .4, .75);
			glTranslated(-2.9, 0, 0);
			gluSphere(q, 1, 100, 100);
			glPopMatrix();

			//draw a tail
			glPushMatrix();
			glScaled(.5, .3, .5);
			glTranslated(0, .8, -1.8);
			glRotated(-145, 1, 0, 0);
			gluCylinder(q, 1, 0, 1, 100, 100);
			glPopMatrix();

			// draw the eyes
			glPushMatrix();
			glScaled(.1, .1, .1);
			glColor3d(1, 1, 1);
			glTranslated(2, 10, 11.3);
			gluSphere(q, 1, 100, 100);
			glPopMatrix();

			glPushMatrix();
			glScaled(.1, .1, .1);
			glColor3d(1, 1, 1);
			glTranslated(-2, 10, 11.3);
			gluSphere(q, 1, 100, 100);
			glPopMatrix();

			// blue pupils
			glPushMatrix();
			glScaled(.05, .05, .05);
			glColor3d(0, 0, 1);
			glTranslated(4, 20, 24);
			gluSphere(q, 1, 100, 100);
			glPopMatrix();

			glPushMatrix();
			glScaled(.05, .05, .05);
			glColor3d(0, 0, 1);
			glTranslated(-4, 20, 24);
			gluSphere(q, 1, 100, 100);
			glPopMatrix();

			// draw the beak
			glPushMatrix();
			glScaled(.25, .1, .5);
			glColor3d(1, .5, 0);
			glTranslated(0, 7.5, 2.35);
			gluCylinder(q, 1, 0, 1, 100, 100);
			glPopMatrix();

			glPopMatrix();
		} //end if q

		else {
			exit(1); // should never happen
		}

		glEndList();
	} // end if displayList == -1


	glCallList(this->displayListHandle);

}


//This balloon is drawn using an advanced technique called vertex arrays
// don't worry if you don't understand all of this code - that's why I left the comments in
using namespace std;
using namespace glm;
std::vector<vec3> a6_GL_window::va_vertices;
std::vector<ivec3> a6_GL_window::va_indices;
std::vector<vec3> a6_GL_window::va_normals;

const float PI = 3.14159265f;
void a6_GL_window::drawBalloon() {

	//Source: https://uwmad.courses.wisconsin.edu/d2l/lms/content/viewer/main_frame.d2l?tId=11011796&ou=1821693
	//Example vertex array code used to figure out vertex arrays

	//GL_CULL_FACE is left enabled as disabling it leads to bizarre ripple effects
	glDisable(GL_COLOR_MATERIAL); //disabled, so that the color will be determined by the material specified below
	GLboolean blendAlreadyEnabled;
	glGetBooleanv(GL_BLEND, &blendAlreadyEnabled); //checks if blending is already enable, to later restore the previous state
	if (blendAlreadyEnabled) glBlendFunc(GL_ONE, GL_ONE);
	else glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND);

	//Unique color and alpha values for each component of light result in giving a unique look to the
	//model. These values were chosen to simulate the appearance of a shiny, semi-transparent balloon
	GLfloat material_ambient_gold[] = { 0.25f, 0.20f, 0.08f, 0.8f };//{ 0.7f, 0.6f, 0.6f, 0.7f};
	GLfloat material_diffuse_gold[] = { 0.75f, 0.61f, 0.22f, 0.8f };//{ 0.7f, 0.6f, 0.6f, 0.7f};
	GLfloat material_specular_gold[] = { 0.63f, 0.56f, 0.37f, 0.7f };
	GLfloat material_shininess_gold[] = { .4f * 128.0f };

	GLfloat material_ambient_silver[] = { 0.7f, 0.6f, 0.6f, 0.7f };
	GLfloat material_diffuse_silver[] = { 0.7f, 0.6f, 0.6f, 0.7f };
	GLfloat material_specular_silver[] = { 0.7f, 0.6f, 0.6f, 0.7f };
	GLfloat material_shininess_silver[] = { .25f * 128.0f };

	GLfloat material_ambient_red[] = { 1.0f, 0.1f, 0.1f, 0.8f };//{ 0.7f, 0.6f, 0.6f, 0.7f};
	GLfloat material_diffuse_red[] = { 1.0f, 0.1f, 0.1f, 0.8f };//{ 0.7f, 0.6f, 0.6f, 0.7f};
	GLfloat material_specular_red[] = { 0.7f, 0.6f, 0.6f, 0.7f };
	GLfloat material_shininess_red[] = { .25f * 128.0f };

	GLfloat material_ambient_green[] = { 0.1f, 1.0f, 0.1f, 0.8f };//{ 0.7f, 0.6f, 0.6f, 0.7f};
	GLfloat material_diffuse_green[] = { 0.1f, 1.0f, 0.1f, 0.8f };//{ 0.7f, 0.6f, 0.6f, 0.7f};
	GLfloat material_specular_green[] = { 0.6f, 0.7f, 0.6f, 0.7f };
	GLfloat material_shininess_green[] = { .25f * 128.0f };

	GLfloat material_ambient_blue[] = { 0.1f, 0.1f, 1.0f, 0.8f };//{ 0.7f, 0.6f, 0.6f, 0.7f};
	GLfloat material_diffuse_blue[] = { 0.1f, 0.1f, 1.0f, 0.8f };//{ 0.7f, 0.6f, 0.6f, 0.7f};
	GLfloat material_specular_blue[] = { 0.6f, 0.6f, 0.7f, 0.7f };
	GLfloat material_shininess_blue[] = { .25f * 128.0f };

	
		glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, material_ambient_red);
		glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, material_diffuse_red);
		glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, material_specular_red);
		glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, material_shininess_red);


	if (va_vertices.size() == 0) {

		GLfloat r;
		GLfloat o;
		GLfloat p;
		r = 1.0;

		//The balloon is drawn by specifying individual vertexes. In this case, the top half of the
		//balloon is drawn by loops that draw verticle stacks of circles of non-linear radius which are connected to form
		//a balloon shape. In this case, the circles are made by taking polar coordinates and converting
		//them back into cartesian.

		//The balloon's unique bottom shape is due to an equation which varies the distance of the stack of circles
		//from the center of the shape in a non-linear form.

		GLfloat omegaPoints = 91.0f;
		GLfloat omegaIncrement = 180 / (omegaPoints - 1);

		//The value to increment between the points is determined by the desired space to fill over the number
		//of points. In this case, a 1 is subtracted from the points, because 0 is counted as the first point
		//and the loop runs until the value equals the desired size.

		GLfloat phiPoints = 120.0f;
		GLfloat phiIncrement = 360 / phiPoints;

		//Source: http://electron9.phys.utk.edu/vectors/3dcoordinates.htm used to translate polar to 
		for (o = (GLfloat)0; o <= (GLfloat)180; o += omegaIncrement) {
			for (p = (GLfloat)0; p <(GLfloat)360; p += phiIncrement) {

				if (o < .5 * 180) r = (GLfloat)1;
				else r = (GLfloat)(1 + (1 - cos((o - 90)*(PI / 180))) / 2);

				this->va_vertices.push_back(glm::vec3((r * sin(o*(PI / 180))* cos(p*(PI / 180))),
					(r * cos(o*(PI / 180))), (r * sin(o*(PI / 180))* sin(p*(PI / 180)))));
			}
		}

		GLfloat height;
		GLfloat angle;
		r = 0.0;
		GLfloat heightPoints = 6.0;
		GLfloat heightIncrement = 0.1f / (heightPoints - 1);

		//The value to increment between the points is determined by the desired space to fill over the number
		//of points. In this case, a 1 is subtracted from the points, because 0 is counted as the first point
		//and the loop runs until the value equals the desired size.

		GLfloat anglePoints = 18.0;
		GLfloat angleIncrement = 360 / anglePoints;

		GLfloat radialIncreasePerHeightIncrement = 0.02f;

		//A small cone is created on the bottom of the balloon by drawing a stack of circles of a linear radius.
		//Source: http://electron9.phys.utk.edu/vectors/2dcoordinates.htm used to translate polar to cartesian 2D
		for (height = (GLfloat)-1.45f; height >= (GLfloat)-1.55f; height -= heightIncrement) {
			for (angle = 0; angle < 360; angle += angleIncrement){
				this->va_vertices.push_back(glm::vec3((r * cos(angle*(PI / 180))), height, (r * sin(angle*(PI / 180)))));
			}
			r += radialIncreasePerHeightIncrement;
		}

		r = 1; //the radius is reset to 1 as it is used later

		//The vertices are then grouped into triangles and have their normals calculated by normalizing 
		//the result of taking the cross-product between the two sides of every triangle that the vertex is involved in
		//and summing them. 

		GLfloat a;
		GLfloat aMax = (omegaPoints - 1) * phiPoints;
		//Iterates through the loop and connects the vertices into triangular shapes that blur together into the final shape
		//the max index of the loop does not include the last row of points as each row constructs triangles with the row
		//beneath it and thus the last row does not need to construct triangles
		for (a = 0; a < aMax; a++) {
			//the last vertex in a row is unique as the point considered next to it is actually the first point in the row
			if (((int)a % (int)phiPoints) != ((int)phiPoints - 1)) {
				this->va_indices.push_back(glm::ivec3(a, a + phiPoints + 1, a + phiPoints));
				this->va_indices.push_back(glm::ivec3(a, a + 1, a + phiPoints + 1));
			}
			else {
				this->va_indices.push_back(glm::ivec3(a, a + 1, a + phiPoints));
				this->va_indices.push_back(glm::ivec3(a, a - phiPoints + 1, a + 1));
			}
			//the top row of normals are easily predicted due to the shape of the balloon, the rest are calculated
			if (a < phiPoints) {
				this->va_normals.push_back(glm::vec3(0, 1, 0));
			}
			else {

				//Source: http://glm.g-truc.net/code.html used to figure our normal calculations

				glm::vec3 one;
				glm::vec3 two;
				glm::vec3 three;
				glm::vec3 four;
				glm::vec3 five;
				glm::vec3 six;

				//get all points starting at point directly above and going clockwise
				one = va_vertices[GLuint(a - phiPoints)];
				//points at the end of the row must wrap around the array to find their neighbor points
				if (((int)a % (int)phiPoints) != ((int)phiPoints - 1)) {
					two = va_vertices[GLuint(a + 1)];
					three = va_vertices[GLuint(a + phiPoints + 1)];
				}
				else {
					two = va_vertices[GLuint(a - phiPoints + 1)];
					three = va_vertices[GLuint(a + 1)];
				}
				four = va_vertices[GLuint(a + phiPoints)];
				//points at the end of the row must wrap around the array to find their neighbor points
				if (((int)a % (int)phiPoints) != 0) {
					five = va_vertices[GLuint(a - 1)];
					six = va_vertices[GLuint(a - phiPoints - 1)];
				}
				else {
					five = va_vertices[GLuint(a + phiPoints - 1)];
					six = va_vertices[GLuint(a - 1)];
				}

				vec3 sum = glm::cross(one - va_vertices[GLuint(a)], two - va_vertices[GLuint(a)]);
				sum += glm::cross(two - va_vertices[GLuint(a)], three - va_vertices[GLuint(a)]);
				sum += glm::cross(three - va_vertices[GLuint(a)], four - va_vertices[GLuint(a)]);
				sum += glm::cross(four - va_vertices[GLuint(a)], five - va_vertices[GLuint(a)]);
				sum += glm::cross(five - va_vertices[GLuint(a)], six - va_vertices[GLuint(a)]);
				sum += glm::cross(six - va_vertices[GLuint(a)], one - va_vertices[GLuint(a)]);
				this->va_normals.push_back(glm::normalize(sum));
			}
		}

		//The preceding loop did not address the final row of normals as it did not need to loop through the final
		//row to specify vertices. This loop fills in the rest of the normals as they are easily predicted due to the
		//shape of the balloon.
		for (a = 0; a < phiPoints; ++a) {
			this->va_normals.push_back(glm::vec3(0, -1, 0));
		}

		//The normals and indices of the cone beneath the balloon are calculated the same way.
		for (a = 0; a < anglePoints; ++a) {
			this->va_normals.push_back(glm::vec3(0, 1, 0));
		}

		GLfloat initial = omegaPoints * phiPoints;
		GLfloat b = initial;
		GLfloat bMax = b + (heightPoints - 1) * anglePoints;

		for (b = omegaPoints * phiPoints; b < bMax; b++) {
			if (((int)(b - initial) % (int)anglePoints) != ((int)anglePoints - 1)) {
				this->va_indices.push_back(glm::ivec3(b, b + anglePoints + 1, b + anglePoints));
				this->va_indices.push_back(glm::ivec3(b, b + 1, b + anglePoints + 1));
			}
			else {
				this->va_indices.push_back(glm::ivec3(b, b + 1, b + anglePoints));
				this->va_indices.push_back(glm::ivec3(b, b - anglePoints + 1, b + 1));
			}

			if (b < initial + anglePoints) {
				this->va_normals.push_back(glm::vec3(0, 1, 0));
			}
			else {
				glm::vec3 one;
				glm::vec3 two;
				glm::vec3 three;
				glm::vec3 four;
				glm::vec3 five;
				glm::vec3 six;

				//get all points starting at point directly above and going clockwise
				one = va_vertices[GLuint(b - anglePoints)];
				if (((int)(b - initial) % (int)anglePoints) != ((int)anglePoints - 1)) {
					two = va_vertices[GLuint(b + 1)];
					three = va_vertices[GLuint(b + anglePoints + 1)];
				}
				else {
					two = va_vertices[GLuint(b - anglePoints + 1)];
					three = va_vertices[GLuint(b + 1)];
				}
				four = va_vertices[GLuint(b + anglePoints)];
				if (((int)(b - initial) % (int)anglePoints) != 0) {
					five = va_vertices[GLuint(b - 1)];
					six = va_vertices[GLuint(b - anglePoints - 1)];
				}
				else {
					five = va_vertices[GLuint(b + anglePoints - 1)];
					six = va_vertices[GLuint(b - 1)];
				}

				glm::vec3 sum = glm::cross(one - va_vertices[GLuint(b)], two - va_vertices[GLuint(b)]);
				sum += glm::cross(two - va_vertices[GLuint(b)], three - va_vertices[GLuint(b)]);
				sum += glm::cross(three - va_vertices[GLuint(b)], four - va_vertices[GLuint(b)]);
				sum += glm::cross(four - va_vertices[GLuint(b)], five - va_vertices[GLuint(b)]);
				sum += glm::cross(five - va_vertices[GLuint(b)], six - va_vertices[GLuint(b)]);
				sum += glm::cross(six - va_vertices[GLuint(b)], one - va_vertices[GLuint(b)]);
				this->va_normals.push_back(glm::normalize(sum));
			}
		}

		for (a = 0; a < anglePoints; ++a) {
			for (angle = 0; angle < 360; angle += angleIncrement) {
				this->va_normals.push_back(glm::normalize(glm::vec3(r*cos(angle *(PI / 180)), 0, r*sin(angle *(PI / 180)))));
			}
		}

	}

	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);

	glVertexPointer(3, GL_FLOAT, 0, &va_vertices[0]);
	glNormalPointer(GL_FLOAT, 0, &va_normals[0]);

	glDrawElements(GL_TRIANGLES, 3 * va_indices.size(), GL_UNSIGNED_INT, &va_indices[0]);

	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);

	glPushMatrix();
	glTranslated(0, -1.55, 0);
	glRotated(90, 1, 0, 0);
	glutSolidTorus((GLdouble) 0.018, (GLdouble) 0.11, (GLint)20, (GLint)20);
	//Source: http://www.nigels.com/glt/doc/class_glut_torus.html
	glPopMatrix();

	glEnable(GL_COLOR_MATERIAL);
	if (!blendAlreadyEnabled){
		glDisable(GL_BLEND);
	}
	else glBlendFunc(GL_ONE, GL_ONE);
}

// ignore this...its only here to make the duck and balloon look good
// we'll cover lighting soon enough
void a6_GL_window::lightsOn() {
	glShadeModel(GL_SMOOTH);

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_NORMALIZE);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glLightModelf(GL_LIGHT_MODEL_TWO_SIDE, 1.0);
	//////set up light position
	GLfloat light_position[] = { 2, 2, 1, 0 };
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
}

void a6_GL_window::lightsOff() {
	glDisable(GL_LIGHTING);
}