#ifndef FONT_H
#define FONT_H

#include <ft2build.h>
#include FT_FREETYPE_H
#include "Renderable2D.h"
#include <FTGL/ftgl.h>
#include "Fonts.h"

namespace NumberOne {
	namespace Graphics {

		class Font : public Renderable2D
		{
		protected:
			unsigned int f_size;
			std::string f_text;


		public:
			Font(std::string& text, float& x, float& y, unsigned int& size, Math::vec4& color);
			virtual ~Font() {}
		
			void setPosition(float& x, float& y);
			void setColor(Math::vec4& col);
			virtual void setFont(std::string& filePath) = 0;
			void setSize(unsigned int& size);
			void setText(std::string& text);

			virtual void render(GLuint shaderID) = 0;

			inline Math::vec3& getPosition() { return r_position; }
			inline unsigned int& getColor() { return r_color; }
			inline unsigned int& getSize() { return f_size; }
			inline std::string& getText() { return f_text; }
		};
	}
}

#endif // 
