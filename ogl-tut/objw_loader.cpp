#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cstdio>
#include "glm\glm.hpp"
#include "objw_loader.h"

void load_obj(std::string fileName, std::vector<float>& vertice_pos,
									std::vector<float>& texture_pos,
									std::vector<float>& normal_pos,
									std::vector<unsigned int>& indices)
{
	std::ifstream f(fileName);
	std::string buffer;
	if (!f.is_open())
	{
		std::cerr << "Error: Could not open custom model file (obj)\n";
	}

	std::vector<glm::vec3> vertices;
	std::vector<glm::vec2> textures;
	std::vector<glm::vec3> normals;
	std::vector<unsigned int> index;

	bool start = false;

	while (std::getline(f, buffer))
	{
		if (!buffer.empty())
		{
			if (buffer[0] == 'v' && buffer[1] == ' ')
			{
				float x, y, z;
				sscanf(buffer.c_str(), "v %f %f %f", &x, &y, &z);
				vertices.push_back(glm::vec3(x, y, z));
			}

			else
			if (buffer[0] == 'v' && buffer[1] == 't')
			{
				if (buffer[2] == ' ')
				{
					float x, y;
					sscanf(buffer.c_str(), "vt %f %f", &x, &y);
					textures.push_back(glm::vec2(x, y));
				}
			}

			else
			if (buffer[0] == 'v' && buffer[1] == 'n')
			{
				if (buffer[2] == ' ')
				{
					float x, y, z;
					sscanf(buffer.c_str(), "vn %f %f %f", &x, &y, &z);
					normals.push_back(glm::vec3(x, y, z));
				}
			}

			else
			if (buffer[0] == 'f')
			{
				if (buffer[1] == ' ')
				{
					if (start == false)
					{
						start = true;
						texture_pos.resize(vertices.size() * 2, 0.0f);
						normal_pos.resize(vertices.size() * 3, 0.0f);
					}

					int i1, i2, i3, i21, i22, i23, i31, i32, i33;
					sscanf(buffer.c_str(), "f %d/%d/%d %d/%d/%d %d/%d/%d", &i1, &i2, &i3, &i21, &i22, &i23, &i31, &i32, &i33);

					i1--; i2--; i3--;
					i21--; i22--; i23--;
					i31--; i32--; i33--;

					indices.push_back(i1);
					glm::vec2 crt_tex1 = textures[i2];
					texture_pos[i1 * 2] = crt_tex1.x;
					texture_pos[i1 * 2 + 1] = 1 - crt_tex1.y;
					glm::vec3 crt_norm1 = normals[i3];
					normal_pos[i1 * 3] = crt_norm1.x;
					normal_pos[i1 * 3 + 1] = crt_norm1.y;
					normal_pos[i1 * 3 + 2] = crt_norm1.z;

					indices.push_back(i21);
					glm::vec2 crt_tex2 = textures[i22];
					texture_pos[i21 * 2] = crt_tex2.x;
					texture_pos[i21 * 2 + 1] = 1 - crt_tex2.y;
					glm::vec3 crt_norm2 = normals[i23];
					normal_pos[i21 * 3] = crt_norm2.x;
					normal_pos[i21 * 3 + 1] = crt_norm2.y;
					normal_pos[i21 * 3 + 2] = crt_norm2.z;

					indices.push_back(i31);
					glm::vec2 crt_tex3 = textures[i32];
					texture_pos[i31 * 2] = crt_tex3.x;
					texture_pos[i31 * 2 + 1] = 1 - crt_tex3.y;
					glm::vec3 crt_norm3 = normals[i33];
					normal_pos[i31 * 3] = crt_norm3.x;
					normal_pos[i31 * 3 + 1] = crt_norm3.y;
					normal_pos[i31 * 3 + 2] = crt_norm3.z;
				}
			}
		}
	}

	for (int i = 0; i < vertices.size(); i++)
	{
		vertice_pos.push_back(vertices[i].x);
		vertice_pos.push_back(vertices[i].y);
		vertice_pos.push_back(vertices[i].z);
	}

	f.close();
}
