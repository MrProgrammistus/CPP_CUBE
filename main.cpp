#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "window.h"
#include "render.h"


int main() {
	createWindow(192*5, 108*5, "Window");

	start_render();
	runWindow();
	stop_render();
	return 0;
}