#ifndef SIMPLERENDERER2D_H
#define SIMPLERENDERER2D_H

#include "Renderer2D.h"
#include "SimpleSprite.h"
#include <deque>

namespace NumberOne {
	namespace Graphics {

		class SimpleRenderer2D : Renderer2D
		{
		private:
			std::deque<const SimpleSprite*> r_RenderQueue;
		public:
			void submit(const Renderable2D* renderable) override;
			void flush() override;
			void begin() override {}
		};
	}
}

#endif //SIMPLERENDERER2D_H
