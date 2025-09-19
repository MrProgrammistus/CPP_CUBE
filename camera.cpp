#include "camera.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "window.h"

glm::mat4 Camera::GetView() {
	return glm::perspective(1.57f, (float)width / height, 0.1f, 10.0f) * glm::lookAt(pos, pos + dir, up);
}

bool _camera_keys[1024];
void _camera_key_callback(GLFWwindow* window, int key, int scan_code, int action, int mode) {
    if (action == GLFW_PRESS)
        _camera_keys[key] = true;
    else if (action == GLFW_RELEASE)
        _camera_keys[key] = false;
}

void Camera::Start() {
	glfwSetKeyCallback(window, _camera_key_callback);
}

void Camera::Update(float time) {
    float speed = 0.01f * time;
    if (_camera_keys[GLFW_KEY_W])
        pos += speed * dir;
    if (_camera_keys[GLFW_KEY_S])
        pos -= speed * dir;
    if (_camera_keys[GLFW_KEY_A])
        pos -= glm::normalize(glm::cross(dir, up)) * speed;
    if (_camera_keys[GLFW_KEY_D])
        pos += glm::normalize(glm::cross(dir, up)) * speed;
}