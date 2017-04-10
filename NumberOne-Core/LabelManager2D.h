#pragma once

#include <algorithm>
#include <ft2build.h>
#include FT_FREETYPE_H
#include "Label.h"

namespace NumberOne {
	namespace Graphics {

		class LabelManager2D : public Renderable2D
		{
		private:
			std::vector<Label*> fm_fonts;

		public:
			LabelManager2D();
			~LabelManager2D();
			void add(std::string text, int x, int y, float size, Math::vec4 color, std::string font);
			void add(Label* label);
			void remove(int position);
			void submit(Renderer2D* renderer) const override;

			inline const int getNumLines() { return fm_fonts.size(); }
			inline const Math::vec3& getPosition(int position);
			inline const unsigned int& getColor(int position);
			inline const float& getSize(int position);
			inline const std::string& getText(int position);
			inline const std::string getFont(int position);
			
			void setFont(int position, std::string& filePath);
			void setPosition(int position, int x, int y);
			void setColor(int position, Math::vec4 col);
			void setSize(int position, float size);
			void setText(int position, std::string text);

		};
} }
 // !FONT_MANAGER_H
