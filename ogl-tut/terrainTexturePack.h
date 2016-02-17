#pragma once
#include "terrainTexture.h"
class TerrainTexturePack
{
public:

	TerrainTexture *backgroundTexture;
	TerrainTexture *rTexture;
	TerrainTexture *gTexture;
	TerrainTexture *bTexture;

	TerrainTexturePack(TerrainTexture *_backgroundTexture, TerrainTexture *_rTexture, TerrainTexture *_gTexture, TerrainTexture *_bTexture) :
		backgroundTexture(_backgroundTexture), rTexture(_rTexture), gTexture(_gTexture), bTexture(_bTexture) {}
	virtual ~TerrainTexturePack();
};

