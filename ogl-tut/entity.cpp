#include "entity.h"

void Entity::setPosition(glm::vec3 _position)
{
	position = _position;
}

glm::vec3 Entity::getPosition()
{
	return position;
}

void Entity::setRot(glm::vec3 _rot_angles)
{
	rot_angles = _rot_angles;
}

glm::vec3 Entity::getRot()
{
	return rot_angles;
}

void Entity::setScale(glm::vec3 _scale_factor)
{
	scale_factor = _scale_factor;
}

glm::vec3 Entity::getScale()
{
	return scale_factor;
}

void Entity::increasePosition(glm::vec3 offset)
{
	position += offset;
}

void Entity::increaseRotation(glm::vec3 offset)
{
	rot_angles += offset;
}

void Entity::setLightVars(float _reflectivity, float _shineDamper)
{
	reflectivity = _reflectivity;
	shineDamper = _shineDamper;
}

Entity::~Entity()
{
}
