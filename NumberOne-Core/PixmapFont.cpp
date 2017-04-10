#include "PixmapFont.h"

namespace NumberOne {
	namespace Graphics {

		PixmapFont::PixmapFont(std::string& text, float& x, float& y, unsigned int& size, Math::vec4& color, std::string& fontPath)
			: Font(text, x, y, size, color)
		{
			f_font = new FTGLPixmapFont(fontPath.c_str());

			// If something went wrong, bail out.
			if (f_font->Error())
				std::cout << "Font didn't load properly" << std::endl;

			// Set the font size and render a small text.
			f_font->FaceSize(f_size);
		}


		PixmapFont::~PixmapFont()
		{
			delete f_font;
		}

		void PixmapFont::render(GLuint shaderID)
		{
			glUseProgram(0);
			
			glPixelTransferf(GL_RED_BIAS, r_color.x - 1);
			glPixelTransferf(GL_GREEN_BIAS, r_color.y - 1);
			glPixelTransferf(GL_BLUE_BIAS, r_color.z - 1);
			glPixelTransferf(GL_ALPHA_BIAS, r_color.w - 1);

			f_font->Render(f_text.c_str(), -1, FTPoint(r_position.x + 960/2, r_position.y + 540/2, 0));

			glUseProgram(shaderID);
		}

		void PixmapFont::setFont(std::string& filePath)
		{
			f_fontPath = filePath;
			delete f_font;

			f_font = new FTGLPixmapFont(f_fontPath.c_str());

			// If something went wrong, bail out.
			if (f_font->Error())
				std::cout << "Font didn't load properly" << std::endl;

			// Set the font size and render a small text.
			f_font->FaceSize(f_size);
		}
	}
}