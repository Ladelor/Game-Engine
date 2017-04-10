#include "VertexArray.h"

namespace NumberOne { namespace Graphics {

	VertexArray::VertexArray()
	{
		glGenVertexArrays(1, &b_ArrayId);
	}

	VertexArray::~VertexArray()
	{
		for (unsigned int i = 0; i < b_Buffers.size(); i++)
			delete b_Buffers[i];
		glDeleteBuffers(1, &b_ArrayId);
	}

	void VertexArray::addBuffer(Buffer* buffer, GLuint index)
	{
		enable();
		buffer->enable();

		glEnableVertexAttribArray(index);
		glVertexAttribPointer(index, buffer->getCompCount(), GL_FLOAT, GL_FALSE, 0, 0);

		buffer->disable();
		disable();
		b_Buffers.push_back(buffer);
	}

	void VertexArray::enable() const
	{
		glBindVertexArray(b_ArrayId);
	}

	void VertexArray::disable() const
	{
		glBindVertexArray(0);
	}

} }
