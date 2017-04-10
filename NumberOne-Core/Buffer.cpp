#include "Buffer.h"

namespace NumberOne { namespace Graphics {

	Buffer::Buffer(GLfloat* data, GLsizei count, GLuint compCount)
		: b_CompCount(compCount)
	{
		glGenBuffers(1, &b_BufferId);
		glBindBuffer(GL_ARRAY_BUFFER, b_BufferId);
		glBufferData(GL_ARRAY_BUFFER, count * sizeof(GLfloat), data, GL_STATIC_DRAW);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	void Buffer::enable() const
	{
		glBindBuffer(GL_ARRAY_BUFFER, b_BufferId);
	}

	void Buffer::disable() const
	{
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	GLuint Buffer::getCompCount() const
	{
		return b_CompCount;
	}

	Buffer::~Buffer()
	{
		glDeleteBuffers(1, &b_BufferId);
	}

} }