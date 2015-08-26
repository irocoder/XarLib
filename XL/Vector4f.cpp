#include "Vector4f.hpp"

XL::Vector4f::Vector4f(float x, float y, float z, float w)
{
	setXYZW(x, y, z, w);
}

XL::Vector4f* XL::Vector4f::setXYZW(float x, float y, float z, float w)
{
	this->x = x;
	this->y = y;
	this->z = z;
	this->w = w;

	return this;
}

float XL::Vector4f::setX(float x)
{
	this->x = x;
	return this->x;
}

float XL::Vector4f::setY(float y)
{
	this->y = y;
	return this->y;
}

float XL::Vector4f::setZ(float z)
{
	this->z = z;
	return this->z;
}

float XL::Vector4f::setW(float w)
{
	this->w = w;
	return this->w;
}

float XL::Vector4f::getX()
{
	return x;
}

float XL::Vector4f::getY()
{
	return y;
}

float XL::Vector4f::getZ()
{
	return z;
}

float XL::Vector4f::getW()
{
	return w;
}