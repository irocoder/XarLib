#ifndef XL_FONT_HPP
#define XL_FONT_HPP

#include "Texture2D.hpp"
#include "Glyph.hpp"
#include <string>
#include <vector>
#include <map>

#include <ft2build.h>
#include FT_FREETYPE_H

namespace XL
{
class Font : public Texture2D
{
	public:
		Font();
		Font(const std::string& filePath);
		~Font();
		
		void load(const std::string& filePath); //add special chars
		void load(const std::string& filePath, int size);
		void bind();
		void unbind();

		FT_GlyphSlot glyph;

		//WIDTH AND HEIGHT OF FINAL PACKED BITMAP
		int width = 0;
		int height = 0;

		std::map<unsigned char, XL::Glyph> glyphs;
		std::map<int, std::map<unsigned char, XL::Glyph>> sizes;
	
	private:
		FT_Library freeType;
		FT_Face face;
};
};

#endif