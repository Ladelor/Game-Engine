#include "Label.h"

namespace NumberOne {
	namespace Graphics {

		Label::Label(std::string text, float x, float y, float size, Math::vec4 color, std::string fontPath)
		: Renderable2D(), l_text(text), l_size(size),  l_fontPath(fontPath)
	{
		r_position = Math::vec3(x, y, 0.0f);
		int r, g, b, a;
		r = (int)(color.x * 255.0f);
		g = (int)(color.y * 255.0f);
		b = (int)(color.z * 255.0f);
		a = (int)(color.w * 255.0f);

		r_color = a << 24 | b << 16 | g << 8 | r;

		l_TFAtlas = ftgl::texture_atlas_new(512, 512, 2);
		l_TFFont = ftgl::texture_font_new_from_file(l_TFAtlas, l_size, l_fontPath.c_str());
	}

	Label::~Label()
	{
		//I don't think I had memory leak when I left these out but I'm going to leave them anyway
		//For now...
		texture_atlas_delete(l_TFAtlas);
		texture_font_delete(l_TFFont);
	}

	Label::Label(std::string text, float x, float y, float size, unsigned int color, std::string fontPath)
		: Renderable2D(), l_text(text), l_size(size), l_fontPath(fontPath)
	{
		r_position = Math::vec3(x, y, 0.0f);
		r_color = color;

		l_TFAtlas = ftgl::texture_atlas_new(512, 512, 2);
		l_TFFont = ftgl::texture_font_new_from_file(l_TFAtlas, l_size, l_fontPath.c_str());
	}
	
	void Label::submit(Renderer2D * renderer) const
	{
		renderer->drawString(l_text, r_position, r_color, l_TFAtlas, l_TFFont);
	}

	void Label::setFont(std::string& filePath)
	{
		l_fontPath = filePath;
		ftgl::texture_atlas_delete(l_TFAtlas);
		ftgl::texture_font_delete(l_TFFont);
		l_TFAtlas = ftgl::texture_atlas_new(512, 512, 2);
		l_TFFont = ftgl::texture_font_new_from_file(l_TFAtlas, l_size, l_fontPath.c_str());
	}

	void Label::setPosition(float x, float y)
	{
		r_position = Math::vec3(x, y, .0f);
	}

	void Label::setColor(Math::vec4 col)
	{
		int r, g, b, a;
		r = (int)(col.x * 255.0f);
		g = (int)(col.y * 255.0f);
		b = (int)(col.z * 255.0f);
		a = (int)(col.w * 255.0f);

		r_color = a << 24 | b << 16 | g << 8 | r;
	}

	void Label::setSize(float size)
	{
		l_size = size;
		ftgl::texture_atlas_delete(l_TFAtlas);
		ftgl::texture_font_delete(l_TFFont);
		l_TFAtlas = ftgl::texture_atlas_new(512, 512, 2);
		l_TFFont = ftgl::texture_font_new_from_file(l_TFAtlas, l_size, l_fontPath.c_str());
	}

	void Label::setText(std::string text)
	{
		l_text = text;
	}

} }
