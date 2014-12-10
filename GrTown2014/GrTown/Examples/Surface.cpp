#include "../GrTown_PCH.H"
#include "Surface.h"
#include "../DrawUtils.H"
#include "Utilities/Texture.H"
#include "../MMatrix.H"
#include <FL/fl_ask.h>

#include "Utilities/ShaderTools.H"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>


Surface::Surface(glm::vec3 t, glm::vec3 s, std::vector<glm::vec3> tmpPts, int divs,
  char* vert, char* frag, char* texture, float scale, bool special)
  : divs(divs), points(points), normals(normals), shader(shader), frag(frag), vert(vert),
    texture(texture), special(special), scale(scale)
{
  transMatrix(transform, t[0], t[1], t[2]);
  glm::mat4 tempscale = glm::scale(glm::mat4(1.0f), glm::vec3(s[0], s[1], s[2]));

  // generate points and normals only once

  float divStep = 360.0 / divs;

  for (int i = 0; i <= divs - 1; i++) {
    // Current rotation
    glm::mat4 rotateY1 = glm::rotate(
      tempscale, i * divStep, glm::vec3(0.0f, 1.0f, 0.0f)
    );

    // Rotation for next vertex (step + 1)
    glm::mat4 rotateY2 = glm::rotate(
      tempscale, (i + 1) * divStep, glm::vec3(0.0f, 1.0f, 0.0f)
    );

    glm::vec4 point1, point2;
    // Find current vertex when rotated and next one, compute normal too (to build strip)
    for (int j = 0; j < tmpPts.size(); j++) {
      point1 = glm::vec4(tmpPts[j][0], tmpPts[j][1], 0, 0);
      point1 = rotateY1 * point1;
      point2 = glm::vec4(tmpPts[j][0], tmpPts[j][1], 0, 0);
      point2 = rotateY2 * point2;

      glm::vec3 normal(point2[0] - point1[0], point2[1] - point1[1], point2[2] - point1[2]);

      points.push_back(glm::vec3(point1[0], point1[1], point1[2]));
      normals.push_back(glm::vec3(normal[0], normal[1], normal[2]));
    }
  }

  counter = 0;
}

void Surface::draw(DrawingState* ds){
  
  if (vert != NULL && frag != NULL) {
    if (!triedShader) {
      triedShader = true;
      char* error;
      if (!(shader = loadShader(vert, frag, error))) {
        std::string s = "Can't Load Surface Shader:";
        s += error;
        fl_alert(s.c_str());
      }
    }
  } else if (texture != NULL) {
    fetchTexture(texture, true, true);
    glColor3f(1.0, 1.0, 1.0);
  }
  
  glPushMatrix();

  glColor4fv(&color.r);

  if (shader != 0) {
    glUseProgram(shader);
    /* Lighting */
    GLint timeUniformLocation = glGetUniformLocation(shader, "timeOfDay");
    glUniform1i(timeUniformLocation, ds->timeOfDay);
    GLint ambientUniformLocation = glGetUniformLocation(shader, "ambient");
    glUniform1f(ambientUniformLocation, ds->ambient);
    GLint lightUniformLocation = glGetUniformLocation(shader, "light");
    glUniform4fv(lightUniformLocation, 1, ds->lightPos);
    /* Other Vars */
    GLint speedupUniformLocation = glGetUniformLocation(shader, "speedup");
    glUniform1f(speedupUniformLocation, ds->speedup);
    if (special) {
      counter = fmod((counter + (0.049087 * ds->speedup)), 3.14159);
      GLint rotationUniformLocation = glGetUniformLocation(shader, "counter");
      glUniform1f(speedupUniformLocation, counter);
    }
  }

  int perDiv = points.size() / divs;
  int total = points.size();

  for (int i = 0; i <= divs - 1; i++) {

    glBegin(GL_TRIANGLE_STRIP);

    int debug = 0;

    // Build triangle strip from computed verticies and use computed normals
    for (int j = i * perDiv; j < (i + 1) * perDiv; j++) {
      glNormal3f(normals[j][0], normals[j][1], normals[j][2]);

      if (texture != NULL) {
        float s = ( (float) (j - (i * perDiv) ) / (float) (perDiv - 1)) * scale;
        float t = ( (float) (i + 1) / (float) (divs)) * scale;
        glTexCoord2f(s, t);
      }

      glVertex3f(points[(j + perDiv) % total][0], points[(j + perDiv) % total][1], points[(j + perDiv) % total][2]);
      
      if (texture != NULL) {
        float s = ((float)(j - (i * perDiv)) / (float)(perDiv - 1)) * scale;
        float t = ((float)i / (float)(divs)) * scale;
        glTexCoord2f(s, t);
      }

      glVertex3f(points[j][0], points[j][1], points[j][2]);
    }

    glEnd();
  }
  
  glUseProgram(0);
  glBindTexture(GL_TEXTURE_2D, 0);

  glPopMatrix();
}