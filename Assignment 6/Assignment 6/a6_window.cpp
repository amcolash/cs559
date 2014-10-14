// Adam Sperling
// The implementaion of the a6_window

#include "a6_window.h"
#include "callbacks.h"

a6_window::a6_window(int x, int y, int w, int h, const char * name) : Fl_Double_Window(x, y, w, h, name) {
	
	begin(); {
		int pty = 5;
		
		this->canvas = new a6_GL_window(5, 5, 790, 748);

		this->angle_x = new Fl_Hor_Value_Slider(800, pty, 200, 20, "Rotate X");
		angle_x->bounds(0, 360);
		angle_x->value(0);
		angle_x->callback((Fl_Callback*)rotate_x_CB, (void*)this);
		pty += 40;

		this->angle_y = new Fl_Hor_Value_Slider(800, pty, 200, 20, "Rotate Y");
		angle_y->bounds(0, 360);
		angle_y->value(0);
		angle_y->callback((Fl_Callback*)rotate_y_CB, (void*)this);
		pty += 40;

		this->angle_z = new Fl_Hor_Value_Slider(800, pty, 200, 20, "Rotate Z");
		angle_z->bounds(0, 360);
		angle_z->value(0);
		angle_z->callback((Fl_Callback*)rotate_z_CB, (void*)this);
		pty += 80;

		this->cube = new Fl_Button(800, pty, 200, 20, "Draw Cube");
		cube->callback((Fl_Callback*)draw_cu_CB, (void*)this);
		
		pty += 40;

		this->triangle = new Fl_Button(800, pty, 200, 20, "Draw Triangle");
		triangle->callback((Fl_Callback*)draw_tri_CB, (void*)this);

		pty += 40;

		this->duck = new Fl_Button(800, pty, 200, 20, "Draw Duck");
		duck->callback((Fl_Callback*)draw_duck_CB, (void*)this);

		pty += 40;

		this->balloon = new Fl_Button(800, pty, 200, 20, "Draw Balloon");
		balloon->callback((Fl_Callback*)draw_balloon_CB, (void*)this);
	}
	end();
	
}

void a6_window::damageMe() {
	canvas->damage(1);
}

a6_GL_window * a6_window::getCanvas() {
	return this->canvas;
}

void a6_window::rotate_x() {
	this->canvas->rotate_x((int)angle_x->value());
}

void a6_window::rotate_y() {
	this->canvas->rotate_y((int)angle_y->value());
}

void a6_window::rotate_z() {
	this->canvas->rotate_z((int)angle_z->value());
}

void a6_window::drawTriangle() {
	this->canvas->setDrawTri();
}

void a6_window::drawCube() {
	this->canvas->setDrawCube();
}

void a6_window::drawDuck() {
	this->canvas->setDrawDuck();
}

void a6_window::drawBalloon() {
	this->canvas->setDrawBalloon();
}