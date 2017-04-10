#pragma once

// FREEIMAGE_LIB
#include <FreeImage.h>
#include <glew.h>
#include <GLFW\glfw3.h>
#include <string>

namespace NumberOne {
	namespace Graphics {

		class Texture
		{
		private:
			GLuint t_tid;
			std::string t_filePath;
			GLsizei t_width, t_height;
			
			BYTE* load();
		public:

			Texture(const std::string FileName);
			//~Texture();

			void Enable();
			void Disable();

			inline const unsigned int getHeight() const { return t_height; }
			inline const unsigned int getWidth() const { return t_width; }
			inline const GLuint& gettid() const { return t_tid; }
		};
} }

 //TEXTURE_H
