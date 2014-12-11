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
  char* vert, char* frag, char* texture, float sScale, float tScale, bool special)
  : divs(divs), points(points), normals(normals), shader(shader), frag(frag), vert(vert),
    texture(texture), special(special), sScale(sScale), tScale(tScale)
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

  y = 0;
  x = randFloat(600.0, 1500.0);
  z = randFloat(300.0, 620.0);
  vx = vy = vz = 3.0;

  counter = 0;
}

void Surface::draw(DrawingState* ds){
  
  if (!special || (special && ds->timeOfDay < 5 || ds->timeOfDay >= 19)) {

    glColor4fv(&color.r);

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
    }

    else if (texture != NULL) {
      fetchTexture(texture, true, true);
      glColor3f(1.0, 1.0, 1.0);
    }

    glPushMatrix();

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
        counter += (ds->speedup * 1.0);
        GLint counterUniformLocation = glGetUniformLocation(shader, "counter");
        glUniform1f(counterUniformLocation, counter);
      }
    }

    int perDiv = points.size() / divs;
    int total = points.size();

    if (special) {
      x += (vx * ds->speedup);
      //y += (vy * ds->speedup);
      z += (vz * ds->speedup);
      glTranslatef(x, y, z);

      if (x < 530 || x > 1590) {
        vx *= -1;
      }
      if (z < 0 || z > 690) {
        vz *= -1;
      }

      glPushMatrix();

      if (texture == "metal.png")
        glRotatef(-counter, 0.0, 1.0, 0.0);
      else
        glRotatef(counter, 0.0, 1.0, 0.0);

      glPopMatrix();
    }

    for (int i = 0; i <= divs - 1; i++) {

      glBegin(GL_TRIANGLE_STRIP);

      // Build triangle strip from computed verticies and use computed normals
      for (int j = i * perDiv; j < (i + 1) * perDiv; j++) {
        glNormal3f(normals[j][0], normals[j][1], normals[j][2]);

        if (texture != NULL) {
          float s = ((float)(j - (i * perDiv)) / (float)(perDiv - 1)) * tScale;
          float t = ((float)(i + 1) / (float)(divs)) * sScale;
          glTexCoord2f(s, t);
        }

        glVertex3f(points[(j + perDiv) % total][0], points[(j + perDiv) % total][1], points[(j + perDiv) % total][2]);

        if (texture != NULL) {
          float s = ((float)(j - (i * perDiv)) / (float)(perDiv - 1)) * tScale;
          float t = ((float)i / (float)(divs)) * sScale;
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
}

float Surface::randFloat(float min, float max) {
  return min + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (max - min)));
}