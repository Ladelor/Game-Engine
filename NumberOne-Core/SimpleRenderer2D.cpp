#include "SimpleRenderer2D.h"
#include "Renderable2D.h"

namespace NumberOne {
	namespace Graphics {
		void SimpleRenderer2D::submit(const Renderable2D* renderable)
		{
			r_RenderQueue.push_back((SimpleSprite*)renderable);
		}

		void SimpleRenderer2D::flush()
		{
			while (!r_RenderQueue.empty())
			{
				const SimpleSprite* renderable = r_RenderQueue.front();

				renderable->getVao()->enable();
				renderable->getIbo()->enable();

				renderable->getShader().setUniformMat4("ml_matrix", Math::mat4::translation(renderable->getPosition()));
				glDrawElements(GL_TRIANGLES, renderable->getIbo()->getCount(), GL_UNSIGNED_SHORT, 0);

				renderable->getVao()->disable();
				renderable->getIbo()->disable();
				r_RenderQueue.pop_front();
			}
		}
	}
}
