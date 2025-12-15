#include "camera.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "window.h"
#include <set>
#include <iostream>
#include "field.h"
#include "analyzer.h"

glm::mat4 Camera::GetView() {
	return glm::perspective(1.57f, (float)width / height, 0.01f, 1000.0f) * glm::lookAt(pos, pos + dir, up);
}

glm::vec3 Camera::GetPos() {
	return pos;
}

std::set<int> _camera_keys{};
// ================================================================================================================= клавиши клавиатуры
void _camera_key_callback(GLFWwindow* window, int key, int scan_code, int action, int mode) {
	if (action == GLFW_PRESS)
		_camera_keys.insert(key);
	else if (action == GLFW_RELEASE)
		_camera_keys.erase(key);
}

float _camera_sensitivity = 0.1f;
int _camera_last_x;
int _camera_last_y;
float _camera_yaw = -90;
float _camera_pitch = 0;
glm::vec3* _camera_dir;
extern bool _camera_mouse_hide;
int _camera_center_x;
int _camera_center_y;
bool _camera_first = true;
// ================================================================================================================= курсор
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

		x_offset *= _camera_sensitivity;
		y_offset *= _camera_sensitivity;

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
	mousePosAction(x_pos, y_pos);
}
// ================================================================================================================= кнопки мыши
void _camera_mouse_callback2(GLFWwindow* window, int button, int action, int mode) {
	if (button == 0) {
		if (action) {
			_camera_first = true;
			glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
			_camera_mouse_hide = true;
		}
		else {
			glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
			_camera_mouse_hide = false;
		}
	}
	mouseButtonAction(button, action, mode);
}
void _camera_resize(float w, float h) {
	_camera_last_x = _camera_center_x = w / 2;
	_camera_last_y = _camera_center_y = h / 2;
}

void Camera::Start() {
	_camera_dir = &dir;
	glfwSetKeyCallback(window, _camera_key_callback);
	glfwSetCursorPosCallback(window, _camera_mouse_callback);
	glfwSetMouseButtonCallback(window, _camera_mouse_callback2);
	_camera_resize(width, height);
	onResizeEvent.insert(_camera_resize);
	glfwSetCursorPos(window, _camera_center_x, _camera_center_y);
}

bool f1;
bool _f1;
float _camera_base_speed = 0.01f;
float _camera_boost = 5;
float _camera_speed;
bool _camera_mouse_hide;
bool c_space_enter;
bool c_pause;
// ================================================================================================================= движение
void Camera::Update(float time) {
	float speed = _camera_speed * time;
	if (_camera_keys.contains(GLFW_KEY_W))
		pos += speed * glm::normalize(glm::vec3(dir.x, 0, dir.z));
	if (_camera_keys.contains(GLFW_KEY_S))
		pos -= speed * glm::normalize(glm::vec3(dir.x, 0, dir.z));
	if (_camera_keys.contains(GLFW_KEY_A))
		pos -= glm::normalize(glm::normalize(glm::cross(dir, up))) * speed;
	if (_camera_keys.contains(GLFW_KEY_D))
		pos += glm::normalize(glm::normalize(glm::cross(dir, up))) * speed;
	if (_camera_keys.contains(GLFW_KEY_SPACE))
		pos += glm::normalize(glm::normalize(up)) * speed;
	if (_camera_keys.contains(GLFW_KEY_LEFT_SHIFT))
		pos -= glm::normalize(glm::normalize(up)) * speed;
	if (_camera_keys.contains(GLFW_KEY_LEFT_CONTROL))
		_camera_speed = _camera_base_speed * _camera_boost;
	else
		_camera_speed = _camera_base_speed;

	if (_camera_keys.contains(GLFW_KEY_R)) {
		stop_field();
		start_field();
	}
	if (_camera_keys.contains(GLFW_KEY_F) && !c_space_enter) {
		if (!c_pause) {
			pause_field();
			pause_step();
			c_pause = true;
		}
		else {
			resume_field();
			resume_step();
			c_pause = false;
		}
		c_space_enter = true;
	}
	else if(!_camera_keys.contains(GLFW_KEY_F)) c_space_enter = false;
	if (_camera_keys.contains(GLFW_KEY_V)) {
		next_frame();
		next_step();
	}
	if (_camera_keys.contains(GLFW_KEY_F1) && !_f1) {
		if (!f1) {
			f1 = true;
		}
		else {
			f1 = false;
		}
		_f1 = true;
	}
	else if (!_camera_keys.contains(GLFW_KEY_F1)) _f1 = false;
}