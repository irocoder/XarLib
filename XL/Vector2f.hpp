#ifndef XL_VECTOR2F_HPP
#define XL_VECTOR2F_HPP

namespace XL
{
class Vector2f
{
	public:
		Vector2f();
		Vector2f(double x, double y);
		
		Vector2f* setXY(double x, double y);

		Vector2f* setX(double x);
		Vector2f* setY(double y);

		double getX();
		double getY();

	private:
		double x = 0;
		double y = 0;
};
};

#endif