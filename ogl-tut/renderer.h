#ifndef RENDERER_H
#define RENDERER_H
#include "entity.h"
#include "shader.h"
#include "transform.h"
class Renderer
{
public:

	Shader* shader;
	Renderer(Shader* _shader);
	void render(Entity *entity);
	virtual ~Renderer();
};

#endif