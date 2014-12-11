#pragma once

#include "../GrObject.H"
#include "../DrawingState.H"
#include <glm/glm.hpp>

class Surface : public GrObject {
public:
  Surface(glm::vec3 t, glm::vec3 s, std::vector<glm::vec3> points, int divs, char* vert,
    char* frag, char* texture, float sScale, float tScale, bool special);
  Color color;
  std::vector<glm::vec3> points;
  std::vector<glm::vec3> normals;
  int divs;
  int shader;
  bool triedShader = false;
  char* frag;
  char* vert;
  char* texture;
  float sScale, tScale;
  bool special;
  float x, y, z, vx, vy, vz;
  float counter;
  virtual void draw(DrawingState*);
  float randFloat(float min, float max);
};

// Define some surfaces below to make things easier

// A Building
const std::vector<glm::vec3> S_BUILDING = {
  glm::vec3(0.0, 43.0, 0.0),
  glm::vec3(1.0, 35.0, 0.0),
  glm::vec3(2.0, 34.0, 0.0),
  glm::vec3(3.0, 34.0, 0.0),
  glm::vec3(5.0, 35.0, 0.0),
  glm::vec3(4.0, 32.0, 0.0),
  glm::vec3(3.0, 31.0, 0.0),
  glm::vec3(3.0, 27.0, 0.0),
  glm::vec3(5.0, 26.0, 0.0),
  glm::vec3(5.0, 22.0, 0.0),
  glm::vec3(6.0, 21.0, 0.0),
  glm::vec3(6.0, 15.0, 0.0),
  glm::vec3(7.0, 14.0, 0.0),
  glm::vec3(7.0, 9.0, 0.0),
  glm::vec3(8.0, 5.0, 0.0),
  glm::vec3(9.0, 2.0, 0.0),
  glm::vec3(9.5, 1.0, 0.0),
  glm::vec3(10.0, 0.0, 0.0)
};

// A fountain
const std::vector<glm::vec3> S_FOUNTAIN = {
  glm::vec3(0.0, .70, 0.0),
  glm::vec3(0.0, 7.0, 0.0),
  glm::vec3(1.0, 7.0, 0.0),
  glm::vec3(1.0, 3.0, 0.0),
  glm::vec3(2.0, 3.0, 0.0),
  glm::vec3(2.0, 1.0, 0.0),
  glm::vec3(12.0, 1.0, 0.0),
  glm::vec3(12.0, 2.0, 0.0),
  glm::vec3(13.0, 3.0, 0.0),
  glm::vec3(14.0, 3.0, 0.0),
  glm::vec3(15.0, 2.0, 0.0),
  glm::vec3(15.0, 1.0, 0.0),
  glm::vec3(14.0, 0.0, 0.0),
  glm::vec3(0.0, 0.0, 0.0)
};

// A pool of water for fountain
// A fountain
const std::vector<glm::vec3> S_WATER = {
  glm::vec3(0.0, 2.0, 0.0),
  glm::vec3(14, 2.25, 0.0)
};

// A UFO
/*
const std::vector<glm::vec3> S_UFO = {
  glm::vec3(0.0, 17.0, 0.0),
  glm::vec3(1.0, 17.0, 0.0),
  glm::vec3(1.0, 12.0, 0.0),
  glm::vec3(5.0, 12.0, 0.0),
  glm::vec3(9.0, 11.5, 0.0),
  glm::vec3(14.0, 10.25, 0.0),
  glm::vec3(18.0, 8.25, 0.0),
  glm::vec3(21.0, 6.0, 0.0),
  glm::vec3(22.5, 4.0, 0.0),
  glm::vec3(23.5, 2.0, 0.0),
  glm::vec3(24.0, 0.0, 0.0),
  glm::vec3(20.0, 0.0, 0.0),
  glm::vec3(13.0, 2.0, 0.0),
  glm::vec3(6.0, 2.0, 0.0),
  glm::vec3(0.0, 2.0, 0.0)
};
*/

const std::vector<glm::vec3> S_UFO = {
  glm::vec3(0.0, 17.0, 0.0),
  glm::vec3(1.0, 17.0, 0.0),
  glm::vec3(1.0, 12.0, 0.0),
  glm::vec3(5.0, 12.0, 0.0),
  glm::vec3(9.0, 11.5, 0.0),
  glm::vec3(14.0, 10.25, 0.0),
  glm::vec3(18.0, 8.25, 0.0),
  glm::vec3(21.0, 6.0, 0.0),
  glm::vec3(22.5, 4.0, 0.0),
  glm::vec3(23.5, 2.0, 0.0),
  glm::vec3(0.0, 7.0, 0.0)
};

const std::vector<glm::vec3> S_UFO_BOTTOM = {
  glm::vec3(23.5, 0.0, 0.0),
  glm::vec3(20.0, 0.0, 0.0),
  glm::vec3(13.0, 1.5, 0.0),
  glm::vec3(6.0, 1.85, 0.0),
  glm::vec3(0.0, 2.0, 0.0)
};

// Simple ring
const std::vector<glm::vec3> S_RING = {
  glm::vec3(4.0, 8.0, 0.0),
  glm::vec3(8.0, 8.0, 0.0),
  glm::vec3(14.0, 6.0, 0.0),
  glm::vec3(14.0, 4.0, 0.0),
  glm::vec3(8.0, 2.0, 0.0),
  glm::vec3(4.0, 2.0, 0.0),
  glm::vec3(4.0, 10.0, 0.0),
  glm::vec3(8.0, 10.0, 0.0),
  glm::vec3(16.0, 6.0, 0.0),
  glm::vec3(16.0, 4.0, 0.0),
  glm::vec3(8.0, 0.0, 0.0),
  glm::vec3(4.0, 0.0, 0.0)
};

const std::vector<glm::vec3> S_BIG_HUT = {
	glm::vec3(15.0, 70.0, 0.0),
	glm::vec3(15.0, 0.0, 0.0),
	glm::vec3(1.0, 105.0, 0.0),
	glm::vec3(15.0, 101.0, 0.0),
	glm::vec3(20.0, 97.0, 0.0),
	glm::vec3(23.0, 93.0, 0.0),
	glm::vec3(25.0, 89.0, 0.0),
	glm::vec3(26.0, 85.0, 0.0),
	glm::vec3(25.0, 81.0,0.0),
	glm::vec3(23.0, 77.0,0.0),
	glm::vec3(20.0, 73.0, 0.0),
	glm::vec3(15.0, 69.0, 0.0),
	glm::vec3(1.0, 65.0, 0.0),
	glm::vec3(0.0, 61.0, 0.0)

};