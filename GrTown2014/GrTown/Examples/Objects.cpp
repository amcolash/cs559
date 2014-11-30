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

Surface::Surface(float x, float y, float z, float r, float g, float b)
  : color(r, g, b)
{
  transMatrix(transform, x, y, z);
}
void Surface::draw(DrawingState*){
  glPushMatrix();
  //glScaled(1, 1, 1.5);
  glColor4fv(&color.r);
  
  //std::vector<Pt> points = { Pt(x, y, z); 0.0, 0.5, 1.0, 2.0, 3.0, 4.0, 5.0, 7.0, 10.0 };
  std::vector<Point> points = {
    Point(0.0, 9.0, 0.0),
    Point(0.25, 8.93, 0.0),
    Point(0.5, 8.75, 0.0),
    Point(0.75, 8.43, 0.0),
    Point(1.0, 8.0, 0.0),
    Point(1.25, 7.43, 0.0),
    Point(1.5, 6.75, 0.0),
    Point(1.75, 5.93, 0.0),
    Point(2.0, 5.0, 0.0),
    Point(2.25, 3.93, 0.0),
    Point(2.5, 2.75, 0.0),
    Point(2.75, 1.43, 0.0),
    Point(3.0, 0.0, 0.0),
    Point(0.0, 0.0, 0.0)
  };

  float height = 10.0;
  int divs = 10;

  float heightStep = height / points.size();
  float divStep = 360.0 / divs;

  for (float i = 0.0; i <= divs; i++) {
    glRotatef(divStep, 0, 1, 0);
    //glBegin(GL_TRIANGLE_FAN);
    glBegin(GL_LINE_STRIP);
    
    for (int j = 0; j < points.size(); j++) {
      glVertex2f(points[j].x, points[j].y);
      //glVertex2f(points[j])
    }
    
    glEnd();
  }

  glPopMatrix();
}

// $Header: /p/course/cs559-gleicher/private/CVS/GrTown/Examples/Objects.cpp,v 1.6 2009/11/10 22:40:03 gleicher Exp $
