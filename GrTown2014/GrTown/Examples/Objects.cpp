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

Skybox::Skybox()
{
}

void Skybox::draw(DrawingState* ds) {
  glPushMatrix();

  //glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  //glDisable(GL_DEPTH_TEST);
  //glDisable(GL_BLEND);
  //glDisable(GL_ALPHA_TEST);
  //glDisable(GL_TEXTURE_GEN_S);
  //glDisable(GL_TEXTURE_GEN_T);
  //glDisable(GL_DEPTH_TEST | GL_BLEND | GL_ALPHA_TEST |
	//  GL_TEXTURE_GEN_S | GL_TEXTURE_GEN_T);
  //glDepthMask(GL_FALSE);
  //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

  glColor3f(1.0, 1.0, 1.0);

  fetchTexture("left2.jpg");
  glBegin(GL_QUADS);
  glTexCoord2i(1, 0);
  glVertex3f(-10000, -1000, -10000);
  glTexCoord2i(0, 0);
  glVertex3f(10000, -1000, -10000);
  glTexCoord2i(0, 1);
  glVertex3f(10000, 4000, -10000);
  glTexCoord2i(1, 1);
  glVertex3f(-10000, 4000, -10000);
  glEnd();

  fetchTexture("right.jpg");
  glBegin(GL_QUADS);
  glTexCoord2i(0, 1);
  glVertex3f(-10000, 4000, 10000);
  glTexCoord2i(1, 1);
  glVertex3f(10000, 4000, 10000);
  glTexCoord2i(1, 0);
  glVertex3f(10000, -1000, 10000);
  glTexCoord2i(0, 0);
  glVertex3f(-10000, -1000, 10000);

  glEnd();
  
  fetchTexture("Up.jpg");
  glBegin(GL_QUADS);
  glTexCoord2i(1, 0);
  glVertex3f(10000, 4000, 10000);
  glTexCoord2i(0, 0);
  glVertex3f(-10000, 4000, 10000);
  glTexCoord2i(1, 0);
  glVertex3f(-10000, 4000, -10000);
  glTexCoord2i(1, 1);
  glVertex3f(10000, 4000, -10000);
  glEnd();

  fetchTexture("front.jpg");
  glBegin(GL_QUADS);
  glTexCoord2i(1, 1);
  glVertex3f(10000, 4000, -10000);
  glTexCoord2i(1, 0);
  glVertex3f(10000, -1000, -10000);
  glTexCoord2i(0, 0);
  glVertex3f(10000, -1000, 10000);
  glTexCoord2i(0, 1);
  glVertex3f(10000, 4000, 10000);
  glEnd();

  fetchTexture("back.jpg");
  glBegin(GL_QUADS);
  glTexCoord2i(1, 1);
  glVertex3f(-10000, 4000, 10000);
  glTexCoord2i(1, 0);
  glVertex3f(-10000, -1000, 10000);
  glTexCoord2i(0, 0);
  glVertex3f(-10000, -1000, -10000);
  glTexCoord2i(0, 1);
  glVertex3f(-10000, 4000, -10000);



  glEnd();


  glPopMatrix();
  
 
}


// $Header: /p/course/cs559-gleicher/private/CVS/GrTown/Examples/Objects.cpp,v 1.6 2009/11/10 22:40:03 gleicher Exp $
