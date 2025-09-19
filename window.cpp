#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <time.h>

#include "window.h"
#include "shader.h"

GLFWwindow* window;

int width, height;

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
	glfwSetWindowSizeCallback(window, [](GLFWwindow* window, int w, int h)
	{
		width = w;
		height = h;
		glViewport(0, 0, width, height);
	});
}

void(*start)();
void(*update)(float);

void loadWindow() {
	if (start != 0) start();
}

float _window_time;
void runWindow() {
	long last = clock();
	while (!glfwWindowShouldClose(window)) {
		glfwPollEvents();

		glClear(GL_COLOR_BUFFER_BIT);

		long time = clock();
		_window_time = (_window_time * 1023 + time - last) / 1024;
		if(update != 0) update(_window_time);
		last = time;

		glfwSwapBuffers(window);
	}
}