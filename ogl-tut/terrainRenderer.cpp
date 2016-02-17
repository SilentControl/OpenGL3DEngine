#include "terrainRenderer.h"
#include "transform.h"
#include "terrainTexture.h"
#include "terrainTexturePack.h"

TerrainRenderer::TerrainRenderer(TerrainShader *_shader, glm::mat4 projectionMatrix)
{
	shader = _shader;
	shader->Bind();
	shader->loadProjectionMatrix(projectionMatrix);
	shader->connectTextureUnits();
	shader->Stop();
}

void TerrainRenderer::render(Terrain *terrain)
{
	Mesh* mesh = terrain->mesh;
	glm::mat4 matrix = createTransformationMatrix(glm::vec3(terrain->x, 0.0f, terrain->z), glm::vec3(0.0, 0.0, 0.0), glm::vec3(1.0, 1.0, 1.0));

	shader->loadTransformationMatrix(matrix);
	shader->loadShineVars(terrain->reflectivity, terrain->shineDamper);

	bindTextures(terrain);

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

	unbind();
}

void TerrainRenderer::renderAll(std::vector<Terrain*> terrains)
{
	for (Terrain *terrain : terrains)
	{
		render(terrain);
	}

	shader->Stop();
}

void TerrainRenderer::unbind()
{
	glBindTexture(GL_TEXTURE_2D, 0);
}

void TerrainRenderer::bindTextures(Terrain *terrain)
{
	TerrainTexturePack *texturePack = terrain->texturePack;
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texturePack->backgroundTexture->texture_id);
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, texturePack->rTexture->texture_id);
	glActiveTexture(GL_TEXTURE2);
	glBindTexture(GL_TEXTURE_2D, texturePack->gTexture->texture_id);
	glActiveTexture(GL_TEXTURE3);
	glBindTexture(GL_TEXTURE_2D, texturePack->bTexture->texture_id);
	glActiveTexture(GL_TEXTURE4);
	glBindTexture(GL_TEXTURE_2D, terrain->blendMap->texture_id);
}

TerrainRenderer::~TerrainRenderer()
{
}
