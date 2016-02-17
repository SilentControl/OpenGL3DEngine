#include "masterRenderer.h"

MasterRenderer::MasterRenderer(Renderer *_renderer, Camera* _camera, Light* _light, glm::vec4& _skyColor) : 
				renderer(_renderer), camera(_camera), light(_light), skyColor(_skyColor)
{
	createProjectionMatrix();
	renderer->shader->Bind();
	renderer->shader->loadProjectionMatrix(projectionMatrix);
	renderer->shader->Stop();

	// Culling
	enableCulling();

	terrainShader = new TerrainShader(".//res//");
	terrainRenderer = new TerrainRenderer(terrainShader, projectionMatrix);
}

void MasterRenderer::listTerrains(std::vector<Terrain* >& _Terrains)
{
	Terrains = _Terrains;
}

void MasterRenderer::enableCulling()
{
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
}

void MasterRenderer::disableCulling()
{
	glDisable(GL_CULL_FACE);
}

void MasterRenderer::clearFrame()
{
	glEnable(GL_DEPTH_TEST);
	glClearColor(skyColor.x, skyColor.y, skyColor.z, skyColor.a);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void MasterRenderer::renderEntities(std::vector<Entity*>& Entities)
{
	Shader* shader = renderer->shader;
	shader->Bind();
	shader->loadSkyColor(glm::vec3(skyColor));
	shader->loadLight(*light);
	shader->loadViewMatrix(*camera);

	for (int i = 0; i < Entities.size(); i++)
	{
		if (Entities[i]->texture->transparency == true)
		{
			disableCulling();
		}

		renderer->render(Entities[i]);
		enableCulling();
	}

	shader->Stop();

	terrainShader->Bind();
	terrainShader->loadSkyColor(glm::vec3(skyColor));
	terrainShader->loadLight(*light);
	terrainShader->loadViewMatrix(*camera);
	terrainRenderer->renderAll(Terrains);
	terrainShader->Stop();
}

void MasterRenderer::createProjectionMatrix()
{
	/*float aspect_ratio = 800.0 / 600.0;
	float y_scale = (float)((1.0f / glm::tan(glm::radians(FOV / 2.0f))) * aspect_ratio);
	float x_scale = y_scale / aspect_ratio;
	float frustrum_length = FAR_PLANE - NEAR_PLANE;

	projectionMatrix = glm::mat4(;*/
	projectionMatrix = glm::perspective(glm::radians(FOV), 800.0f / 600.0f, NEAR_PLANE, FAR_PLANE);
}

MasterRenderer::~MasterRenderer()
{
}
