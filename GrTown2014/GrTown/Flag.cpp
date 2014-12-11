/*#include "Flag.h"
#include "GrTown_PCH.H"
#include "Utilities/Texture.H"
#include <FL/fl_ask.h>

#include "Utilities/ShaderTools.H"

GLfloat waveTime = 0.0;
float count = 0.0f;

Flag::Flag(float x, float y, float z, float r, float g, float b) :
color(r, g, b), shader(shader)
{
	transMatrix(transform, x, 0, z);
}
void Flag::draw(DrawingState* ds){
	
	count += ds->speedup*.001;
	if (!triedShader) {
		triedShader = true;
		char* error;
		if (!(shader = loadShader("Flag.vert", "Flag.frag", error))) {
			std::string s = "Can't Load Surface Shader:";
			s += error;
			fl_alert(s.c_str());
		}
	}
	
	if (shader != 0) {
		glUseProgram(shader);
		GLint timeUniformLocation = glGetUniformLocation(shader, "count");
		glUniform1i(timeUniformLocation, count);
		GLfloat waveWidth = 2.1, waveHeight = 1.3;
		GLint waveTimeLoc = glGetUniformLocation(shader, "waveTime");
		GLint waveWidthLoc = glGetUniformLocation(shader, "waveWidth");
		GLint waveHeightLoc = glGetUniformLocation(shader, "waveHeight");
		glUniform1f(waveTimeLoc, waveTime);
		glUniform1f(waveWidthLoc, waveWidth);
		glUniform1f(waveHeightLoc, waveHeight);
		//GLfloat UniformMatrix = glGetUniformLocation(shader, "_mvProj");
		//glUniform1i(UniformMatrix, GL_MODELVIEW_PROJECTION_NV);
	}


	/* Draw flag */

		/*glPushMatrix();
		glTranslated(0, 90, 0);
		glRotated(90, 0, 1, 0);
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

		/* Draw flagpole 
		glPushMatrix();
		GLUquadricObj *quadric = gluNewQuadric();
		glColor4fv(&color.r);
		glRotated(-90, 1, 0, 0);
		gluCylinder(quadric, 2, 2, 100, 10, 10);
		glPopMatrix();
		waveTime += .1*ds->speedup;
	
}*/