// Adam Sperling
// The main file for all FLTK projects will probably look a lot like this

#include <GL\glew.h>
#include <FL\Fl.H>
#include <glm\glm.hpp>
#include "a6_window.h"


int main(int argc, char * argv[]) {
	a6_window myWindow(50, 50, 1024, 768, "Assignment 6");

	myWindow.show();
	return Fl::run();
}