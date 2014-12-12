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
  glm::vec3(23.5, 1.0, 0.0),
  glm::vec3(0.0, 7.0, 0.0)
};

const std::vector<glm::vec3> S_UFO_BOTTOM = {
  glm::vec3(23.5, 0.0, 0.0),
  glm::vec3(20.0, 0.0, 0.0),
  glm::vec3(13.0, 1.5, 0.0),
  glm::vec3(6.0, 1.85, 0.0),
  glm::vec3(0.0, 2.0, 0.0)
};

const std::vector<glm::vec3> S_UFO_CONE = {
  glm::vec3(7.0, 260.0, 0.0),
  glm::vec3(25.0, 0.0, 0.0),
};

// Buildings
const std::vector<glm::vec3> S_COOL = {
  glm::vec3(00.0, 88.0, 00.0),
  glm::vec3(1.0, 87.75, 00.0),
  glm::vec3(3.0, 86.5, 00.0),
  glm::vec3(6.0, 77.0, 02.5),
  glm::vec3(9.0, 65.0, 05.0),
  glm::vec3(12.0, 54.0, 10.0),
  glm::vec3(9.0, 43.0, 10.0),
  glm::vec3(6.0, 32.0, 15.0),
  glm::vec3(3.0, 21.0, 15.0),
  glm::vec3(6.0, 15.0, 20.0),
  glm::vec3(9.0, 00.0, 20.0)
};

const std::vector<glm::vec3> S_MUSHROOM = {
	glm::vec3(00.0, 64.0, 00.0),
	glm::vec3(05.0, 62.0, 00.0),
	glm::vec3(08.0, 59.5, 00.0),
	glm::vec3(10.0, 57.0, 02.5),
	glm::vec3(15.0, 42.0, 05.0),
	glm::vec3(16.0, 32.0, 10.0),
	glm::vec3(16.0, 32.0, 00.0),
	glm::vec3(15.0, 30.0, 00.0),
	glm::vec3(10.0, 27.5, 00.0),
	glm::vec3(08.0, 25.0, 02.5),
	glm::vec3(05.0, 10.0, 05.0),
	glm::vec3(00.0, 00.0, 10.0),
};

const std::vector<glm::vec3> S_EGG = {
	glm::vec3(00.0, 63.0, 0.0),
	glm::vec3(05.0, 62.0, 0.0),
	glm::vec3(08.0, 59.5, 0.0),
	glm::vec3(10.0, 57.0, 0.0),
	glm::vec3(13.5, 49.0, 0.0),
	glm::vec3(15.0, 42.0, 0.0),
	glm::vec3(16.0, 32.0, 0.0),
	glm::vec3(15.0, 22.0, 0.0),
	glm::vec3(13.5, 15.0, 0.0),
	glm::vec3(10.0, 07.0, 0.0),
	glm::vec3(08.0, 04.5, 0.0),
	glm::vec3(05.0, 02.0, 0.0),
	glm::vec3(00.0, 01.0, 0.0)
};

const std::vector<glm::vec3> S_BOX = {
	glm::vec3(00.0, 200.0, 0.0),
	glm::vec3(20.0, 200.0, 0.0),
	glm::vec3(20.0, 0.0, 0.0)
};

const std::vector<glm::vec3> S_BIG_HUT = {
	glm::vec3(0.0, 105.0, 0.0),
	glm::vec3(1.0, 105.0, 0.0),
	glm::vec3(15.0, 101.0, 0.0),
	glm::vec3(20.0, 97.0, 0.0),
	glm::vec3(23.0, 93.0, 0.0),
	glm::vec3(25.0, 89.0, 0.0),
	glm::vec3(26.0, 85.0, 0.0),
	glm::vec3(25.0, 81.0, 0.0),
	glm::vec3(23.0, 77.0, 0.0),
	glm::vec3(20.0, 73.0, 0.0),
	glm::vec3(15.0, 69.0, 0.0),
	glm::vec3(1.0, 65.0, 0.0),
	glm::vec3(0.0, 61.0, 0.0),
	glm::vec3(15.0, 70.0, 0.0),
	glm::vec3(15.0, 64.1666667, 0.0),
	glm::vec3(15.0, 58.3333333, 0.0),
	glm::vec3(15.0, 52.5, 0.0),
	glm::vec3(15.0, 46.6666667, 0.0),
	glm::vec3(15.0, 40.8333333, 0.0),
	glm::vec3(15.0, 35.0, 0.0),
	glm::vec3(15.0, 29.1666667, 0.0),
	glm::vec3(15.0, 23.3333333, 0.0),
	glm::vec3(15.0, 17.5, 0.0),
	glm::vec3(15.0, 11.6666667, 0.0),
	glm::vec3(15.0, 5.83333333, 0.0),
	glm::vec3(15.0, 0.0, 0.0)


};
const std::vector<glm::vec3> S_UMBRELLA = {
	glm::vec3(1.0, 40.0, 1.0),
	glm::vec3(10, 30.0, 30.0),
	glm::vec3(1.0, 40.0, 1.0)
	
	//glm::vec3(4.0, 10.0, 13.0)
};
const std::vector<glm::vec3> S_TABLE = {
	glm::vec3(0.0, 10.0, 0.0),
	glm::vec3(20.0, 10.0, 0.0),
	glm::vec3(20.2, 13.0, 0.0),
	glm::vec3(0.0, 13.0, 0.0),
	glm::vec3(20.0, 10.0, 0.0),
	
};

const std::vector<glm::vec3> S_SKYSKPR = {
	glm::vec3(0.0, 150.0, 0.0),
	glm::vec3(20.0, 150.0, 0.0),
	glm::vec3(20.0, 0.0, 0.0)
};