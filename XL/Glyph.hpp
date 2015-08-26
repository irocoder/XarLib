#ifndef XL_GLYPH_HPP
#define XL_GLYPH_HPP

namespace XL
{
class Glyph
{
	public:
		Glyph();
		Glyph(int x, int y, int width, int height, int advanceX, int bearingX, int offsetY);

		int x;
		int y;

		int width;
		int height;

		int advanceX;
		int bearingX;
		int offsetY;

	private:
};
};

#endif