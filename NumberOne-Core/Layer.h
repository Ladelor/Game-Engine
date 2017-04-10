#pragma once 

#include <vector>
#include "Shaders.h"
#include "Renderer2D.h"

namespace NumberOne {
	namespace Graphics {

		class Layer
		{
		protected:
			Renderer2D* l_renderer;
			std::vector<Renderable2D*> l_renderables;
			Shader* l_shader;
			Math::mat4 l_projection;
			Layer(Renderer2D* renderer, Shader* shader, Math::mat4 projection)
				: l_renderer(renderer), l_shader(shader), l_projection(projection)
			{
				l_shader->enable();
				l_shader->setUniformMat4("pr_matrix", l_projection);
			}

		public:
			virtual ~Layer()
			{
				delete l_renderer;
				for (unsigned int i = 0; i < l_renderables.size(); i++)
					delete l_renderables[i];
			}

			void add(Renderable2D* renderable)
			{
				l_renderables.push_back(renderable);
			}

			void render()
			{
				l_shader->enable();
				l_renderer->begin();
				for (const Renderable2D* renderable : l_renderables)
				{
					renderable->submit(l_renderer);
				}
				l_renderer->flush();
			}

			inline const int getSize() const { return l_renderables.size(); }

		};
	}
}

 // !LAYER_H
