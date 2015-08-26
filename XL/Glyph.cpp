#include "Glyph.hpp"

XL::Glyph::Glyph()
{
}

XL::Glyph::Glyph(int x, int y, int width, int height, int advanceX, int bearingX, int offsetY)
{
	this->x = x;
	this->y = y;
	this->width = width;
	this->height = height;
	this->advanceX = advanceX;
	this->bearingX = bearingX;
	this->offsetY = offsetY;
}