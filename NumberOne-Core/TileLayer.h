#pragma once 

#include "Layer.h"
#include "BatchRenderer2D.h"
#include "Sprite.h"

namespace NumberOne {
	namespace Graphics {

		class TileLayer : public Layer
		{
		public:
			TileLayer(Shader* shader)
				: Layer(new BatchRenderer2D(), shader, Math::mat4::orthographic(-16.0f, 16.0f, -9.0f, 9.0f, -1.0f, 1.0f))
			{
			}

			~TileLayer() {}
		};
	}
}
 // !TILE_LAYER_H
