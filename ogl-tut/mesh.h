#ifndef MESH_H
#define MESH_H

#include <glm/glm.hpp>
#include <GL/glew.h>
#include <vector>

class Vertex
{
public:
	glm::vec3 pos;
	glm::vec2 texCoord;

	Vertex(const glm::vec3& pos, const glm::vec2& texCoord)
	{
		this->pos = pos;
		this->texCoord = texCoord;
	}
};

class Mesh
{
public:

	//Mesh(Vertex* vertices, unsigned int numVertices, std::vector<unsigned int>& _interconnect = std::vector<unsigned int>());
	Mesh(std::vector<float>& _vertice_pos, std::vector<float>& _texture_pos, std::vector<float>& _normals, std::vector<unsigned int>& _interconnect = std::vector<unsigned int>());
	void Draw();

	virtual ~Mesh();

	enum
	{
		POSITION_VB,
		TEXCOORD_VB,
		NORMAL_VB,
		INDEX_VB,

		NUM_BUFFERS
	};

	GLuint m_VertexArrayObject;
	GLuint m_VertexArrayBuffers[NUM_BUFFERS];
	unsigned int m_drawCount;
};

#endif