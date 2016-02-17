#ifndef TEXTURE_H
#define TEXTURE_H

#include <string>
#include <GL/glew.h>

class Texture
{
public:

	int id;
	bool transparency;
	bool fakeLight;

	Texture(const std::string& filename, bool transparency);
	void setFakeLight(bool light);
	void Bind(unsigned int unit);
	void Unbind();

	virtual ~Texture();

	GLuint m_texture;
};

#endif