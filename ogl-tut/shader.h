#ifndef SHADER_H
#define SHADER_H

#include <string>
#include <GL/glew.h>
#include <glm/glm.hpp>
#include "camera.h"
#include "transform.h"
#include "light.h"

class Shader
{
public:
	Shader(const std::string& filename);
	std::string LoadShader(const std::string& fileName);
	void CheckShaderError(GLuint shader, GLuint flag, bool isProgram, const std::string& errorMessage);
	GLuint CreateShader(const std::string& text, unsigned int type);
	GLuint GetUniformLocation(std::string& varname);
	void loadFloat(int location, float value);
	void loadVector(int location, glm::vec3& arr);
	void loadLight(Light& light);
	void loadShineVars(float reflectivity, float shineDamper);
	void loadFakeLight(bool fakeLight);
	void loadSkyColor(glm::vec3& color);
	void loadBool(int location, bool value);
	void loadMatrix(int location, glm::mat4& matrix);
	void loadTransformationMatrix(glm::mat4& matrix);
	void loadProjectionMatrix(glm::mat4& matrix);
	void loadViewMatrix(Camera& camera);
	void GetAllUniformLocations();

	void Bind();
	void Stop();
	void Update();

	virtual ~Shader();

	static const unsigned int NUM_SHADER = 2;

	enum
	{
		TRANSFORM_U,
		PROJECTION_U,
		VIEW_U,
		LIGHT_POS_U,
		LIGHT_COL_U,
		REFL_U,
		SHINE_U,
		FAKE_LIGHT_U,
		SKY_COLOR_U,

		NUM_UNIFORM
	};

	GLuint m_program;
	GLuint m_shaders[NUM_SHADER];
	GLuint m_uniforms[NUM_UNIFORM];
};

#endif