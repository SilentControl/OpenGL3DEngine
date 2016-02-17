#include "shader.h"
#include <iostream>
#include <fstream>
#include <glm/gtc/type_ptr.hpp>

Shader::Shader(const std::string& filename)
{
	m_program = glCreateProgram();
	m_shaders[0] = CreateShader(LoadShader(filename + "vertexshader.txt"), GL_VERTEX_SHADER);
	m_shaders[1] = CreateShader(LoadShader(filename + "fragmentshader.txt"), GL_FRAGMENT_SHADER);

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

GLuint Shader::GetUniformLocation(std::string& varname)
{
	return glGetUniformLocation(m_program, varname.c_str());
}

void Shader::GetAllUniformLocations()
{
	m_uniforms[TRANSFORM_U] = glGetUniformLocation(m_program, "transformationMatrix");
	m_uniforms[PROJECTION_U] = glGetUniformLocation(m_program, "projectionMatrix");
	m_uniforms[VIEW_U] = glGetUniformLocation(m_program, "viewMatrix");
	m_uniforms[LIGHT_POS_U] = glGetUniformLocation(m_program, "lightPosition");
	m_uniforms[LIGHT_COL_U] = glGetUniformLocation(m_program, "lightColor");
	m_uniforms[REFL_U] = glGetUniformLocation(m_program, "reflectivity");
	m_uniforms[SHINE_U] = glGetUniformLocation(m_program, "shineDamper");
	m_uniforms[FAKE_LIGHT_U] = glGetUniformLocation(m_program, "fakeLight");
	m_uniforms[SKY_COLOR_U] = glGetUniformLocation(m_program, "skyColor");
}

void Shader::loadFloat(int location, float value)
{
	glUniform1f(location, value);
}

void Shader::loadFakeLight(bool fakeLight)
{
	if (fakeLight == true)
		loadFloat(m_uniforms[FAKE_LIGHT_U], 2.0);
	else
		loadFloat(m_uniforms[FAKE_LIGHT_U], 0.0);
}

void Shader::loadVector(int location, glm::vec3& arr)
{
	glUniform3f(location, arr.x, arr.y, arr.z);
}

void Shader::loadSkyColor(glm::vec3& color)
{
	loadVector(m_uniforms[SKY_COLOR_U], color);
}

void Shader::loadLight(Light& light)
{
	loadVector(m_uniforms[LIGHT_POS_U], light.position);
	loadVector(m_uniforms[LIGHT_COL_U], light.color);
}

void Shader::loadShineVars(float reflectivity, float shineDamper)
{
	loadFloat(m_uniforms[REFL_U], reflectivity);
	loadFloat(m_uniforms[SHINE_U], shineDamper);
}

void Shader::loadBool(int location, bool value)
{
	loadFloat(location, value == true ? 1.0f : 0.0f);
}

void Shader::loadMatrix(int location, glm::mat4& matrix)
{
	glUniformMatrix4fv(location, 1, false, glm::value_ptr(matrix));
}

void Shader::loadTransformationMatrix(glm::mat4& matrix)
{
	loadMatrix(m_uniforms[TRANSFORM_U], matrix);
}

void Shader::loadProjectionMatrix(glm::mat4& matrix)
{
	loadMatrix(m_uniforms[PROJECTION_U], matrix);
}

void Shader::loadViewMatrix(Camera& camera)
{
	loadMatrix(m_uniforms[VIEW_U], createViewMatrix(camera));
}


void Shader::Bind()
{
	glUseProgram(m_program);
}

void Shader::Stop()
{
	glUseProgram(0);
}

Shader::~Shader()
{
	glUseProgram(0);
	for (unsigned int i = 0; i < NUM_SHADER; i++)
	{
		glDetachShader(m_program, m_shaders[i]);
		glDeleteShader(m_shaders[i]);
	}

	glDeleteProgram(m_program);
}

std::string Shader::LoadShader(const std::string& fileName)
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

void Shader::CheckShaderError(GLuint shader, GLuint flag, bool isProgram, const std::string& errorMessage)
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

GLuint Shader::CreateShader(const std::string& text, unsigned int type)
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