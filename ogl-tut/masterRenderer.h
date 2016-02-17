#pragma once
#include "renderer.h"
#include "entity.h"
#include "terrainRenderer.h"
#include <vector>
class MasterRenderer
{
public:

	float FOV = 70.0f;
	float NEAR_PLANE = 0.01f;
	float FAR_PLANE = 1000.0f;

	glm::vec4 skyColor;

	glm::mat4 projectionMatrix;
	void createProjectionMatrix();

	Renderer *renderer;
	TerrainRenderer *terrainRenderer;
	TerrainShader *terrainShader;
	Camera* camera;
	Light* light;
	std::vector<Terrain*> Terrains;

	MasterRenderer(Renderer *_renderer, Camera* _camera, Light* _light, glm::vec4& skyColor);

	void renderEntities(std::vector<Entity*>& Entities);
	void listTerrains(std::vector<Terrain* >& _Terrains);
	void enableCulling();
	void disableCulling();
	void clearFrame();

	virtual ~MasterRenderer();
};

