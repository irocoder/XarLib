#ifndef COLLISION_HPP
#define COLLISION_HPP

#include "Vector2i.hpp"
#include "Rectangle.hpp"

namespace XL
{
	bool intersects(XL::Vector2i& vec, XL::Rectangle& rect);
	bool intersects(XL::Rectangle& rect1, XL::Rectangle& rect2);


};

#endif