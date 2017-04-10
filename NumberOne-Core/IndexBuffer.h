#pragma once 

#include <glew.h>

namespace NumberOne { namespace Graphics {

	class IndexBuffer
	{
	private:
		GLuint b_BufferId;
		GLuint b_Count;

	public:
		IndexBuffer(GLushort* data, GLsizei count);
		~IndexBuffer();

		//bind buffer
		void enable() const;
		//unbind buffer
		void disable() const;

		GLuint getCount() const;
	};

} }

 // !INDEXBUFFER_H

