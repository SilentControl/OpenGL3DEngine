#pragma once
#include "mesh.h"
#include "texture.h"

class Entity
{
public:

	Mesh *mesh;
	Texture* texture;
	glm::vec3 position;
	glm::vec3 rot_angles;
	glm::vec3 scale_factor;
	float reflectivity;
	float shineDamper;

	Entity(Mesh *_mesh, Texture *_texture = NULL, glm::vec3 _position = glm::vec3(0, 0, 0),
						glm::vec3 _rot_angles = glm::vec3(0, 0, 0),
						glm::vec3 _scale_factor = glm::vec3(1, 1, 1)) :
		mesh(_mesh),	texture(_texture), position(_position),
						rot_angles(_rot_angles),
						scale_factor(_scale_factor) {
		reflectivity = 0.5f;
		shineDamper = 100.0f;
	}

	void setLightVars(float _reflectivity, float _shineDamper);

	void setPosition(glm::vec3 _position);
	glm::vec3 getPosition();

	void setRot(glm::vec3 _rot_angles);
	glm::vec3 getRot();

	void setScale(glm::vec3 _scale_factor);
	glm::vec3 getScale();

	void increasePosition(glm::vec3 offset);
	void increaseRotation(glm::vec3 offset);

	virtual ~Entity();
};

