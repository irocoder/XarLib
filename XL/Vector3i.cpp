#include "Vector3i.hpp"

Vector3i::Vector3i()
{
	x = 0;
	y = 0;
	z = 0;
}

Vector3i::Vector3i(int x, int y, int z)
{
	this->x = x;
	this->y = y;
	this->z = z;
}

Vector3i::Vector3i(const Vector3i& copyFrom)
{
	*this = copyFrom;
}

Vector3i& Vector3i::operator=(const Vector3i& copyFrom)
{	
	this->x = copyFrom.x;
	this->y = copyFrom.y;
	this->z = copyFrom.z;

	return *this;
}
