//Adam Sperling
// Here's where we actually implement the callbacks

#include "callbacks.h"


void rotate_x_CB(Fl_Widget*, a6_window* w) {
	w->rotate_x();
	w->damageMe();
}

void rotate_y_CB(Fl_Widget*, a6_window* w) {
	w->rotate_y();
	w->damageMe();
}

void rotate_z_CB(Fl_Widget*, a6_window* w) {
	w->rotate_z();
	w->damageMe();
}

void draw_tri_CB(Fl_Widget*, a6_window* w) {
	w->drawTriangle();
	w->damageMe();
}

void draw_cu_CB(Fl_Widget*, a6_window* w) {
	w->drawCube();
	w->damageMe();
}

void draw_duck_CB(Fl_Widget*, a6_window* w) {
	w->drawDuck();
	w->damageMe();
}

void draw_balloon_CB(Fl_Widget*, a6_window* w) {
	w->drawBalloon();
	w->damageMe();
}