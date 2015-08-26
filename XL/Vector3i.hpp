#ifndef VECTOR_3I_HPP
#define VECTOR_3I_HPP

class Vector3i
{
	public:
		Vector3i();
		Vector3i(int x, int y, int z);
		Vector3i(const Vector3i& copyFrom);

		Vector3i& operator=(const Vector3i& copyFrom);
			
		int x, y, z;
};

#endif