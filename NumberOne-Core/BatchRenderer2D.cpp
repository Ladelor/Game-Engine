#include "BatchRenderer2D.h"

namespace NumberOne {
	namespace Graphics {

		BatchRenderer2D::BatchRenderer2D()
			: r_indexCount(0)
		{
			glGenVertexArrays(1, &r_vao);
			glGenBuffers(1, &r_vbo);

			glBindVertexArray(r_vao);
			glBindBuffer(GL_ARRAY_BUFFER, r_vbo);
			glBufferData(GL_ARRAY_BUFFER, RENDERER_BUFFER_SIZE, NULL, GL_DYNAMIC_DRAW);
			glEnableVertexAttribArray(SHADER_VERTEX_INDEX);
			glEnableVertexAttribArray(SHADER_UV_INDEX);
			glEnableVertexAttribArray(SHADER_TID_INDEX);
			glEnableVertexAttribArray(SHADER_COLOR_INDEX);
			glVertexAttribPointer(SHADER_VERTEX_INDEX, 3, GL_FLOAT, GL_FALSE, RENDERER_VERTEX_SIZE, (const GLvoid*)NULL);
			glVertexAttribPointer(SHADER_UV_INDEX, 2, GL_FLOAT, GL_FALSE, RENDERER_VERTEX_SIZE, (const GLvoid*)(offsetof(VertexData, VertexData::v_uv)));
			glVertexAttribPointer(SHADER_TID_INDEX, 1, GL_FLOAT, GL_FALSE, RENDERER_VERTEX_SIZE, (const GLvoid*)(offsetof(VertexData, VertexData::v_tid)));
			glVertexAttribPointer(SHADER_COLOR_INDEX, 4, GL_UNSIGNED_BYTE, GL_TRUE, RENDERER_VERTEX_SIZE, (const GLvoid*)(offsetof(VertexData, VertexData::v_color)));
			glBindBuffer(GL_ARRAY_BUFFER, 0);

			GLushort* Indices = new GLushort[RENDERER_INDICES_SIZE];

			int index = 0;
			for (int i = 0; i < RENDERER_INDICES_SIZE; i += 6)
			{
				Indices[i] = index;
				Indices[i + 1] = index + 1;
				Indices[i + 2] = index + 2;
				Indices[i + 3] = index + 2;
				Indices[i + 4] = index + 3;
				Indices[i + 5] = index;
				index += 4;
			}

			r_ibo = new IndexBuffer(Indices, RENDERER_INDICES_SIZE);
			delete[] Indices;
			glBindVertexArray(0);
		}

		BatchRenderer2D::~BatchRenderer2D()
		{
			delete r_ibo;
			glDeleteBuffers(1, &r_vbo);
			glDeleteBuffers(1, &r_vao);
		}

		void BatchRenderer2D::submit(const Renderable2D* renderable)
		{
			const Math::vec2& size(renderable->getSize());
			const Math::vec3& pos(renderable->getPosition());
			const unsigned int& c(renderable->getColor());
			const std::vector<Math::vec2>& uv(renderable->getUV());
			const GLuint& tid(renderable->gettid());
			
			float ts = 0.0f;

			if (tid > 0)
			{
				bool foundTexture = false;
				for (unsigned int i = 0; i < r_textures.size(); i++)
				{
					if (tid == r_textures[i])
					{
						ts = (float)i + 1;
						foundTexture = true;
						break;
					}
				}

				if (!foundTexture)
				{
					if (r_textures.size() >= 32)	//openGL only has 32 texture slots
					{
						flush();
						begin();
					}
					r_textures.push_back(tid);
					ts = (float)r_textures.size();
				}
			}
			

			r_buffer->v_position = *tStack.getStackBack() * pos;
			r_buffer->v_uv = uv[0];
			r_buffer->v_tid = ts;
			r_buffer->v_color = c;
			r_buffer++;

			r_buffer->v_position = *tStack.getStackBack() * Math::vec3(pos.x, pos.y + size.y, 0);
			r_buffer->v_uv = uv[1];
			r_buffer->v_tid = ts;
			r_buffer->v_color = c;
			r_buffer++;

			r_buffer->v_position = *tStack.getStackBack() *Math::vec3(pos.x + size.x, pos.y + size.y, 0);
			r_buffer->v_uv = uv[2];
			r_buffer->v_tid = ts;
			r_buffer->v_color = c;
			r_buffer++;

			r_buffer->v_position = *tStack.getStackBack() *Math::vec3(pos.x + size.x, pos.y, 0);
			r_buffer->v_uv = uv[3];
			r_buffer->v_tid = ts;
			r_buffer->v_color = c;
			r_buffer++;

			r_indexCount += 6;
		}

		/*
		void BatchRenderer2D::submitVector(std::vector<Graphics::Sprite*>& renderables)
		{
			for (int i = 0; i < renderables.size(); i++)
				submit(renderables[i]);
		}
		*/

		void BatchRenderer2D::flush()
		{
			glUnmapBuffer(GL_ARRAY_BUFFER);
			glBindBuffer(GL_ARRAY_BUFFER, 0);

			for (unsigned int i = 0; i < r_textures.size(); ++i)
			{
				glActiveTexture(GL_TEXTURE0 + i);
				glBindTexture(GL_TEXTURE_2D, r_textures[i]);
			}
			r_textures.empty();

			glBindVertexArray(r_vao);
			r_ibo->enable();
			
			glDrawElements(GL_TRIANGLES, r_indexCount, GL_UNSIGNED_SHORT, 0);

			r_ibo->disable();
			glBindVertexArray(0);
			r_indexCount = 0;
		}

		void BatchRenderer2D::begin()
		{
			glBindBuffer(GL_ARRAY_BUFFER, r_vbo);
			r_buffer = (VertexData*)glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);
		}

		void BatchRenderer2D::drawString(const std::string& text, const Math::vec3& position, const unsigned int& c, ftgl::texture_atlas_t* TFAtlas, ftgl::texture_font_t* TFFont)
		{
			float ts = 0.0f;

			bool foundTexture = false;
			for (unsigned int i = 0; i < r_textures.size(); i++)
			{
				if (TFAtlas->id == r_textures[i])
				{
					ts = (float)(i + 1);
					foundTexture = true;
					break;
				}
			}

			if (!foundTexture)
			{
				if (r_textures.size() >= 32)	//openGL only has 32 texture slots
				{
					flush();
					begin();
				}
				r_textures.push_back(TFAtlas->id);
				ts = (float)r_textures.size();
			}
			
			float scaleX = 960.0f / 32.0f;
			float scaleY = 540.0f / 18.0f;

			float x = position.x;
			
			for (int i = 0; i < text.length(); i++)
			{
				char temp = text[i];
				ftgl::texture_glyph_t* glyph = ftgl::texture_font_get_glyph(TFFont, temp);
				if (glyph)
				{
					if (i > 0)
					{
						float kern = ftgl::texture_glyph_get_kerning(glyph, text[i-1]);
						x += kern / scaleX;
					}

					float x0 = x + glyph->offset_x / scaleX;
					float y0 = position.y + glyph->offset_y / scaleY;
					float x1 = x0 + glyph->width / scaleX;
					float y1 = y0 - glyph->height / scaleY;
					
					float u0 = glyph->s0;
					float v0 = glyph->t0;
					float u1 = glyph->s1;
					float v1 = glyph->t1;

					r_buffer->v_position = *tStack.getStackBack() * Math::vec3(x0, y0, 0);
					r_buffer->v_uv = Math::vec2(u0, v0);
					r_buffer->v_tid = ts;
					r_buffer->v_color = c;
					r_buffer++;

					r_buffer->v_position = *tStack.getStackBack() * Math::vec3(x0, y1, 0);
					r_buffer->v_uv = Math::vec2(u0, v1);
					r_buffer->v_tid = ts;
					r_buffer->v_color = c;
					r_buffer++;

					r_buffer->v_position = *tStack.getStackBack() * Math::vec3(x1, y1, 0);
					r_buffer->v_uv = Math::vec2(u1, v1);
					r_buffer->v_tid = ts;
					r_buffer->v_color = c;
					r_buffer++;

					r_buffer->v_position = *tStack.getStackBack() * Math::vec3(x1, y0, 0);
					r_buffer->v_uv = Math::vec2(u1, v0);
					r_buffer->v_tid = ts;
					r_buffer->v_color = c;
					r_buffer++;

					r_indexCount += 6;
					x += glyph->advance_x / scaleX;
				}
			}
		}


	}

}
