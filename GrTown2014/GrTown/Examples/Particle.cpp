#include "../GrTown_PCH.H"
#include "Particle.h"
#include "../DrawUtils.H"
#include "Utilities/Texture.H"
#include "Utilities/ShaderTools.H"
#include <FL/fl_ask.h>
#include "../GraphicsTownUI.H"

Particle::Particle(float x, float y, float z, float scale)
  : particleList(), scale(scale)
{
  transMatrix(transform, x, y, z);
  num = 0;
}

void Particle::initList(int oldNum, int newNum) {
  particleList.resize(num);
  if (oldNum < newNum) {
    for (int i = oldNum; i < newNum; i++) {
      particleList.push_back(Part());
      initParticle(&particleList[i]);
    }
  }
}

void Particle::initParticle(Part *p) {
  float pMax = 1.0 * scale;
  float pMin = -pMax;

  float vMax = 0.23 * scale;
  float vMin = -vMax;

  p->x = randFloat(pMin, pMax);
  p->y = randFloat(pMin, pMax);
  p->z = randFloat(pMin, pMax);
  p->vX = randFloat(vMin, vMax);
  p->vY = randFloat(vMax, 2 * vMax);
  p->vZ = randFloat(vMin, vMax);
  p->size = randFloat(7.0, 10.0);
  p->age = 0;
  p->active = true;
  p->maxAge = randInt(10, 30);
  p->c = Color(randFloat(0.3, 0.5), randFloat(0.4, 0.7), randFloat(0.5, 1.0), randFloat(0.5, 0.75));
}

void Particle::draw(DrawingState* st) {

  if (st->timeOfDay < 5 || st->timeOfDay >= 13) {
    float a0[] = { .3f, .3f, .3f, .3f };
    glLightfv(GL_LIGHT1, GL_AMBIENT, a0);
    glEnable(GL_LIGHT1);
  }

  if (st->timeOfDay >= 13 && st->timeOfDay <= 20)
    glDisable(GL_LIGHT0);
  
  if (num != st->particles) {
    initList(num, st->particles);
    num = st->particles;
  }
  

  GLint blendSrc;
  GLint blendDst;
  glGetIntegerv(GL_BLEND_SRC_ALPHA, &blendSrc);
  glGetIntegerv(GL_BLEND_DST_ALPHA, &blendDst);

  // Enable blending
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_COLOR, GL_ONE);

  for (int i = 0; i < num; i++) {
    Part *p = &particleList[i];
    if (p->age > p->maxAge)
      initParticle(p);
	
	
    if (st->speedup > 0) {
      p->x += p->vX * st->speedup / 3.0;
      p->y += p->vY  * st->speedup / 3.0;
      p->z += p->vZ  * st->speedup / 3.0;

      p->vY -= 0.05  * st->speedup / (1 / scale * 3.0);
      p->age += 1.0 * st->speedup / 3.0;
      p->c.a -= 0.025  * st->speedup / 3.0;
    }

    glColor4f(p->c.r, p->c.g, p->c.b, p->c.a);
    glPointSize(p->size);

    glBegin(GL_POINTS);
      glVertex3f(p->x, p->y, p->z);
    glEnd();

  }

  glBlendFunc(blendSrc, blendDst);
  glDisable(GL_BLEND);

  glDisable(GL_LIGHT1);
  glEnable(GL_LIGHT0);
}

float randFloat(float min, float max) {
  return min + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (max - min)));
}

int randInt(int min, int max) {
  return min + rand() % (max - min + 1);
}