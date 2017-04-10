#include "LabelManager2D.h"


namespace NumberOne {
	namespace Graphics {

		LabelManager2D::LabelManager2D() : Renderable2D()
		{
		}

		LabelManager2D::~LabelManager2D()
		{
			glPopAttrib();
			for (unsigned int i = 0; i < fm_fonts.size(); i++)
			{
				fm_fonts.pop_back();
			}
		}

		void LabelManager2D::submit(Renderer2D* renderer) const
		{
			for (Label* label : fm_fonts)
			{
				label->submit(renderer);
			}
		}

		void LabelManager2D::add(std::string text, int x, int y, float size, Math::vec4 color, std::string font)
		{
			fm_fonts.push_back(new Label(text, x, y, size, color, font));
		}

		void LabelManager2D::add(Label* label)
		{
			fm_fonts.push_back(label);
		}

		void LabelManager2D::remove(int position)
		{
			if (position >= fm_fonts.size())
				throw (-1);
			
		//	fm_fonts.erase(std::remove(fm_fonts.begin(), fm_fonts.end(), position), fm_fonts.end());

		}

		const Math::vec3& LabelManager2D::getPosition(int position)
		{
			if (position >= fm_fonts.size())
				throw (-1);

			return fm_fonts[position]->getPosition();
		}

		const unsigned int& LabelManager2D::getColor(int position)
		{
			if (position >= fm_fonts.size())
				throw (-1);

			return fm_fonts[position]->getColor();
		}

		const float& LabelManager2D::getSize(int position)
		{
			if (position >= fm_fonts.size())
				throw (-1);

			return fm_fonts[position]->getSize();
		}

		const std::string& LabelManager2D::getText(int position)
		{
			if (position >= fm_fonts.size())
				throw (-1);

			return fm_fonts[position]->getText();
		}

		const std::string LabelManager2D::getFont(int position)
		{
			if (position >= fm_fonts.size())
				throw (-1);

			return fm_fonts[position]->getFont();
		}

		void LabelManager2D::setFont(int position, std::string& filePath)
		{
			if (position >= fm_fonts.size())
				throw (-1);

			fm_fonts[position]->setFont(filePath);
		}

		void LabelManager2D::setPosition(int position, int x, int y)
		{
			if (position >= fm_fonts.size())
				throw (-1);

			fm_fonts[position]->setPosition(x, y);
		}

		void LabelManager2D::setColor(int position, Math::vec4 col)
		{
			if (position >= fm_fonts.size())
				throw (-1);

			fm_fonts[position]->setColor(col);
		}

		void LabelManager2D::setSize(int position, float size)
		{
			if (position >= fm_fonts.size())
				throw (-1);

			fm_fonts[position]->setSize(size);
		}

		void LabelManager2D::setText(int position, std::string text)
		{
			if (position >= fm_fonts.size())
				throw (-1);

			fm_fonts[position]->setText(text);
		}
		
} }