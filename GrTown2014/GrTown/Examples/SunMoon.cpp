#include "../GrTown_PCH.H"
#include "SunMoon.h"
#include "../DrawUtils.H"
#include "Utilities/Texture.H"
#include "../MMatrix.H"
#include <FL/fl_ask.h>

#include "Utilities/ShaderTools.H"

Sun::Sun()
{
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

  if (ds->timeOfDay >= 5 && ds->timeOfDay <= 20) {

    if (sunShader != 0) {
      glUseProgram(sunShader);
      GLint textureUniformLocation = glGetUniformLocation(sunShader, "timeOfDay");
      glUniform1i(textureUniformLocation, ds->timeOfDay);
    }

    glPushMatrix();
    glTranslatef(0.0,
      arcSize * sin((ds->timeOfDay / 24.0) * (2 * PI) - (PI / 2.0)),
      arcSize * cos((ds->timeOfDay / 24.0) * (2 * PI) - (PI / 2.0)));

    glBegin(GL_POLYGON);
    for (double i = 0; i < 2 * PI; i += PI / 16) //<-- Change this Value
      glVertex3f(0.0, sin(i) * radius, cos(i) * radius);
    glEnd();

    if (sunShader != 0)
      glUseProgram(0);

    glBindTexture(GL_TEXTURE_2D, 0);

    glPopMatrix();

  }
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

  if (ds->timeOfDay <= 5 || ds->timeOfDay >= 19) {

    if (moonShader != 0) {
      glUseProgram(moonShader);
      GLint textureUniformLocation = glGetUniformLocation(moonShader, "timeOfDay");
      glUniform1i(textureUniformLocation, ds->timeOfDay);
    }

    glPushMatrix();
    glTranslatef(0.0,
      arcSize * sin((ds->timeOfDay / 24.0) * (2 * PI) + (PI / 2.0)),
      arcSize * cos((ds->timeOfDay / 24.0) * (2 * PI) + (PI / 2.0)));

    glBegin(GL_POLYGON);
    for (double i = 0; i < 2 * PI; i += PI / 16) //<-- Change this Value
      glVertex3f(0.0, sin(i) * radius, cos(i) * radius);
    glEnd();

    if (moonShader != 0)
      glUseProgram(0);

    glBindTexture(GL_TEXTURE_2D, 0);

    glPopMatrix();

  }
}