#pragma once 
#include "Renderer2D.h"

namespace NumberOne{
	namespace Graphics{

		class Group : public Renderable2D
		{
		private:
			std::vector<Renderable2D*> g_renderables;
			Math::mat4 g_transMatrix;

		public:
			Group(Math::mat4 transMatrix)
				: g_transMatrix(transMatrix)
			{
			}

			~Group()
			{
				for (unsigned int i = 0; i < g_renderables.size(); i++)
					delete g_renderables[i];
			}

			inline void add(Renderable2D* renderable)
			{
				g_renderables.push_back(renderable);
			}

			void submit(Renderer2D* renderer) const override
			{
				renderer->push(g_transMatrix);
				for (const Renderable2D* renderable : g_renderables)
					renderable->submit(renderer);

				renderer->pop();
			}

			void setMatrix(Math::mat4 transMatrix)
			{
				g_transMatrix = transMatrix;
			}

		};
	}
}
 // !GROUP_H
