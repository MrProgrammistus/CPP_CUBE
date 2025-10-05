#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <time.h>

#include "window.h"
#include "shader.h"

GLFWwindow* window;

int width, height;

std::set<void(*)(float)> onUpdateEvent;
std::set<void(*)(float, float)> onResizeEvent;

void _window_onResize(GLFWwindow * window, int w, int h)
{
	width = w;
	height = h;
	glViewport(0, 0, width, height);

	for (void(*func)(float, float) : onResizeEvent) func(w, h);
}

void createWindow(int w, int h, const char* name) {
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	window = glfwCreateWindow(w, h, name, nullptr, nullptr);
	glfwMakeContextCurrent(window);
	glewInit();
	width = w;
	height = h;
	glfwSetWindowSizeCallback(window, _window_onResize);
}

float _window_time;
void runWindow() {
	long last = clock();
	while (!glfwWindowShouldClose(window)) {
		glfwPollEvents();

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		long time = clock();
		_window_time = (_window_time * 1023 + time - last) / 1024;
		for (void(*func)(float) : onUpdateEvent) func(_window_time);
		last = time;

		glfwSwapBuffers(window);
	}
}