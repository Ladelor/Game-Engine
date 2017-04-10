#pragma once 

#include "Math.h"
#include "renderer2d.h"
#include "Texture.h"

namespace NumberOne {
	namespace Graphics {

		struct VertexData {
			Math::vec3 v_position;
			Math::vec2 v_uv;
			float v_tid;
			unsigned int v_color;
		};

		class Renderable2D
		{
		protected:
			Math::vec2 r_size;
			Math::vec3 r_position;
			unsigned int r_color;
			std::vector<Math::vec2> r_uv;
			Texture* r_texture;

			Renderable2D() : r_texture(nullptr) { setUV(); }

		private:
			void setUV() 
			{
				r_uv.push_back(Math::vec2(0, 0));
				r_uv.push_back(Math::vec2(0, 1));
				r_uv.push_back(Math::vec2(1, 1));
				r_uv.push_back(Math::vec2(1, 0));
			}

		public:
			virtual ~Renderable2D() {}

			Renderable2D(const Math::vec2 size, const Math::vec3 position, const Math::vec4 color, Texture* texture = nullptr)
				: r_size(size), r_position(position), r_texture(texture)
			{
				setUV();

				int r, g, b, a;
				r = (int)(color.x * 255.0f);
				g = (int)(color.y * 255.0f);
				b = (int)(color.z * 255.0f);
				a = (int)(color.w * 255.0f);

				r_color = a << 24 | b << 16 | g << 8 | r;
			}

			Renderable2D(const Math::vec2 size, const Math::vec3 position, unsigned int color, Texture* texture = nullptr)
				: r_size(size), r_position(position), r_color(color), r_texture(texture)
			{
				setUV();
			}

			virtual void submit(Renderer2D* renderer) const 
			{
				renderer->submit(this);
			}

			inline const Math::vec2& getSize() const { return r_size; }
			inline const Math::vec3& getPosition() const { return r_position; }
			inline const unsigned & getColor() const { return r_color; }
			inline const std::vector<Math::vec2>& getUV() const { return r_uv; }
			inline const GLuint gettid() const { return r_texture == nullptr ? 0 : r_texture->gettid(); }
		};
		
} }
 // !RENDERABLE2D_H

