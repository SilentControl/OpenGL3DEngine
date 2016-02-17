#pragma once
#include <glm/glm.hpp>

class Camera
{
public:

	glm::vec3 position;
	float pitch;
	float yaw;
	float roll;

	Camera();
	void move();

	virtual ~Camera();
};

