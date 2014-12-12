// Adam Sperling
// The definition for the a6_window class, which holds the GL window and widgets

#pragma once

#include <FL\Fl.H>
#include <FL\Fl_Double_Window.H>
#include <FL\Fl_Widget.H>
#include <FL\Fl_Button.H>
#include <FL\Fl_Hor_Value_Slider.H>
#include <FL/Fl_Group.H>

#include "a6_GL_window.h"


class a6_window : public Fl_Double_Window {

public:
	a6_window(int x, int y, int w, int h, const char * name);

	a6_GL_window * getCanvas();

	void damageMe();
	void rotate_x();
	void rotate_y();
	void rotate_z();
	void drawTriangle();
	void drawCube();
	void drawDuck();
	void drawBalloon();



private:
	a6_GL_window * canvas;

	Fl_Group * widgets;

	Fl_Button * cube;
	Fl_Button * triangle;
	Fl_Button * duck;
	Fl_Button * balloon;
	
	Fl_Hor_Value_Slider * angle_x;
	Fl_Hor_Value_Slider * angle_y;
	Fl_Hor_Value_Slider * angle_z;



};
