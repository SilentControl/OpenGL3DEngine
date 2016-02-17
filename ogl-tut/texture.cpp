#include "texture.h"
#include "stb_image.h"
#include <iostream>
#include <cassert>

Texture::Texture(const std::string& filename, bool _transparency)
{
	int width, height, numComponents;
	unsigned char* imageData = stbi_load(filename.c_str(), &width, &height, &numComponents, 4);
	transparency = _transparency;
	fakeLight = false;

	if (imageData == NULL)
	{
		std::cerr << "Error loading texture!\n";
	}
	
	glGenTextures(1, &m_texture);

	glBindTexture(GL_TEXTURE_2D, m_texture);
	// wrap the texture if not enough pixels
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, imageData);
	glBindTexture(GL_TEXTURE_2D, 0);
	stbi_image_free(imageData);
}

void Texture::Bind(unsigned int unit)
{
	assert(unit >= 0 && unit <= 31);
	glActiveTexture(GL_TEXTURE0 + unit);
	glBindTexture(GL_TEXTURE_2D, m_texture);
}

void Texture::setFakeLight(bool light)
{
	fakeLight = light;
}

void Texture::Unbind()
{
	glBindTexture(GL_TEXTURE_2D, 0);
}

Texture::~Texture()
{
	glDeleteTextures(1, &m_texture);
}