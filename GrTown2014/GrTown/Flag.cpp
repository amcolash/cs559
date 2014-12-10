#include "Flag.h"
#include "GrTown_PCH.H"
#include "Utilities/Texture.H"
#include <FL/fl_ask.h>

#include "Utilities/ShaderTools.H"

float count = 0.0f;

Flag::Flag(float x, float y, float z, float r, float g, float b) :
color(r, g, b), shader(shader)
{
	transMatrix(transform, x, 0, z);
}
void Flag::draw(DrawingState* ds){
	
	count += ds->speedup*.1;
	if (!triedShader) {
		triedShader = true;
		char* error;
		if (!(shader = loadShader("flag.vert", "flag.frag", error))) {
			std::string s = "Can't Load Surface Shader:";
			s += error;
			fl_alert(s.c_str());
		}
	}
	if (shader != 0) {
		glUseProgram(shader);
		GLint timeUniformLocation = glGetUniformLocation(shader, "_time");
		glUniform1i(timeUniformLocation, count);
		GLfloat UniformMatrix = glGetUniformLocation(shader, "_mvProj");
		glUniform1i(UniformMatrix, GL_MODELVIEW_PROJECTION_NV);
	}

		

		glPushMatrix();
		glTranslated(0, 90, 0);

		glBegin(GL_QUADS);
		glVertex3f(0, -20, 0);
		glVertex3f(0, 10, 0);
		glVertex3f(30, 10, 30);
		glVertex3f(30, -20, 30);
		glEnd();

		glBegin(GL_QUADS);
		glVertex3f(30, -20, 30);
		glVertex3f(30, 10, 30);
		glVertex3f(0, 10, 0);
		glVertex3f(0, -20, 0);
		glEnd();

		glPopMatrix();
		glUseProgram(0);

		glPushMatrix();
		GLUquadricObj *quadric = gluNewQuadric();
		glColor4fv(&color.r);
		glRotated(-90, 1, 0, 0);
		gluCylinder(quadric, 2, 2, 100, 10, 10);
		glPopMatrix();
	
}