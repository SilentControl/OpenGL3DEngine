#include "terrainShader.h"
#include "GL\glew.h"
#include "glm\glm.hpp"
#include <iostream>
#include <fstream>
#include "glm\gtc\type_ptr.hpp"
#include "transform.h"

TerrainShader::TerrainShader(const std::string& filename)
{
	m_program = glCreateProgram();
	m_shaders[0] = CreateShader(LoadShader(filename + "terrainVertexShader.txt"), GL_VERTEX_SHADER);
	m_shaders[1] = CreateShader(LoadShader(filename + "terrainFragmentShader.txt"), GL_FRAGMENT_SHADER);

	for (unsigned int i = 0; i < NUM_SHADER; i++)
	{
		glAttachShader(m_program, m_shaders[i]);
	}

	glBindAttribLocation(m_program, 0, "position");
	glBindAttribLocation(m_program, 1, "texCoord");
	glBindAttribLocation(m_program, 2, "normal");

	glLinkProgram(m_program);
	CheckShaderError(m_program, GL_LINK_STATUS, true, "Error: Program linking failed: ");

	glValidateProgram(m_program);
	CheckShaderError(m_program, GL_VALIDATE_STATUS, true, "Error: Program validation failed: ");

	GetAllUniformLocations();
}

GLuint TerrainShader::GetUniformLocation(std::string& varname)
{
	return glGetUniformLocation(m_program, varname.c_str());
}

void TerrainShader::GetAllUniformLocations()
{
	m_uniforms[TRANSFORM_U] = glGetUniformLocation(m_program, "transformationMatrix");
	m_uniforms[PROJECTION_U] = glGetUniformLocation(m_program, "projectionMatrix");
	m_uniforms[VIEW_U] = glGetUniformLocation(m_program, "viewMatrix");
	m_uniforms[LIGHT_POS_U] = glGetUniformLocation(m_program, "lightPosition");
	m_uniforms[LIGHT_COL_U] = glGetUniformLocation(m_program, "lightColor");
	m_uniforms[REFL_U] = glGetUniformLocation(m_program, "reflectivity");
	m_uniforms[SHINE_U] = glGetUniformLocation(m_program, "shineDamper");
	m_uniforms[SKY_COLOR_U] = glGetUniformLocation(m_program, "skyColor");
	m_uniforms[BACKGROUND_TEX_U] = glGetUniformLocation(m_program, "backgroundTexture");
	m_uniforms[R_TEX_U] = glGetUniformLocation(m_program, "rTexture");
	m_uniforms[G_TEX_U] = glGetUniformLocation(m_program, "gTexture");
	m_uniforms[B_TEX_U] = glGetUniformLocation(m_program, "bTexture");
	m_uniforms[BLEND_MAP_TEX_U] = glGetUniformLocation(m_program, "blendMap");
}

void TerrainShader::connectTextureUnits()
{
	loadInt(m_uniforms[BACKGROUND_TEX_U], 0);
	loadInt(m_uniforms[R_TEX_U], 1);
	loadInt(m_uniforms[G_TEX_U], 2);
	loadInt(m_uniforms[B_TEX_U], 3);
	loadInt(m_uniforms[BLEND_MAP_TEX_U], 4);
}

void TerrainShader::loadInt(int location, float value)
{
	glUniform1i(location, value);
}

void TerrainShader::loadFloat(int location, float value)
{
	glUniform1f(location, value);
}

void TerrainShader::loadVector(int location, glm::vec3& arr)
{
	glUniform3f(location, arr.x, arr.y, arr.z);
}

void TerrainShader::loadLight(Light& light)
{
	loadVector(m_uniforms[LIGHT_POS_U], light.position);
	loadVector(m_uniforms[LIGHT_COL_U], light.color);
}

void TerrainShader::loadSkyColor(glm::vec3& color)
{
	loadVector(m_uniforms[SKY_COLOR_U], color);
}

void TerrainShader::loadShineVars(float reflectivity, float shineDamper)
{
	loadFloat(m_uniforms[REFL_U], reflectivity);
	loadFloat(m_uniforms[SHINE_U], shineDamper);
}

void TerrainShader::loadBool(int location, bool value)
{
	loadFloat(location, value == true ? 1.0f : 0.0f);
}

void TerrainShader::loadMatrix(int location, glm::mat4& matrix)
{
	glUniformMatrix4fv(location, 1, false, glm::value_ptr(matrix));
}

void TerrainShader::loadTransformationMatrix(glm::mat4& matrix)
{
	loadMatrix(m_uniforms[TRANSFORM_U], matrix);
}

void TerrainShader::loadProjectionMatrix(glm::mat4& matrix)
{
	loadMatrix(m_uniforms[PROJECTION_U], matrix);
}

void TerrainShader::loadViewMatrix(Camera& camera)
{
	loadMatrix(m_uniforms[VIEW_U], createViewMatrix(camera));
}


void TerrainShader::Bind()
{
	glUseProgram(m_program);
}

void TerrainShader::Stop()
{
	glUseProgram(0);
}

std::string TerrainShader::LoadShader(const std::string& fileName)
{
	std::ifstream file;
	file.open((fileName).c_str());

	std::string output;
	std::string line;

	if (file.is_open())
	{
		while (file.good())
		{
			getline(file, line);
			output.append(line + "\n");
		}
	}
	else
	{
		std::cerr << "Unable to load shader: " << fileName << std::endl;
	}

	return output;
}

void TerrainShader::CheckShaderError(GLuint shader, GLuint flag, bool isProgram, const std::string& errorMessage)
{
	GLint success = 0;
	GLchar error[1024] = { 0 };

	if (isProgram)
		glGetProgramiv(shader, flag, &success);
	else
		glGetShaderiv(shader, flag, &success);

	if (success == GL_FALSE)
	{
		if (isProgram)
			glGetProgramInfoLog(shader, sizeof(error), NULL, error);
		else
			glGetShaderInfoLog(shader, sizeof(error), NULL, error);

		std::cerr << errorMessage << ": '" << error << "'" << std::endl;
	}
}

GLuint TerrainShader::CreateShader(const std::string& text, unsigned int type)
{
	GLuint shader = glCreateShader(type);

	if (shader == 0)
		std::cerr << "Error compiling shader type " << type << std::endl;

	const GLchar* p[1];
	p[0] = text.c_str();
	GLint lengths[1];
	lengths[0] = text.length();

	glShaderSource(shader, 1, p, lengths);
	glCompileShader(shader);

	CheckShaderError(shader, GL_COMPILE_STATUS, false, "Error compiling shader!");

	return shader;
}

TerrainShader::~TerrainShader()
{
	glUseProgram(0);
	for (unsigned int i = 0; i < NUM_SHADER; i++)
	{
		glDetachShader(m_program, m_shaders[i]);
		glDeleteShader(m_shaders[i]);
	}

	glDeleteProgram(m_program);
}
