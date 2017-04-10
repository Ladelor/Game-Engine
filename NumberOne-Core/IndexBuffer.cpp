#include "IndexBuffer.h"

namespace NumberOne { namespace Graphics {

	IndexBuffer::IndexBuffer(GLushort* data, GLsizei count)
		: b_Count(count)
	{
		glGenBuffers(1, &b_BufferId);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, b_BufferId);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(GLushort), data, GL_STATIC_DRAW);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}

	void IndexBuffer::enable() const
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, b_BufferId);
	}

	void IndexBuffer::disable() const
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}

	GLuint IndexBuffer::getCount() const
	{
		return b_Count;
	}

	IndexBuffer::~IndexBuffer()
	{
		glDeleteBuffers(1, &b_BufferId);
	}

} }

