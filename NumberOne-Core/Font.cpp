#include "Font.h"
namespace NumberOne {
	namespace Graphics {

		Font::Font(std::string& text, float& x, float& y, unsigned int& size, Math::vec4& color)
			: f_text(text), f_size(size), Renderable2D()
		{
			r_position = Math::vec3(x, y, 0);
			int r, g, b, a;
			r = color.x * 255.0f;
			g = color.y * 255.0f;
			b = color.z * 255.0f;
			a = color.w * 255.0f;

			r_color = a << 24 | b << 16 | g << 8 | r;
		}

		void Font::setPosition(float& x, float& y)
		{
			r_position = Math::vec3(x, y, 0);
		}

		void Font::setColor(Math::vec4& col)
		{
			int r, g, b, a;
			r = col.x * 255.0f;
			g = col.y * 255.0f;
			b = col.z * 255.0f;
			a = col.w * 255.0f;

			r_color = a << 24 | b << 16 | g << 8 | r;
			
		}
		
		void Font::setSize(unsigned int& size)
		{
			f_size = size;
		}
		
		void Font::setText(std::string& text)
		{
			f_text = text;
		}
	}
}
