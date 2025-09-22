#include "camera.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "window.h"
#include <set>
#include <iostream>

glm::mat4 Camera::GetView() {
	return glm::perspective(1.57f, (float)width / height, 0.01f, 1000.0f) * glm::lookAt(pos, pos + dir, up);
}

std::set<int> _camera_keys{};
void _camera_key_callback(GLFWwindow* window, int key, int scan_code, int action, int mode) {
	if (action == GLFW_PRESS)
		_camera_keys.insert(key);
	else if (action == GLFW_RELEASE)
		_camera_keys.erase(key);
}

float _camera_sensitivity = 0.3f;
int _camera_last_x;
int _camera_last_y;
float _camera_yaw = -90;
float _camera_pitch = 0;
glm::vec3* _camera_dir;
float _camera_time;
extern bool _camera_mouse_hide;
int _camera_center_x;
int _camera_center_y;
bool _camera_first = true;
void _camera_mouse_callback(GLFWwindow* window, double x_pos, double y_pos) {

	if (_camera_first) {
		_camera_last_x = x_pos;
		_camera_last_y = y_pos;
		_camera_first = false;
	}
	else if (_camera_mouse_hide) {

		float x_offset = x_pos - _camera_last_x;
		float y_offset = _camera_last_y - y_pos;
		_camera_last_x = x_pos;
		_camera_last_y = y_pos;

		x_offset *= _camera_sensitivity * _camera_time;
		y_offset *= _camera_sensitivity * _camera_time;

		_camera_yaw += x_offset;
		_camera_pitch += y_offset;

		if (_camera_pitch > 89.9f)
			_camera_pitch = 89.9f;
		if (_camera_pitch < -89.9f)
			_camera_pitch = -89.9f;

		glm::vec3 front;
		front.x = cos(glm::radians(_camera_pitch)) * cos(glm::radians(_camera_yaw));
		front.y = sin(glm::radians(_camera_pitch));
		front.z = cos(glm::radians(_camera_pitch)) * sin(glm::radians(_camera_yaw));
		*_camera_dir = glm::normalize(front);
	}
}
void _camera_resize(float w, float h) {
	_camera_last_x = _camera_center_x = w / 2;
	_camera_last_y = _camera_center_y = h / 2;
}

void Camera::Start() {
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	_camera_dir = &dir;
	glfwSetKeyCallback(window, _camera_key_callback);
	glfwSetCursorPosCallback(window, _camera_mouse_callback);
	_camera_resize(width, height);
	onResizeEvent.insert(_camera_resize);
	glfwSetCursorPos(window, _camera_center_x, _camera_center_y);
}

float _camera_base_speed = 0.01f;
float _camera_speed;
bool _camera_esc_press;
bool _camera_mouse_hide = true;
void Camera::Update(float time) {
	_camera_time = time;
	
	if (_camera_mouse_hide) {
		float speed = _camera_speed * time;
		if (_camera_keys.contains(GLFW_KEY_W))
			pos += speed * glm::vec3(dir.x, 0, dir.z);
		if (_camera_keys.contains(GLFW_KEY_S))
			pos -= speed * glm::vec3(dir.x, 0, dir.z);
		if (_camera_keys.contains(GLFW_KEY_A))
			pos -= glm::normalize(glm::cross(dir, up)) * speed;
		if (_camera_keys.contains(GLFW_KEY_D))
			pos += glm::normalize(glm::cross(dir, up)) * speed;
		if (_camera_keys.contains(GLFW_KEY_SPACE))
			pos += glm::normalize(up) * speed;
		if (_camera_keys.contains(GLFW_KEY_LEFT_SHIFT))
			pos -= glm::normalize(up) * speed;
		if (_camera_keys.contains(GLFW_KEY_LEFT_CONTROL))
			_camera_speed = _camera_base_speed * 5;
		else
			_camera_speed = _camera_base_speed;
	}
	if (_camera_keys.contains(GLFW_KEY_ESCAPE) && !_camera_esc_press) {
		if (_camera_mouse_hide) {
			glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
			_camera_mouse_hide = false;
		}
		else {
			glfwSetCursorPos(window, _camera_center_x, _camera_center_y);
			_camera_first = true;
			glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
			_camera_mouse_hide = true;
		}
		_camera_esc_press = true;
	}
	else if (!_camera_keys.contains(GLFW_KEY_ESCAPE)) _camera_esc_press = false;
}