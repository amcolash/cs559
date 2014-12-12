#include "../GrTown_PCH.H"
#include "SunMoon.h"
#include "../DrawUtils.H"
#include "Utilities/Texture.H"
#include "../MMatrix.H"
#include <FL/fl_ask.h>

#include "Utilities/ShaderTools.H"

float x, y, z;

Sun::Sun(float tx, float ty, float tz) {
	x = tx;
	y = ty;
	z = tz;
}

static unsigned int sunShader = 0;
static bool triedSunShader = false;

void Sun::draw(DrawingState* ds)
{
  if (!sunShader && !triedSunShader) {
    triedSunShader = true;
    char* error;
    if (!(sunShader = loadShader("Billboard.vert", "Sun.frag", error))) {
      std::string s = "Can't Load Sun Shader:";
      s += error;
      fl_alert(s.c_str());
    }
  }

  float PI = 3.14159;
  float radius = 30.0;

  float arcSize = 1500.0;

  if (ds->timeOfDay > 5 && ds->timeOfDay <= 18) {

    if (sunShader != 0) {
      glUseProgram(sunShader);
      GLint textureUniformLocation = glGetUniformLocation(sunShader, "timeOfDay");
      glUniform1f(textureUniformLocation, ds->timeOfDay + (ds->counter / ds->maxCounter));
    }

		y = arcSize * sin(((ds->timeOfDay / 24.0) + (ds->counter / ds->maxCounter / 24.0)) * (2 * PI) - (PI / 2.0));
		z = arcSize * cos(((ds->timeOfDay / 24.0) + (ds->counter / ds->maxCounter / 24.0)) * (2 * PI) - (PI / 2.0));

    glPushMatrix();
    glTranslatef(x, y, z);

    glBegin(GL_POLYGON);
    for (double i = 0; i < 2 * PI; i += PI / 16) //<-- Change this Value
      glVertex3f(0.0, sin(i) * radius, cos(i) * radius);
    glEnd();

    if (sunShader != 0)
      glUseProgram(0);

    glPopMatrix();

  }

	this->laX = x;
	this->laY = y - 400.0;
	this->laZ = z;
}

Moon::Moon()
{
}

static unsigned int moonShader = 0;
static bool triedMoonShader = false;

void Moon::draw(DrawingState* ds)
{
  if (!moonShader && !triedMoonShader) {
    triedMoonShader = true;
    char* error;
    if (!(moonShader = loadShader("Billboard.vert", "Moon.frag", error))) {
      std::string s = "Can't Load Moon Shader:";
      s += error;
      fl_alert(s.c_str());
    }
  }

  float PI = 3.14159;
  float radius = 50.0;

  float arcSize = 1500.0;

  if (ds->timeOfDay <= 5 || ds->timeOfDay >= 18) {

    if (moonShader != 0) {
      glUseProgram(moonShader);
      GLint widthUniformLocation = glGetUniformLocation(moonShader, "resolution");
      glUniform2f(widthUniformLocation, ds->width, ds->height);
    }
		
		y = arcSize * sin(((ds->timeOfDay / 24.0) + (ds->counter / ds->maxCounter / 24.0)) * (2 * PI) + (PI / 2.0));
		z = arcSize * cos(((ds->timeOfDay / 24.0) + (ds->counter / ds->maxCounter / 24.0)) * (2 * PI) + (PI / 2.0));

		glPushMatrix();
		glTranslatef(x, y, z);

    glBegin(GL_POLYGON);
    for (double i = 0; i < 2 * PI; i += PI / 16) //<-- Change this Value
      glVertex3f(0.0, sin(i) * radius, cos(i) * radius);
    glEnd();

    if (moonShader != 0)
      glUseProgram(0);

    glPopMatrix();

  }
}