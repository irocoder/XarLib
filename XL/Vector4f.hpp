#ifndef XL_VECTOR4F_HPP
#define XL_VECTOR4F_HPP

namespace XL
{
class Vector4f
{
	public:
		Vector4f(float x, float y, float z, float w);
		
		Vector4f* setXYZW(float x, float y, float z, float w);

		float setX(float x);
		float setY(float y);
		float setZ(float z);
		float setW(float w);

		float getX();
		float getY();
		float getZ();
		float getW();

	private:
		float x = 0;
		float y = 0;
		float z = 0;
		float w = 0;
};
};

#endif