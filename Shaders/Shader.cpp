#include "Shader.h"

#include "linking/glad.h"
#include <Vertex.h>
#include <iostream>
#include <fstream>
#include <string>

std::string LoadShaderSource(const char* sourceFile);
std::string LoadShaderSource(const char* sourceFile)
{
	std::string src = "";
	std::string tmp = "";
	std::ifstream shader_In;
	shader_In.open(sourceFile);
	if (shader_In.is_open())
	{
		std::cout << "Shader loading: " << sourceFile << std::endl;
		while (std::getline(shader_In, tmp))
			src += tmp + "\n";
	}
	else
	{
		std::cout << "Error: Can't Open Shader File: " << sourceFile << std::endl;
		return "";
	}
	shader_In.close();
	return src;
}

namespace DLEngine
{
	Shader::Shader(const char* shaderVert, const char* shaderFrag) :
		vertFile(shaderVert), fragFile(shaderFrag)
	{
		
	}

	bool Shader::LoadShaders(unsigned int& shaderPrograme, const char* shaderVert, const char* shaderFrag)
	{
		this->vertFile = shaderVert;
		this->fragFile = shaderFrag;
		GLint shaderCompiled = 0;
		char shaderInfoLog[512];
		std::string shaderVertCode = "";
		std::string shaderFragCode = "";
		shaderVertCode = LoadShaderSource(shaderVert);
		shaderFragCode = LoadShaderSource(shaderFrag);

		// Create Fragment Shader
		this->FragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
		const GLchar* fragSrc = shaderFragCode.c_str();
		glShaderSource(this->FragmentShader, 1, &fragSrc, NULL);
		glCompileShader(this->FragmentShader);
		glGetShaderiv(this->FragmentShader, GL_COMPILE_STATUS, &shaderCompiled);
		if (!shaderCompiled)
		{
			std::cout << "Error: Can't Compile Fragment Shader!" << std::endl;
			glGetShaderInfoLog(this->FragmentShader, 512, NULL, shaderInfoLog);
			std::cout << shaderInfoLog << std::endl;
			return false;
		}

		// Create Vertex Shader
		this->vertexShader = glCreateShader(GL_VERTEX_SHADER);
		const GLchar* vertSrc = shaderVertCode.c_str();
		glShaderSource(this->vertexShader, 1, &vertSrc, NULL);
		glCompileShader(this->vertexShader);
		glGetShaderiv(this->vertexShader, GL_COMPILE_STATUS, &shaderCompiled);
		if (!shaderCompiled)
		{
			std::cout << "Error: Can't Compile Vertex Shader!" << std::endl;
			glGetShaderInfoLog(this->vertexShader, 512, NULL, shaderInfoLog);
			std::cout << shaderInfoLog << std::endl;
			return false;
		}

		// Create Shader Program
		shaderPrograme = glCreateProgram();
		//shaderProgram_id = shaderPrograme;
		glAttachShader(shaderPrograme, FragmentShader);
		glAttachShader(shaderPrograme, vertexShader);
		glLinkProgram(shaderPrograme);
		glGetProgramiv(shaderPrograme, GL_LINK_STATUS, &shaderCompiled);
		if (!shaderCompiled)
		{
			glGetProgramInfoLog(shaderPrograme, 512, NULL, shaderInfoLog);
			std::cout << "Error: Can't Create Shader Program!" << std::endl;
			std::cout << shaderInfoLog << std::endl;
			return false;
		}

		// End
		glUseProgram(0);
		glDeleteShader(this->vertexShader);
		glDeleteShader(this->FragmentShader);
		std::cout << "\nAll Shaders have been loaded & created Successfully!" << std::endl;
		std::cout << "Shader Frag: " << shaderFrag << " Shader Vert: " << shaderVert << std::endl;
		this->shaderProgram_id = shaderPrograme;
		return true;
	}

	void Shader::Use_program(unsigned int& shaderPrograme, int reset)
	{
		if (reset == 0)
		{
			glUseProgram(0);
			return;
		}
		glUseProgram(shaderPrograme);
	}

	void Shader::use(int value)
	{
		glUseProgram(value);
	}

	void Shader::set1i(const char* name, int value)
	{
		this->use(1);
		glUniform1i(glGetUniformLocation(this->shaderProgram_id, name), value);
		this->use(0);
	}
	void Shader::set1f(float value, const char* name)
	{
		this->use(1);
		glUniform1f(glGetUniformLocation(this->shaderProgram_id, name), value);
		this->use(0);
	}
	void Shader::setVec2f(glm::fvec2 value, const char* name)
	{
		this->use(1);
		glUniform2fv(glGetUniformLocation(this->shaderProgram_id, name), 1, glm::value_ptr(value));
		this->use(0);
	}
	void Shader::setVec3f(glm::fvec3 value, const char* name)
	{
		this->Use_program(shaderProgram_id);
		glUniform3fv(glGetUniformLocation(this->shaderProgram_id, name), 1, glm::value_ptr(value));
		this->Use_program(shaderProgram_id, 0);
	}
	void Shader::setVec4f(glm::fvec4 value, const char* name)
	{
		this->use(1);
		glUniform4fv(glGetUniformLocation(this->shaderProgram_id, name), 1, glm::value_ptr(value));
		this->use(0);
	}

	void Shader::setMat3fv(glm::mat3 value, const char* name, unsigned char transpose)
	{
		this->use(1);
		glUniformMatrix3fv(glGetUniformLocation(this->shaderProgram_id, name), 1, transpose, glm::value_ptr(value));
		this->use(0);
	}

	void Shader::setMat4fv(glm::mat4 value, const char* name, unsigned char transpose)
	{
		this->use(1);
		glUniformMatrix4fv(glGetUniformLocation(this->shaderProgram_id, name), 1, transpose, glm::value_ptr(value));
		this->use(0);
	}

	void Shader::Set_VertexAttribPoint(int index, int size, const void* pointer)
    {
        glBindVertexArray(1);
        glVertexAttribPointer(index, size, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)pointer);
        glEnableVertexAttribArray(index);
        glBindVertexArray(0);
    }
}