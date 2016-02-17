#include "renderer.h"

Renderer::Renderer(Shader* _shader)
{
	shader = _shader;
}

void Renderer::render(Entity *entity)
{
	Mesh* mesh = entity->mesh;
	glm::mat4 matrix = createTransformationMatrix(entity->position, entity->rot_angles, entity->scale_factor);

	shader->loadTransformationMatrix(matrix);
	shader->loadShineVars(entity->reflectivity, entity->shineDamper);

	if (entity->texture)
	{
		entity->texture->Bind(0);
		if (entity->texture->fakeLight == true)
		{
			shader->loadFakeLight(true);
		}

		else
		{
			shader->loadFakeLight(false);
		}
	}

	glBindVertexArray(mesh->m_VertexArrayObject);
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);
	//glDrawArrays(GL_TRIANGLES, 0, mesh->m_drawCount);
	glDrawElements(GL_TRIANGLES, mesh->m_drawCount, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);

	if (entity->texture)
	{
		entity->texture->Unbind();
	}
}

Renderer::~Renderer()
{

}