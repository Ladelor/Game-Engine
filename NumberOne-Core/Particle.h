#pragma once
#include "Math.h"
#include "Renderable2D.h"

namespace NumberOne {
	namespace Graphics {

		struct Particle
		{
			VertexData p_vertexData;
			Math::vec2 p_velocity;
			GLfloat p_life;

			Particle() : p_velocity(0, 0), p_life(0) 
			{
				p_vertexData.v_tid = 0;
			}
		};
} }