#pragma once

#include <glew.h>
#include <GLFW\glfw3.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include "mat4.h"

namespace NumberOne { namespace Graphics {
	class Shader
	{
	private:
		const std::string loadShader(const char* filePath);
		const char *s_vertexPath, *s_fragmentPath;
		GLint getUniformLocation(const GLchar* name);

	public:
		GLuint s_shader;
		Shader(const char* vertexPath, const char* fragmentPath);
		~Shader();

		void setUniform1f(const GLchar* name, float val);
		void setUniform1i(const GLchar* name, int val);
		void setUniform1fv(const GLchar* name, float* val, int count);
		void setUniform1iv(const GLchar* name, int* val, int count);
		void setUniform2f(const GLchar* name, const Math::vec2& vec);
		void setUniform3f(const GLchar* name, const Math::vec3& vec);
		void setUniform4f(const GLchar* name, const Math::vec4& vec);
		void setUniformMat4(const GLchar* name, const Math::mat4& matrix);

		void enable() const;
		void disable() const;

	};
} }
 // !SHADERS_H

