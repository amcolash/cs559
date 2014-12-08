#include "Park.h"
#include "Surface.h"
#include "Particle.h"
#include <time.h>

Fountain::Fountain() {
  // Add a fountain
  Surface* s = new Surface(glm::vec3(0, 0, 0), glm::vec3(0.75, 1.0, 0.75), S_FOUNTAIN, divs,
    "ShadedCubeTest.vert", "ShadedCubeTest.frag", false);
  add(s);

  // Add water to fountain
  Surface* w = new Surface(glm::vec3(0, 0, 0), glm::vec3(0.75, 1.0, 0.75), S_WATER, divs,
    "Fountain.vert", "Fountain.frag", false);
  add(w);

  // Seed rng and add fountain particles
  srand(static_cast <unsigned> (time(0)));
  Particle* p = new Particle(0, 8, 0, numParticles);
  add(p);
}

Park::Park() {
  add(new Fountain(), 0, 0, 0);
  add(new Fountain(), 450, 0, 00);
  add(new Fountain(), 450, 0, 150);
  add(new Fountain(), 0, 0, 150);
  add(new Fountain(), 225, 0, 75);
}