// Adam Sperling
// The definition of the a6_GL_window class, where everything gets drawn

#pragma once

#include <fl/Fl_Gl_Window.H>
#include <FL/gl.h>
#include <glm/glm.hpp>
#include <vector>


class a6_GL_window : public Fl_Gl_Window {
public:
	a6_GL_window(int x, int y, int w, int h, const char * name = 0);

	void rotate_x(int theta);
	void rotate_y(int theta);
	void rotate_z(int theta);

	void setDrawTri();
	void setDrawCube();
	void setDrawDuck();
	void setDrawBalloon();


private:
	virtual void draw();


	void drawCube();
	void drawTriangle();
	void drawDuck();
	void drawBalloon();

	void initGL();
	void initTransforms();
	void lightsOn();
	void lightsOff();
	void rotate(int x, int y, int z);

    bool firstDraw;
	bool draw_tri;
	bool draw_cu;
	bool draw_duck;
	bool draw_balloon;

	int angle_x, angle_y, angle_z;


	//ignore for now...
	int displayListHandle;
	static std::vector<glm::vec3> va_vertices; //array used to hold the points in space used to define the shape of a balloon
	static std::vector<glm::ivec3> va_indices; //array used to hold groups of points that form a single triangular piece of the overall balloon
	static std::vector<glm::vec3> va_normals;  //array used to hold the normal to each point in space, used for light and shadow calculations

};