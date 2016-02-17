#pragma once
#include "mesh.h"
#include "texture.h"
#include "terrainTexturePack.h"
class Terrain
{
public:
	static const int SIZE = 800;
	static const int VERTEX_COUNT = 128;

	int x;
	int z;

	float reflectivity;
	float shineDamper;

	Mesh* mesh;
	TerrainTexturePack *texturePack;
	TerrainTexture *blendMap;

	Terrain(int gridx, int gridz, TerrainTexturePack *_texturePack, TerrainTexture *_blendMap);
	Mesh* generateTerrain();
	void setLightVars(float _reflectivity, float _shineDamper);
	virtual ~Terrain();
};

