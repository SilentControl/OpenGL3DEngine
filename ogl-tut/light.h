#pragma once

#include "glm\glm.hpp"

class Light
{
public:

	glm::vec3 position;
	glm::vec3 color;

	Light(glm::vec3 _position, glm::vec3 _color) : position(_position), color(_color) {}
	void move();
	virtual ~Light();
};

