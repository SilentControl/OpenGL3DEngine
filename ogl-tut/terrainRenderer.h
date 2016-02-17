#pragma once
#include "terrainShader.h"
#include "terrain.h"
#include "glm/glm.hpp"
#include <vector>
class TerrainRenderer
{
public:

	TerrainShader *shader;

	TerrainRenderer(TerrainShader *_shader, glm::mat4 projectionMatrix);
	void render(Terrain *terrain);
	void renderAll(std::vector<Terrain*> terrains);
	void bindTextures(Terrain *terrain);
	void unbind();
	virtual ~TerrainRenderer();
};

