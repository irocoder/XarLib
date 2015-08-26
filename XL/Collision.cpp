#include "Collision.hpp"

bool XL::intersects(XL::Vector2i& vec, XL::Rectangle& rect)
{
	int x1 = rect.x;
	int y1 = rect.y;
	int x2 = rect.x + rect.width;
	int y2 = rect.y + rect.height;

	return vec.getX() > x1 && vec.getX() < x2 && vec.getY() > y1 && vec.getY() < y2;
}

bool XL::intersects(XL::Rectangle& rect1, XL::Rectangle& rect2)
{
	return true;
}