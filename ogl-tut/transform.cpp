#include "transform.h"

glm::mat4 createTransformationMatrix(glm::vec3& translation, glm::vec3& rot_angle, glm::vec3& scale_factor)
{
	glm::mat4 tr_matrix = glm::translate(glm::mat4(1.0f), translation);
	glm::mat4 rot_matrix = glm::rotate(tr_matrix, glm::radians(rot_angle.x), glm::vec3(1, 0, 0));
	rot_matrix = glm::rotate(rot_matrix, glm::radians(rot_angle.y), glm::vec3(0, 1, 0));
	rot_matrix = glm::rotate(rot_matrix, glm::radians(rot_angle.z), glm::vec3(0, 0, 1));
	glm::mat4 scale_matrix = glm::scale(rot_matrix, scale_factor);
	return scale_matrix;
}

glm::mat4 createViewMatrix(Camera& camera)
{
	glm::mat4 view_matrix = glm::mat4();
	glm::mat4 rot_matrix = glm::rotate(view_matrix, glm::radians(camera.pitch), glm::vec3(1, 0, 0));
	rot_matrix = glm::rotate(rot_matrix, glm::radians(camera.yaw), glm::vec3(1, 0, 0));

	glm::vec3 cam_pos = camera.position;
	glm::vec3 neg_cam = glm::vec3(-cam_pos.x, -cam_pos.y, -cam_pos.z);
	rot_matrix = glm::translate(rot_matrix, neg_cam);
	return rot_matrix;
}