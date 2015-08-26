#ifndef XL_VECTOR2I_HPP
#define XL_VECTOR2I_HPP

namespace XL
{
	class Vector2i
	{
	public:
		Vector2i();
		Vector2i(int x, int y);

		Vector2i* setXY(int x, int y);

		Vector2i* setX(int x);
		Vector2i* setY(int y);

		int getX();
		int getY();


		//pathfinding remove later in favor of more permanent solution
		void setParent(Vector2i* newParent);
		Vector2i* getParent();

	private:
		int x = 0;
		int y = 0;

		//pathfinding
		Vector2i* parent;
	};
};

#endif