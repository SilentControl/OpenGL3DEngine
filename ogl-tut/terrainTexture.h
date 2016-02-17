#pragma once
#include "GL\glew.h"
class TerrainTexture
{
public:

	GLuint texture_id;

	TerrainTexture(GLuint _texture_id) : texture_id(_texture_id) {}
	virtual ~TerrainTexture();
};

