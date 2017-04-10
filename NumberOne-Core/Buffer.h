#pragma once

#include <glew.h>

namespace NumberOne { namespace Graphics {
	class Buffer
	{
	private:
		GLuint b_BufferId;
		GLuint b_CompCount;

	public:
		Buffer(GLfloat* data, GLsizei count, GLuint compCount);
		~Buffer();

		//bind buffer
		void enable() const;
		//unbind buffer
		void disable() const;

		GLuint getCompCount() const;
	};
} }

 // !BUFFER_H
