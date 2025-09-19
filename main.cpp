#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "window.h"
#include "render.h"

void _start() {
	start_render();
}

void _update(float time) {
	update_render(time);
}

int main() {
	createWindow(192*5, 108*5, "Window");

	start = _start;
	update = _update;
	loadWindow();
	runWindow();
	return 0;
}