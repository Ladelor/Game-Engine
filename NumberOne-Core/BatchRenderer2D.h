#pragma once

#include "Sprite.h"
#include "Renderer2D.h"
#include "IndexBuffer.h"
#include <ft2build.h>
#include FT_FREETYPE_H
#include "Fonts.h"
#include "freetype-gl.h"


namespace NumberOne {
	namespace Graphics {

 #define RENDERER_MAX_SPRITES 60000
 #define RENDERER_VERTEX_SIZE sizeof(VertexData)
 #define RENDERER_SPRITE_SIZE RENDERER_VERTEX_SIZE * 4
 #define RENDERER_BUFFER_SIZE RENDERER_MAX_SPRITES * RENDERER_SPRITE_SIZE
 #define RENDERER_INDICES_SIZE RENDERER_MAX_SPRITES * 6
 
 #define SHADER_VERTEX_INDEX 0
 #define SHADER_UV_INDEX 1
 #define SHADER_TID_INDEX 2
 #define SHADER_COLOR_INDEX 3

		class BatchRenderer2D : public Renderer2D
		{
		private:
			GLuint r_vao;
			IndexBuffer* r_ibo;
			GLsizei r_indexCount;
			GLuint r_vbo;
			VertexData* r_buffer;
			std::vector<GLuint> r_textures;

		public:
			BatchRenderer2D();
			~BatchRenderer2D();
			void submit(const Renderable2D* renderable) override;

			//this is slower than a for loop with submit
		//	void submitVector(std::vector<Graphics::Sprite*>& renderables);

			void drawString(const std::string& text, const Math::vec3& position, const unsigned int& color, ftgl::texture_atlas_t* TFAtlas, ftgl::texture_font_t* TFFont) override;
			void flush() override;
			void begin() override;
		};
	}
}
 // !BATCHRENDERER2D_H

