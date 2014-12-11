#include "../GrTown_PCH.H"
#include "Particle.h"
#include "../DrawUtils.H"
#include "Utilities/Texture.H"
#include "Utilities/ShaderTools.H"
#include <FL/fl_ask.h>
#include "../GraphicsTownUI.H"

#include "Park.h"
#include "Surface.h"
#include "Particle.h"
#include <time.h>

GLfloat waveTime = 0.0;
float count = 0.0f;

Fountain::Fountain(glm::vec3 scale) {
  // Add a fountain
  Surface* s = new Surface(glm::vec3(0, 0, 0), glm::vec3(0.75 * scale[0], 1.0 * scale[1], 0.75 * scale[2]), S_FOUNTAIN, divs,
    "ShadedCubeTest.vert", "ShadedCubeTest.frag", NULL, 0.0, false);
  add(s);

  // Add water to fountain
  Surface* w = new Surface(glm::vec3(0, 0, 0), glm::vec3(0.75 * scale[0], 1.0 * scale[1], 0.75 * scale[2]), S_WATER, divs,
    "ShadedCubeTest.vert", "Fountain.frag", NULL, 0.0, false);
  add(w);

  // Seed rng and add fountain particles
  srand(static_cast <unsigned> (time(0)));
  Particle* p = new Particle(0, 8 * scale[1], 0, scale[0]);
  add(p);
}

Ground::Ground() {
}

void Ground::draw(DrawingState* ds) {
  glColor3f(1.0, 1.0, 1.0);
  if (ds->drGrTex)
    fetchTexture("metal.png", true, true);
  else {
    glBindTexture(GL_TEXTURE_2D, 0);
    glColor3f(0.25, 0.7, 0.3);
  }
  
  glNormal3f(0, 1, 0);
  
  glBegin(GL_QUADS);
  glTexCoord2f(0, 0);     glVertex3f(0, 0, 0);
  glTexCoord2f(0, 8);     glVertex3f(0, 0, 230);
  glTexCoord2f(18, 8);     glVertex3f(530, 0, 230);
  glTexCoord2f(18, 0);     glVertex3f(530, 0, 0);
  glEnd();

  glBindTexture(GL_TEXTURE_2D, 0);
}

Park::Park() {
  add(new Ground(), 0, 0, 0);

  add(new Fountain(glm::vec3(5.0, 5.0, 5.0)), 250, 0, 115);  
}

Flag::Flag(float x, float y, float z, float r, float g, float b) :
color(r, g, b), shader(shader)
{
	transMatrix(transform, x, 0, z);
}
void Flag::draw(DrawingState* ds){

	/* Draw flagpole */
	glPushMatrix();
	GLUquadricObj *quadric = gluNewQuadric();
	glColor4fv(&color.r);
	glRotated(-90, 1, 0, 0);
	gluCylinder(quadric, 2, 2, 100, 10, 10);
	glPopMatrix();
	waveTime += .1*ds->speedup;

	if (!triedShader) {
		triedShader = true;
		char* error;
		if (!(shader = loadShader("Flag.vert", "Flag.frag", error))) {
			std::string s = "Can't Load Surface Shader:";
			s += error;
			fl_alert(s.c_str());
		}
	}

	if (shader != 0) {
		glUseProgram(shader);
		GLfloat waveWidth = 2.1, waveHeight = 1.3;
		GLint waveTimeLoc = glGetUniformLocation(shader, "waveTime");
		GLint waveWidthLoc = glGetUniformLocation(shader, "waveWidth");
		GLint waveHeightLoc = glGetUniformLocation(shader, "waveHeight");
		glUniform1f(waveTimeLoc, waveTime);
		glUniform1f(waveWidthLoc, waveWidth);
		glUniform1f(waveHeightLoc, waveHeight);

	}


	/* Draw flag */
	fetchTexture("murica.jpg", true, true);
	glPushMatrix();
	glTranslated(0, 90, 0);
	glRotated(90, 0, 1, 0);
	glBegin(GL_QUADS);
	glVertex3f(0, -20, 0);
	glVertex3f(0, 10, 0);
	glVertex3f(30, 10, 30);
	glVertex3f(30, -20, 30);
	glEnd();

	glBegin(GL_QUADS);
	glVertex3f(30, -20, 30);
	glVertex3f(30, 10, 30);
	glVertex3f(0, 10, 0);
	glVertex3f(0, -20, 0);
	glEnd();

	glPopMatrix();
	glUseProgram(0);



}