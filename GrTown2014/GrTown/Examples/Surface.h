#pragma once

#include "../GrObject.H"
#include "../DrawingState.H"
#include <glm/glm.hpp>

class Surface : public GrObject {
public:
  Surface(glm::vec3 t, glm::vec3 s, std::vector<glm::vec3> points, int divs, char* vert, char* frag);
  Color color;
  std::vector<glm::vec3> points;
  std::vector<glm::vec3> normals;
  int divs;
  int shader;
  virtual void draw(DrawingState*);
};

Surface Building1(glm::vec3 t, glm::vec3 s, int divs, char* vert, char* frag);
Surface Fountain(glm::vec3 t, glm::vec3 s, int divs, char* vert, char* frag);
Surface UFO(glm::vec3 t, glm::vec3 s, int divs, char* vert, char* frag);