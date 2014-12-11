//Adam Sperling
// Here's the definition for the callbacks used
#pragma once

#include "a6_window.h"
class a6_window;
class Fl_Widget;

void rotate_x_CB(Fl_Widget*, a6_window* w);
void rotate_y_CB(Fl_Widget*, a6_window* w);
void rotate_z_CB(Fl_Widget*, a6_window* w);

void draw_tri_CB(Fl_Widget*, a6_window* w);
void draw_cu_CB(Fl_Widget*, a6_window* w);
void draw_duck_CB(Fl_Widget*, a6_window* w);
void draw_balloon_CB(Fl_Widget*, a6_window* w);