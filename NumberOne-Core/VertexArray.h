#pragma once  

#include <glew.h>
#include <vector>

#include "Buffer.h"

//only works for single sprite drawcalls
namespace NumberOne { namespace Graphics {

	class VertexArray
	{
	private:
		GLuint b_ArrayId;
		std::vector<Buffer*> b_Buffers;

	public:
		VertexArray();
		~VertexArray();

		void addBuffer(Buffer* buffer, GLuint index);

		//bind vertex array
		void enable() const;
		//unbind vertex array
		void disable() const;
	};

} }
 // ! VERTEXARRAY_H

