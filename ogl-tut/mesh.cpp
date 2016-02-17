#include "mesh.h"
#include <vector>

Mesh::Mesh(std::vector<float>& _vertice_pos, std::vector<float>& _texture_pos, std::vector<float>& _normals, std::vector<unsigned int>& _interconnect)
{
	m_drawCount = _interconnect.size();
	//m_drawCount = numVertices;
	glGenVertexArrays(1, &m_VertexArrayObject);
	glBindVertexArray(m_VertexArrayObject);

	glGenBuffers(NUM_BUFFERS, m_VertexArrayBuffers);
	glBindBuffer(GL_ARRAY_BUFFER, m_VertexArrayBuffers[POSITION_VB]);

	// RAM to GPU
	glBufferData(GL_ARRAY_BUFFER, _vertice_pos.size() * sizeof(_vertice_pos[0]), &_vertice_pos[0], GL_STATIC_DRAW);

	// Interpretate data
	//glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

	// Texture
	glBindBuffer(GL_ARRAY_BUFFER, m_VertexArrayBuffers[TEXCOORD_VB]);

	// RAM to GPU
	glBufferData(GL_ARRAY_BUFFER, _texture_pos.size() * sizeof(_texture_pos[0]), &_texture_pos[0], GL_STATIC_DRAW);

	// Interpretate data
	//glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0);

	// Normals
	glBindBuffer(GL_ARRAY_BUFFER, m_VertexArrayBuffers[NORMAL_VB]);
	glBufferData(GL_ARRAY_BUFFER, _normals.size() * sizeof(_normals[0]), &_normals[0], GL_STATIC_DRAW);
	//glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, 0);

	// Index interconnect
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_VertexArrayBuffers[INDEX_VB]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, _interconnect.size() * sizeof(_interconnect[0]), &_interconnect[0], GL_STATIC_DRAW);

	glBindVertexArray(0);
}

/*Mesh::Mesh(Vertex* vertices, unsigned int numVertices, std::vector<unsigned int>& interconnect)
{
	m_drawCount = interconnect.size();
	//m_drawCount = numVertices;
	glGenVertexArrays(1, &m_VertexArrayObject);
	glBindVertexArray(m_VertexArrayObject);

	std::vector<glm::vec3> positions;
	std::vector<glm::vec2> texCoords;

	positions.reserve(numVertices);
	texCoords.reserve(numVertices);

	for (unsigned int i = 0; i < numVertices; i++)
	{
		positions.push_back(vertices[i].pos);
		texCoords.push_back(vertices[i].texCoord);
	}

	glGenBuffers(NUM_BUFFERS, m_VertexArrayBuffers);
	glBindBuffer(GL_ARRAY_BUFFER, m_VertexArrayBuffers[POSITION_VB]);

	// RAM to GPU
	glBufferData(GL_ARRAY_BUFFER, numVertices * sizeof(positions[0]), &positions[0], GL_STATIC_DRAW);

	// Interpretate data
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

	// Texture
	glBindBuffer(GL_ARRAY_BUFFER, m_VertexArrayBuffers[TEXCOORD_VB]);

	// RAM to GPU
	glBufferData(GL_ARRAY_BUFFER, numVertices * sizeof(texCoords[0]), &texCoords[0], GL_STATIC_DRAW);

	// Interpretate data
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_VertexArrayBuffers[INDEX_VB]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, interconnect.size() * sizeof(interconnect[0]), &interconnect[0], GL_STATIC_DRAW);

	glBindVertexArray(0);
	
}*/

Mesh::~Mesh()
{
	glDeleteVertexArrays(1, &m_VertexArrayObject);
}