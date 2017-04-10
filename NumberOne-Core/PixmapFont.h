#ifndef PIXMAP_FONT_H
#define PIXMAP_FONT_H

#include "Font.h"

namespace NumberOne {
	namespace Graphics {

		class PixmapFont : public Font
		{
		private:
			std::string f_fontPath;
			FTGLPixmapFont* f_font;

		protected:
			virtual ~PixmapFont();

		public:
			PixmapFont(std::string& text, float& x, float& y, unsigned int& size, Math::vec4& color, std::string& fontPath);

			void render(GLuint shaderID) override;
			void setFont(std::string& filePath) override;
			inline std::string getFont() { return f_fontPath; }
		};

	}
}
#endif //
