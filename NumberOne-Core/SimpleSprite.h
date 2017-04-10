#ifndef SIMPLESPRITE_H
#define SIMPLESPRITE_H

#include "Renderable2D.h"
#include "VertexArray.h"
#include "Shaders.h"
#include "IndexBuffer.h"


namespace NumberOne {
	namespace Graphics {
		class SimpleSprite : public Renderable2D
		{
		private:
			Shader& r_shader;
			VertexArray* r_vao;
			IndexBuffer* r_ibo;

		public:
			SimpleSprite(float posX, float posY, float width, float height, const Math::vec4 color, Shader& shader)
				: Renderable2D(Math::vec2(width, height), Math::vec3(posX, posY, 0), color), r_shader(shader)
			{
				r_vao = new VertexArray();

				GLfloat vertices[]
				{
					posX, posY, 0,
					posX, posY + height, 0,
					posX + width, posY + height, 0,
					posX + width, posY, 0
				};

				GLfloat colors[]
				{
					color.x, color.y, color.z, color.w,
					color.x, color.y, color.z, color.w,
					color.x, color.y, color.z, color.w,
					color.x, color.y, color.z, color.w
				};

				r_vao->addBuffer(new Buffer(vertices, 4 * 3, 3), 0);
				r_vao->addBuffer(new Buffer(colors, 4 * 4, 4), 1);

				GLushort indices[]
				{
					0, 1, 2,
					2, 3, 0
				};

				r_ibo = new IndexBuffer(indices, 6);
			
			}

			~SimpleSprite()
			{
				delete r_vao;
				delete r_ibo;
			}

			inline const VertexArray* getVao() const { return r_vao; }
			inline const IndexBuffer* getIbo() const { return r_ibo; }
			inline Shader& getShader() const { return r_shader; }
		};
	}
}
#endif // !SIMPLESPRITE_H
