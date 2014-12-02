#include "../GrTown_PCH.H"
#include "Particle.h"
#include "../DrawUtils.H"
#include "Utilities/Texture.H"
#include "Utilities/ShaderTools.H"

#include <time.h>

Particle::Particle(float x, float y, float z, int num)
  : num(num), particleList()
{
  transMatrix(transform, x, y, z);

  for (int i = 0; i < num; i++) {
    particleList.push_back(Part(0.0, 0.0, 0.0, 0.0, -0.1, 0.0));
  }

}

void Particle::draw(DrawingState*){
  glPushMatrix();

  // Using shader for now, instead of specific color
  //glUseProgram(shadedCubeShader);

  glPointSize(40.0);

  glBegin(GL_POINTS);
    glColor3f(1.0, 1.0, 1.0);
    glVertex3f(0.0, 10.0, 0.0);
  glEnd();

  //glUseProgram(0);

  glPopMatrix();
}