#pragma once
#include <string>
#include "light.h"
#include "camera.h"
#include "GL\glew.h"
class TerrainShader
{
public:
	TerrainShader(const std::string& filename);
	std::string LoadShader(const std::string& fileName);
	void CheckShaderError(GLuint shader, GLuint flag, bool isProgram, const std::string& errorMessage);
	GLuint CreateShader(const std::string& text, unsigned int type);
	GLuint GetUniformLocation(std::string& varname);
	void loadInt(int location, float value);
	void loadFloat(int location, float value);
	void loadVector(int location, glm::vec3& arr);
	void loadLight(Light& light);
	void loadShineVars(float reflectivity, float shineDamper);
	void loadSkyColor(glm::vec3& color);
	void loadBool(int location, bool value);
	void loadMatrix(int location, glm::mat4& matrix);
	void loadTransformationMatrix(glm::mat4& matrix);
	void loadProjectionMatrix(glm::mat4& matrix);
	void loadViewMatrix(Camera& camera);
	void GetAllUniformLocations();
	void connectTextureUnits();

	void Bind();
	void Stop();
	void Update();
	virtual ~TerrainShader();

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
		SKY_COLOR_U,
		BACKGROUND_TEX_U,
		R_TEX_U,
		G_TEX_U,
		B_TEX_U,
		BLEND_MAP_TEX_U,

		NUM_UNIFORM
	};

	GLuint m_program;
	GLuint m_shaders[NUM_SHADER];
	GLuint m_uniforms[NUM_UNIFORM];
};

