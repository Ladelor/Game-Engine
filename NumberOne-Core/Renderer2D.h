#pragma once

#include <vector>
#include <glew.h>
#include "Math.h"
#include <ft2build.h>
#include FT_FREETYPE_H
#include "TransformationStack.h"
#include "freetype-gl.h"

namespace NumberOne {
	namespace Graphics {

		class Renderable2D;

		class Renderer2D
		{
		protected:
			TransformationStack tStack;
		public:

			void push(const Math::mat4& matrix, bool override = false)
			{
				tStack.push(matrix, override);
			}
			
			void pop()
			{
				tStack.pop();
			}

			virtual void submit(const Renderable2D* renderable) = 0;
			virtual void drawString(const std::string& text, const Math::vec3& position, const unsigned int& color, ftgl::texture_atlas_t* TFAtlas, ftgl::texture_font_t* TFFont) {}
			virtual void flush() = 0;
			virtual void begin() = 0;
		};
} }
 // !RENDERER2D_H

