#pragma once

#include "Renderable2D.h"

namespace NumberOne {
	namespace Graphics {

		class Sprite : public Renderable2D
		{
		public:
			Sprite(float posX, float posY, float width, float height, Math::vec4 color)
				: Renderable2D(Math::vec2(width, height), Math::vec3(posX, posY, 0), color)
			{}

			Sprite(float posX, float posY, float width, float height, unsigned int color)
				: Renderable2D(Math::vec2(width, height), Math::vec3(posX, posY, 0), color)
			{}

			Sprite(float posX, float posY, float width, float height, Texture* texture)
				: Renderable2D(Math::vec2(width, height), Math::vec3(posX, posY, 0), 0xffffffff, texture)
			{}

		};
} }
 // !SPRITE_H
