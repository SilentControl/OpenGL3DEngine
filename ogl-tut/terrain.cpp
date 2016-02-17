#include "terrain.h"

Terrain::Terrain(int gridx, int gridz, TerrainTexturePack *_texturePack, TerrainTexture *_blendMap)
{
	texturePack = _texturePack;
	blendMap = _blendMap;
	x = gridx * SIZE;
	z = gridz * SIZE;
	mesh = generateTerrain();
	reflectivity = 0.0f;
	shineDamper = 100.0f;
}

Mesh* Terrain::generateTerrain()
{
	int count = VERTEX_COUNT * VERTEX_COUNT;
	std::vector<float> vertices;
	std::vector<float> normals;
	std::vector<float> textureCoords;
	std::vector<unsigned int> indices;

	vertices.resize(count * 3);
	normals.resize(count * 3);
	textureCoords.resize(count * 2);
	indices.resize(6 * (VERTEX_COUNT - 1)*(VERTEX_COUNT - 1));

	int vertexPointer = 0;
	for (int i = 0; i<VERTEX_COUNT; i++){
		for (int j = 0; j<VERTEX_COUNT; j++){
			vertices[vertexPointer * 3] = (float)j / ((float)VERTEX_COUNT - 1) * SIZE;
			vertices[vertexPointer * 3 + 1] = 0;
			vertices[vertexPointer * 3 + 2] = (float)i / ((float)VERTEX_COUNT - 1) * SIZE;
			normals[vertexPointer * 3] = 0;
			normals[vertexPointer * 3 + 1] = 1;
			normals[vertexPointer * 3 + 2] = 0;
			textureCoords[vertexPointer * 2] = (float)j / ((float)VERTEX_COUNT - 1);
			textureCoords[vertexPointer * 2 + 1] = (float)i / ((float)VERTEX_COUNT - 1);
			vertexPointer++;
		}
	}

	int pointer = 0;
	for (int gz = 0; gz<VERTEX_COUNT - 1; gz++){
		for (int gx = 0; gx<VERTEX_COUNT - 1; gx++){
			int topLeft = (gz*VERTEX_COUNT) + gx;
			int topRight = topLeft + 1;
			int bottomLeft = ((gz + 1)*VERTEX_COUNT) + gx;
			int bottomRight = bottomLeft + 1;
			indices[pointer++] = topLeft;
			indices[pointer++] = bottomLeft;
			indices[pointer++] = topRight;
			indices[pointer++] = topRight;
			indices[pointer++] = bottomLeft;
			indices[pointer++] = bottomRight;
		}
	}

	reflectivity = 0.0f;
	shineDamper = 0.0f;
	return new Mesh(vertices, textureCoords, normals, indices);
}

void Terrain::setLightVars(float _reflectivity, float _shineDamper)
{
	reflectivity = _reflectivity;
	shineDamper = _shineDamper;
}

Terrain::~Terrain()
{
}
