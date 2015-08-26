#ifndef XL_RECTANGLE_HPP
#define XL_RECTANGLE_HPP

namespace XL
{
class Rectangle
{
	public:
		Rectangle();
		Rectangle(int x, int y, int width, int height);

		int x;
		int y;

		int width;
		int height;
};
};
#endif