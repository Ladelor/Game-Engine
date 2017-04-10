#pragma once 
#include "freetype-gl.h"

#include "Renderable2D.h"

namespace NumberOne {
	namespace Graphics {

		class Label : public Renderable2D
		{
		private:
			std::string l_fontPath;
			std::string l_text;
			float l_size;
			ftgl::texture_atlas_t* l_TFAtlas;
			ftgl::texture_font_t* l_TFFont;

		public:
			~Label();
			Label(std::string text, float x, float y, float size, Math::vec4 color, std::string fontPath);
			Label(std::string text, float x, float y, float size, unsigned int color, std::string fontPath);
			void submit(Renderer2D* renderer) const override;

			inline const float& getSize() const { return l_size; }
			inline const std::string& getText() { return l_text; }
			inline const std::string& getFont() { return l_fontPath; }

			void setFont(std::string& filePath);
			void setPosition(float x, float y);
			void setColor(Math::vec4 col);
			void setSize(float size);
			void setText( std::string text);
		};
} }
 // !LABEL_H
