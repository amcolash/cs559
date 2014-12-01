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

Surface::Surface(float x, float y, float z, float r, float g, float b, std::vector<glm::vec3> tmpPts, int divs)
  : color(r, g, b), divs(divs), points(points), normals(normals)
{
  transMatrix(transform, x, y, z);

  // generate points and normals only once

  float divStep = 360.0 / divs;

  for (int i = 0; i <= divs - 1; i++) {
    // Current rotation
    glm::mat4 rotateY1 = glm::rotate(
      glm::mat4(1.0f), i * divStep, glm::vec3(0.0f, 1.0f, 0.0f)
    );

    // Rotation for next vertex (step + 1)
    glm::mat4 rotateY2 = glm::rotate(
      glm::mat4(1.0f), (i + 1) * divStep, glm::vec3(0.0f, 1.0f, 0.0f)
    );

    glm::vec4 point1, point2;
    // Find current vertex when rotated and next one, compute normal too (to build strip)
    for (int j = 0; j < tmpPts.size(); j++) {
      point1 = glm::vec4(tmpPts[j][0], tmpPts[j][1], 0, 0);
      point1 = rotateY1 * point1;
      point2 = glm::vec4(tmpPts[j][0], tmpPts[j][1], 0, 0);
      point2 = rotateY2 * point2;

      glm::vec3 normal(point2[0] - point1[0], point2[1] - point1[1], point2[2] - point1[2]);

      points.push_back(glm::vec3(point1[0], point1[1], point1[2]));
      normals.push_back(glm::vec3(normal[0], normal[1], normal[2]));
    }
  }
}

void Surface::draw(DrawingState*){
  glPushMatrix();

  // Using shader for now, instead of specific color
  glUseProgram(shadedCubeShader);
  //glColor4fv(&color.r);

  glScalef(0.75, 1.25, 0.75);

  int perDiv = points.size() / divs;
  int total = points.size();

  for (int i = 0; i <= divs - 1; i++) {
    
    glBegin(GL_TRIANGLE_STRIP);

    // Build triangle strip from computed verticies and use computed normals
    for (int j = i * perDiv; j < (i + 1) * perDiv; j++) {
      glNormal3f(normals[j][0], normals[j][1], normals[j][2]);
      glVertex3f(points[j][0], points[j][1], points[j][2]);
      glVertex3f(points[(j + perDiv) % total][0], points[(j + perDiv) % total][1], points[(j + perDiv) % total][2]);
    }
    
    glEnd();
  }

  glUseProgram(0);

  glPopMatrix();
}

// $Header: /p/course/cs559-gleicher/private/CVS/GrTown/Examples/Objects.cpp,v 1.6 2009/11/10 22:40:03 gleicher Exp $
