#pragma once
#include <glm/glm.hpp>
#include <GLFW/glfw3.h>

class Camera {
private:
	glm::vec3 pos{ -5, 45, 45 };
	glm::vec3 dir{ 0.0, 0.0, -1.0 };
	glm::vec3 up{ 0.0, 1.0, 0.0 };
public:
	glm::vec3 GetPos();
	void SetPos(glm::vec3);
	glm::vec3 GetDir();
	void SetDir(glm::vec3);
	glm::mat4 GetView();

	void Start();
	void Update(float);
};

extern bool f1;