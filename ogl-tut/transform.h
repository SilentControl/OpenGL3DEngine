#ifndef TRANSFORM_H
#define TRANSFORM_H
#include "glm\glm.hpp"
#include "glm\gtc\matrix_transform.hpp"
#include "camera.h"

glm::mat4 createTransformationMatrix(glm::vec3& translation, glm::vec3& rot_angle, glm::vec3& scale_factor);
glm::mat4 createViewMatrix(Camera& camera);

#endif