/// GraphicsTown2006 - CS559 Sample Code
// written by Michael Gleicher - originally written Fall, 2000
// updated Fall, 2005
// updated Fall, 2006 - new texture manager, improvements for behaviors

#include "../GrTown_PCH.H"
#include "Objects.H"
#include "../DrawUtils.H"
#include "Utilities/Texture.H"
#include "../MMatrix.H"
#include <FL/fl_ask.h>

#include "Utilities/ShaderTools.H"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

// some very basic classes of objects...
// mainly for debugging
Cube::Cube(float x, float y, float z, float s, 
		   float r, float g, float b)
  : color(r,g,b), size(s)
{
  transMatrix(transform,x,y,z);
}
void Cube::draw(DrawingState*)
{
  glColor4fv(&color.r);
  cube(0,0,0,size);
}

/***********************************************************************/
TestCubes::TestCubes()
{
}

void TestCubes::draw(DrawingState*)
{
  glColor3f(1,0,0);
  cube( 20,0,0, 3);
  cube(-20,0,0, 3);
  cube(0, 20,0, 3);
  cube(0,-20,0, 3);
  cube(0,0, 20, 3);
  cube(0,0,-20, 3);

  glColor3f(1,1,0);
  cube(20,10,20,3);
  glColor3f(0,1,1);
  cube(-20,10,20,3);
  glColor3f(1,0,1);
  cube(-20,10,-20,3);
  glColor3f(1,1,1);
  cube(20,10,-20,3);
}

// some very basic classes of objects...
// mainly for debugging
ShadedCube::ShadedCube(float x, float y, float z, float s, 
					   float r, float g, float b)
  : color(r,g,b), size(s)
{
  transMatrix(transform,x,y,z);
}

// load the shader in the first time the cube draws (since that way we
// know we have a GL context)
// we only try to load it once
static unsigned int shadedCubeShader = 0;
static bool triedCubeShader=false;

void ShadedCube::draw(DrawingState*)
{
	if (!shadedCubeShader && !triedCubeShader) {
		triedCubeShader = true;
		char* error;
		if (!(shadedCubeShader=loadShader("ShadedCubeTest.vert","ShadedCubeTest.frag",error))) {
			std::string s = "Can't Load Cube Shader:";
			s += error;
			fl_alert(s.c_str());
		}
	}

	glUseProgram(shadedCubeShader);
	glColor4fv(&color.r);
	cube(0,0,0,size);
	glUseProgram(0);
}

Bird::Bird(float x, float y, float z, float r, float g, float b)
  : color(r,g,b)
{
	transMatrix(transform,x, y, z);
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

Surface::Surface(float x, float y, float z, float r, float g, float b, std::vector<Point> points, int divs)
  : color(r, g, b), points(points), divs(divs)
{
  transMatrix(transform, x, y, z);
}

void Surface::draw(DrawingState*){
  glPushMatrix();
  //glColor4fv(&color.r);

  float divStep = 360.0 / divs;

  glUseProgram(shadedCubeShader);

  for (int i = 0; i <= divs - 1; i++) {
    
    glBegin(GL_TRIANGLE_STRIP);

    glm::mat4 rotateY1 = glm::rotate(
      glm::mat4(1.0f), i * divStep, glm::vec3(0.0f, 1.0f, 0.0f)
    );

    glm::mat4 rotateY2 = glm::rotate(
      glm::mat4(1.0f), (i + 1) * divStep, glm::vec3(0.0f, 1.0f, 0.0f)
    );

    // Find current vertex when rotated and next one, (to build strip)
    for (int j = 0; j < points.size(); j++) {
      glm::vec4 point(points[j].x, points[j].y, 0, 0);
      point = rotateY1 * point;
      glNormal3f(point[0], point[1], point[2]);
      glVertex3f(point[0], point[1], point[2]);
      
      point = glm::vec4(points[j].x, points[j].y, 0, 0);
      point = rotateY2 * point;
      glNormal3f(point[0], point[1], point[2]);
      glVertex3f(point[0], point[1], point[2]);
    }
    
    glEnd();
  }

  glUseProgram(0);

  glPopMatrix();
}

// $Header: /p/course/cs559-gleicher/private/CVS/GrTown/Examples/Objects.cpp,v 1.6 2009/11/10 22:40:03 gleicher Exp $
