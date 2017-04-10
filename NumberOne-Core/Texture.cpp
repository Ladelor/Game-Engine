#include "Texture.h"

namespace NumberOne {
	namespace Graphics {


	Texture::Texture(const std::string filePath)
		: t_filePath(filePath)
	{
		BYTE* bits = load();

		glGenTextures(1, &t_tid);
		glBindTexture(GL_TEXTURE_2D, t_tid);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, t_width, t_height, 0, GL_BGR, GL_UNSIGNED_BYTE, bits);
		glBindTexture(GL_TEXTURE_2D, 0);
		
		delete[] bits;
	}

	BYTE* Texture::load()
	{
		FREE_IMAGE_FORMAT fif = FIF_UNKNOWN;
		//pointer to the image, once loaded
		FIBITMAP *dib(0);
		//pointer to the image data
		BYTE* bits(0);

		//check the file signature and deduce its format
		fif = FreeImage_GetFileType(t_filePath.c_str(), 0);
		//if still unknown, try to guess the file format from the file extension
		if (fif == FIF_UNKNOWN)
			fif = FreeImage_GetFIFFromFilename(t_filePath.c_str());
		//if still unkown, return failure
		if (fif == FIF_UNKNOWN)
			return false;

		//check that the plugin has reading capabilities and load the file
		if (FreeImage_FIFSupportsReading(fif))
			dib = FreeImage_Load(fif, t_filePath.c_str());
		//if the image failed to load, return failure
		if (!dib)
			return false;

		//get the image width and height
		t_width = FreeImage_GetWidth(dib);
		t_height = FreeImage_GetHeight(dib);

		BYTE* pixels = FreeImage_GetBits(dib);
		int bitSize = FreeImage_GetBPP(dib);
		
		//dividing by 8 not working because??????
		int size = t_width * t_height * (bitSize / 6);
		BYTE* result = new BYTE[size];
		memcpy(result, pixels, size);
		FreeImage_Unload(dib);
		
		return result;
	}

	void Texture::Enable()
	{
		glBindTexture(GL_TEXTURE_2D, t_tid);
	}

	void Texture::Disable()
	{
		glBindTexture(GL_TEXTURE_2D, 0);
	}

 } }