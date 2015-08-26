#include "Vector2i.hpp"

XL::Vector2i::Vector2i()
{
	setXY(0, 0);
}

XL::Vector2i::Vector2i(int x, int y)
{
	setXY(x, y);
}

XL::Vector2i* XL::Vector2i::setXY(int x, int y)
{
	this->x = x;
	this->y = y;

	return this;
}

XL::Vector2i* XL::Vector2i::setX(int x)
{
	this->x = x;
	return this;
}

XL::Vector2i* XL::Vector2i::setY(int y)
{
	this->y = y;
	return this;
}

int XL::Vector2i::getX()
{
	return x;
}

int XL::Vector2i::getY()
{
	return y;
}

void XL::Vector2i::setParent(Vector2i* newParent)
{
	parent = newParent;
}

XL::Vector2i* XL::Vector2i::getParent()
{
	return parent;
}


