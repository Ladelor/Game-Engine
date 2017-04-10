#include "Shaders.h"

namespace NumberOne { namespace Graphics {
	Shader::Shader(const char* vertexPath, const char* fragmentPath) : s_vertexPath(vertexPath), s_fragmentPath(fragmentPath)
	{
		std::string vertexShader = loadShader(s_vertexPath);
		std::string fragmentShader = loadShader(s_fragmentPath);

		s_shader = glCreateProgram();
		GLuint vertex = glCreateShader(GL_VERTEX_SHADER);
		GLuint fragment = glCreateShader(GL_FRAGMENT_SHADER);

		const char* vertSource = vertexShader.c_str();
		const char* fragSource = fragmentShader.c_str();
		
		glShaderSource(vertex, 1, &vertSource, NULL);
		glCompileShader(vertex);

		GLint result;
		glGetShaderiv(vertex, GL_COMPILE_STATUS, &result);
		if (result == GL_FALSE)
		{
			GLint length;
			glGetShaderiv(vertex, GL_INFO_LOG_LENGTH, &length);
			std::vector<char> error(length);
			glGetShaderInfoLog(vertex, length, &length, &error[0]);
			std::cout << &error[0] << std::endl;
		}

		glShaderSource(fragment, 1, &fragSource, NULL);
		glCompileShader(fragment);

		glGetShaderiv(fragment, GL_COMPILE_STATUS, &result);
		if (result == GL_FALSE)
		{
			GLint length;
			glGetShaderiv(fragment, GL_INFO_LOG_LENGTH, &length);
			std::vector<char> error(length);
			glGetShaderInfoLog(fragment, length, &length, &error[0]);
			std::cout << &error[0] << std::endl;
		}

		glAttachShader(s_shader, vertex);
		glAttachShader(s_shader, fragment);
		glLinkProgram(s_shader);
		glValidateProgram(s_shader);

		glDeleteShader(vertex);
		glDeleteShader(fragment);
	}

	Shader::~Shader()
	{
		glDeleteProgram(s_shader);
	}

	const std::string Shader::loadShader(const char* filePath)
	{

		std::ifstream shaderFile;
		std::string sourceCode, line, temp;
		temp = filePath;

		shaderFile.exceptions(std::ifstream::badbit);
		try
		{
			shaderFile.open(filePath);
			std::stringstream shaderStream;
			shaderStream << shaderFile.rdbuf();
			sourceCode = shaderStream.str();
			shaderFile.close();
		}
		catch (std::ifstream::failure e)
		{
			std::cout << ("Failed to open: " + temp) << std::endl;
		}

		if (sourceCode == "")
			std::cout << ("Failed to open: " + temp) << std::endl;

		return sourceCode;
	};

	void Shader::enable() const
	{
		glUseProgram(s_shader);
	}

	void Shader::disable() const
	{
		glUseProgram(0);
	}

	GLint Shader::getUniformLocation(const GLchar* name)
	{
		return glGetUniformLocation(s_shader, name);
	}


	void Shader::setUniform1f(const GLchar* name, float val)
	{
		glUniform1f(getUniformLocation(name), val);
	}

	void Shader::setUniform1i(const GLchar* name, int val)
	{
		glUniform1i(getUniformLocation(name), val);
	}

	void Shader::setUniform1fv(const GLchar* name, float* val, int count)
	{
		glUniform1fv(getUniformLocation(name), count, val);
	}

	void Shader::setUniform1iv(const GLchar* name, int* val, int count)
	{
		glUniform1iv(getUniformLocation(name), count, val);
	}

	void Shader::setUniform2f(const GLchar* name, const Math::vec2& vec)
	{
		glUniform2f(getUniformLocation(name), vec.x, vec.y);
	}

	void Shader::setUniform3f(const GLchar* name, const Math::vec3& vec)
	{
		glUniform3f(getUniformLocation(name), vec.x, vec.y, vec.z);
	}

	void Shader::setUniform4f(const GLchar* name, const Math::vec4& vec)
	{
		glUniform4f(getUniformLocation(name), vec.x, vec.y, vec.z, vec.w);
	}

	void Shader::setUniformMat4(const GLchar* name, const Math::mat4& matrix)
	{
		glUniformMatrix4fv(getUniformLocation(name), 1, GL_FALSE, matrix.elements);
	}
} }