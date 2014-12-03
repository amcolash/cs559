#include "../GrTown_PCH.H"
#include "Particle.h"
#include "../DrawUtils.H"
#include "Utilities/Texture.H"
#include "Utilities/ShaderTools.H"
#include <FL/fl_ask.h>
#include "../GraphicsTownUI.H"

Particle::Particle(float x, float y, float z, int num)
  : num(num), particleList()
{
  transMatrix(transform, x, y, z);

  for (int i = 0; i < num; i++) {
    particleList.push_back(Part());
    init(&particleList[i]);
  }
}

void Particle::init(Part *p) {
  float pMax = 1.0;
  float pMin = -pMax;

  float vMax = 0.2;
  float vMin = -vMax;

  p->x = randFloat(pMin, pMax);
  p->y = randFloat(pMin, pMax);
  p->z = randFloat(pMin, pMax);
  p->vX = randFloat(vMin, vMax);
  p->vY = randFloat(vMax, 2 * vMax);
  p->vZ = randFloat(vMin, vMax);
  p->size = randFloat(7.0, 10.0);
  //p->size = 0.75;
  p->age = 0;
  p->active = true;
  p->maxAge = randInt(10, 30);
  p->c = Color(randFloat(0.3, 0.5), randFloat(0.4, 0.7), randFloat(0.4, 1.0), randFloat(0.5, 1.0));
}

void Particle::draw(DrawingState*){
  
  /*
  if (!triedShader) {
    triedShader = true;
    char* error;
    if (!(shader = loadShader("fountain.vert", "fountain.frag", error))) {
      std::string s = "Can't Load Surface Shader:";
      s += error;
      fl_alert(s.c_str());
    }
  }

  //glUseProgram(shader);
  */

  // Enable blending
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_COLOR, GL_ONE);

  for (int i = 0; i < num; i++) {
    Part *p = &particleList[i];
    if (p->age > p->maxAge)
      init(p);
	
	
    p->x += p->vX;
    p->y += p->vY;
    p->z += p->vZ;
    p->vY -= 0.05;
    p->age++;
    p->c.a -= 0.025;

    glColor4f(p->c.r, p->c.g, p->c.b, p->c.a);
    glPointSize(p->size);

    glBegin(GL_POINTS);
      glVertex3f(p->x, p->y, p->z);
    glEnd();

  }

  glDisable(GL_BLEND);
  //glUseProgram(0);
}

float randFloat(float min, float max) {
  return min + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (max - min)));
}

int randInt(int min, int max) {
  return min + rand() % (max - min + 1);
}