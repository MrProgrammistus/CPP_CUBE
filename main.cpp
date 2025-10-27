#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "window.h"
#include "render.h"
#include "field.h"
#include <iostream>


int main() {
	setlocale(LC_ALL, "");
	createWindow(192*5, 108*5, "Window");

	start_render();
	start_field();
	runWindow();
	stop_render();
	stop_field();
	return 0;
}