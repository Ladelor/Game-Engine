#include "Layer.h"

namespace NumberOne {
	namespace Graphics {

		Layer::Layer(Renderer2D* renderer, Shader* shader, Math::mat4 projection)
			: l_renderer(renderer), l_shader(shader), l_projection(projection)
		{
			l_shader->enable();
			l_shader->setUniformMat4("pr_matrix", l_projection);
		}

		Layer::~Layer()
		{
			delete l_renderer;
			for (int i = 0; i < l_renderables.size(); i++)
				delete l_renderables[i];
		}

		void Layer::add(Renderable2D* renderable)
		{
			l_renderables.push_back(renderable);
		}

		void Layer::render()
		{
			l_shader->enable();
			l_renderer->begin();
			for (const Renderable2D* renderable : l_renderables)
				renderable->submit(l_renderer);
			l_renderer->flush();
		}
} }