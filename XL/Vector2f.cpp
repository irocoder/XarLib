#include "Vector2f.hpp"

XL::Vector2f::Vector2f()
{
	setXY(0, 0);
}

XL::Vector2f::Vector2f(double x, double y)
{
	setXY(x, y);
}

XL::Vector2f* XL::Vector2f::setXY(double x, double y)
{
	this->x = x;
	this->y = y;

	return this;
}

XL::Vector2f* XL::Vector2f::setX(double x)
{
	this->x = x;
	return this;
}

XL::Vector2f* XL::Vector2f::setY(double y)
{
	this->y = y;
	return this;
}

double XL::Vector2f::getX()
{
	return x;
}

double XL::Vector2f::getY()
{
	return y;
}




